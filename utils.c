#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

// prints string as hex
static void phex(uint8_t* str, int len)
{
    unsigned char i;
    for (i = 0; i < len; ++i)
        printf("%.2x", str[i] & 0xff);
    printf("\n");
}

static void generate_key(uint8_t* key, size_t lenth)
{
    for (size_t i = 0; i < lenth; i++) {
        key[i] = rand() % 256;
    }
}

int encrypt_and_decrypt_login_and_passwd(uint8_t* key_ptr, uint8_t* check_ptr, size_t len, char* login, char* passwd)
{
    generate_key(key_ptr, len);
    printf("Key:\n");
    phex((uint8_t*)key_ptr, len);
    printf("\n");

    memset(check_ptr, 0, len);
    memcpy(check_ptr, login, strlen(login));

    encrypt_cbc(key_ptr, check_ptr);
    printf("Encrypted login:\n");
    phex(check_ptr, len);
    decrypt_cbc(key_ptr, check_ptr);

    if(0 == memcmp((char*)check_ptr, login, strlen(login))) { printf("Decrypt Success, login = %s\n\n", (char*)check_ptr); }
    else{ printf("Decrypt Fail, login = %s\n\n", (char*)check_ptr);  return -1;}


    memset(check_ptr, 0, len);
    memcpy(check_ptr, passwd, strlen(login));

    encrypt_cbc(key_ptr, check_ptr);
    printf("Encrypted passwd:\n");
    phex(check_ptr, len);
    decrypt_cbc(key_ptr, check_ptr);

    if(0 == memcmp((char*)check_ptr, passwd, strlen(passwd))) { printf("Decrypt success, passwd = %s\n\n", (char*)check_ptr); }
    else{ printf("Decrypt Fail, passwd = %s\n\n", (char*)check_ptr);  return -1;}

    return 0;
}
