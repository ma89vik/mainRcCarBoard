#!/bin/python3
import struct
import argparse

from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.asymmetric import utils
from cryptography.hazmat.primitives import serialization

# header offsets in bytes
HEADER_SEEK_OFFSETS = {"data_size" : 4, "ecdsa" : 28 }
HEADER_SIZE = 92

# Type supported by app_sign.py
HDR_TYPE = 0x1
FW_MAGIC_BYTES = 0xBEAD

def image_sanity_check(header_bin):
    header_magic, header_version = struct.unpack("<HH" , header_bin[0:4])
    fw_type, ver_major, ver_minor, ver_patch = struct.unpack("<BBBB", header_bin[8:12])
    vector_addr = header_bin[12:16].hex()
    git_sha = header_bin[20:28].hex()

    if header_magic != FW_MAGIC_BYTES:
        raise ValueError("Unexpected firmware magic bytes = {}, expected {}".format(header_magic, FW_MAGIC_BYTES))

    if header_version != HDR_TYPE:
        raise ValueError("Unexpected header version = {}, expected {}".format(header_version, HDR_TYPE))

    if ver_major == ver_minor == ver_patch == 0:
        raise ValueError("Image version not set")

    if vector_addr == 0:
        raise ValueError("Image vector table address not set")

    if git_sha == 0:
        raise ValueError("Image git SHA not set")

    print("Signing image: header version = {}, app version = {}.{}.{}, commit = {} with vector table address = 0x{}".format(
          header_version, ver_major, ver_minor, ver_patch, git_sha, vector_addr))

def verify_image(image, public_key_path):
    with open(image, "rb") as f:
        header_bin = f.read(HEADER_SIZE)
        image_bin = f.read()

    image_sanity_check(header_bin)
    r = int.from_bytes(header_bin[28:60], byteorder='big')
    s = int.from_bytes(header_bin[60:92], byteorder='big')
    sig = utils.encode_dss_signature( r, s )

    # Verify signature
    with open(public_key_path, 'rb') as f:
        public_key = serialization.load_pem_public_key(f.read())
        public_key.verify(sig, image_bin, ec.ECDSA(hashes.SHA256()))

    print("Image signature verified")

def gen_ecdsa(image, private_key_path):
    with open(private_key_path, 'rb') as f:
        private_key = serialization.load_pem_private_key(f.read(), password=None)

    chosen_hash = hashes.SHA256()
    hasher = hashes.Hash(chosen_hash)
    hasher.update(image)
    digest = hasher.finalize()

    print("SHA256 Image digest: {}".format(digest.hex()))

    signature = private_key.sign(digest, ec.ECDSA(utils.Prehashed(chosen_hash)))
    print("ECDSA signature: {}, len = {}".format(signature, len(signature)))

    (r,s) = utils.decode_dss_signature(signature)

    return r.to_bytes(32, byteorder='big') + s.to_bytes(32, byteorder='big')


# Updates the binary header with ECDSA and data size
def update_image_header(image_path, sig, size):
    with open(image_path, 'r+b') as f:
        f.seek(HEADER_SEEK_OFFSETS['data_size'])
        f.write(struct.pack("<L", size))

        f.seek(HEADER_SEEK_OFFSETS['ecdsa'])
        f.write(sig)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Sign app image with ECDSA')
    parser.add_argument('image', help='Application image to be signed')
    parser.add_argument('private_key_path', help='256-bit key for ECDSA')
    parser.add_argument('public_key_path', help='256-bit key for ECDSA')

    args = parser.parse_args()

    with open(args.image, "rb") as f:
        header_bin = f.read(HEADER_SIZE)
        image_bin = f.read()
    
    image_sanity_check(header_bin)
    signature = gen_ecdsa(image_bin, args.private_key_path)
    update_image_header(args.image, signature, len(image_bin))

    # Check the updated images
    verify_image(args.image, args.public_key_path)

