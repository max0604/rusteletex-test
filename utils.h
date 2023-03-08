#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>

enum mode {
    AES256 = 0,
    AES192 = 1,
    AES128 = 2
};

int decrypt_cbc(int mode, const uint8_t* key, uint8_t* plain_text);
int encrypt_cbc(int mode, const uint8_t* key, uint8_t* plain_text);

#endif
