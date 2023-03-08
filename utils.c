#include <stdio.h>
#include <string.h>
#include "utils.h"


int encrypt_cbc(const uint8_t* key, uint8_t* plain_text)
{
    // Initialization vector
    static uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, plain_text, 64);
    AES_clear_ctx_iv(&ctx);
    return 0;
}

int decrypt_cbc(const uint8_t* key, uint8_t* plain_text)
{
    // Initialization vector
    static uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, plain_text, 64);
    AES_clear_ctx_iv(&ctx);
    return 0;
}
