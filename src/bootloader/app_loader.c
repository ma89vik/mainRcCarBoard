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
#include "reset.h"


static const uint8_t pub_key[] = {0x67 ,0x0e ,0x17 ,0x78 ,0x54 ,0x21 ,0x5b ,0x00 ,0xf8 ,0xfd ,0x0f ,0x98 ,0x51 ,0xdf 
,0x6c ,0xbe ,0x60 ,0xb3 ,0x44 ,0xf6 ,0xdf ,0xf7 ,0x9e ,0x8d ,0x87 ,0xb1 ,0xad ,0x30 ,0x64 ,0xa4 
,0x2f ,0x25 ,0x37 ,0x4a ,0x77 ,0x6c ,0x71 ,0xcb ,0x89 ,0xe8 ,0xb9 ,0xaa ,0x48 ,0x4d ,0x26 
,0x23 ,0x3c ,0x91 ,0x65 ,0x82 ,0xe5 ,0x21 ,0x95 ,0x10 ,0xea ,0x7e ,0x82 ,0x0d ,0xda ,0x0a 
,0x1a ,0x05 ,0xf4 ,0x1a
};

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
    if (uECC_verify(pub_key , digest, TC_SHA256_DIGEST_SIZE, (uint8_t*)signature, uECC_secp256r1()) != 1) {
        printf("Failed to verify app image signature\n");
        return BOOTLOADER_FAIL;
    }
    printf("Successfully verified the app signature, image is OK to boot\n");
    return BOOTLOADER_OK;
}

/* Aborts if fails to verify */
static void app_verify(fw_hdr_t *app_header)
{
    if (app_header->fw_magic != FW_MAGIC_NUMBER) {
        printf("App verify failed: expected header magic number %d, got %d\n", FW_MAGIC_NUMBER, app_header->fw_magic);
        goto fail;
    }

    uint8_t digest[32];
    if (app_image_calc_sha256((uint32_t)app_header + sizeof(fw_hdr_t), app_header->data_size, digest) != BOOTLOADER_OK){
        goto fail;
    }

    if (app_image_verify_sig(app_header->fw_ecdsa, digest) != BOOTLOADER_OK) {
        goto fail;
    }
    return;
fail: 
    printf("App verify failed\n");
    reset();
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