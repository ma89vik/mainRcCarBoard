#include "app_loader.h"
#include "bootloader_uart.h"
#include "memory_map.h"
#include "board.h"
#include "fw_header.h"
#include "printf.h"
#include <stdbool.h>
#include "tinycrypt/sha256.h"
#include "tinycrypt/ecc_dsa.h"
#include <tinycrypt/constants.h>
#include <tinycrypt/utils.h>
#include "bootloader_err.h"


static const uint8_t pub_key[] = {06,0xf8,0xad,0x6c,0x39,0x38,0xcd,0x7c,0xf0,0x8c,0xf1,0x4e,0xad,0x6a,
0xf4,0xb0,0xb8,0xa2,0x2f,0x4c,0xe8,0x58,0xf8,0xf6,0x5b,0x08,0x8f,0x3e,0x96,
0x44,0x28,0x25,0x8a,0xd9,0x35,0x1e,0xe4,0x47,0xa8,0x03,0xd6,0x55,0x58,0xda,
    0x02,0x5b,0x6e,0xb7,0x35,0x0d,0xda,0x67,0x0d,0x91,0x47,0xfa,0x8e,0x1e,0x75,
    0x37,0x2b,0xbc,0x96,0x56};

_Static_assert(sizeof(pub_key) == 64, "Pub key size");


// static void load_app(uint32_t pc, uint32_t sp) {
//     __asm("           \n\
//           cpsid if    /* disable interruprs */\n\
//           msr msp, r1 /* load r1 into MSP */\n\
//           bx r0       /* branch to the address at r0 */\n\
//     ");
// }

static void app_header_print(fw_hdr_t *app_header)
{
    printf("App header\n");
    printf("Magic number,0x %X\n", app_header->fw_magic);
    printf("Header version: %d\n", app_header->fw_hdr_version);
    printf("Size: %d\n", app_header->data_size);
    printf("Type: %X\n", app_header->fw_type);
    printf("Version: %d.%d.%d\n", app_header->version_major, app_header->version_minor, app_header->version_patch);
    printf("Vector table: %X\n", app_header->vector_addr);

    //printf("git SHA: *.%s", 6, app_header->git_sha);
}


static bootloader_err_t app_image_calc_sha256(const uint32_t app_image_start, uint32_t image_size, uint8_t *digest)
{
    struct tc_sha256_state_struct image_sha256_state_stuct;
    TCSha256State_t image_sha256_state = &image_sha256_state_stuct;
    if (tc_sha256_init(image_sha256_state) != TC_CRYPTO_SUCCESS) {
        printf("Failed to init SHA256\n");
        return BOOTLOADER_FAIL;
    } 

    if (tc_sha256_update(image_sha256_state, (uint8_t*)app_image_start, image_size) != TC_CRYPTO_SUCCESS) {
        printf("Failed to update SHA256\n");
        return BOOTLOADER_FAIL;
    }

    if (tc_sha256_final(digest, image_sha256_state) != TC_CRYPTO_SUCCESS) {
        printf("Failed to finish SHA256\n");
        return BOOTLOADER_FAIL;
    }  
    
    return BOOTLOADER_OK;
}

static bootloader_err_t app_image_verify_sig(const uint8_t *signature, const uint8_t *digest)
{
    printf("verify %d\n", uECC_verify(pub_key , digest, TC_SHA256_DIGEST_SIZE, (uint8_t*)signature, uECC_secp256r1()));

    return BOOTLOADER_OK;
}

static bool app_verify(fw_hdr_t *app_header)
{
    bootloader_err_t ret = BOOTLOADER_FAIL;

    if (app_header->fw_magic != FW_MAGIC_NUMBER) {
        printf("App verify failed: expected header magic number %d, got %d\n", FW_MAGIC_NUMBER, app_header->fw_magic);

    }

    uint8_t digest[32];
    app_image_calc_sha256((uint32_t)app_header + sizeof(fw_hdr_t), app_header->data_size, digest);

    ret = app_image_verify_sig(app_header->fw_ecdsa, digest);

    return ret;
}

void app_loader_start()
{
    /* Verify app */   
    
    void *app_code = (void *)&__approm_start__;
    fw_hdr_t *app_header = (fw_hdr_t*)app_code;

    app_header_print(app_header);
    app_verify(app_header);

    printf("Loading app from 0x%p\n",app_code );

    /* De-init all HW */
    //load_app(app_start, app_sp);

    /* Should never get here */
}