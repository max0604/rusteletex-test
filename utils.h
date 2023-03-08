#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>

enum mode {
    AES256 = 0,
    AES192 = 1,
    AES128 = 2
};

int decrypt_cbc(int mode, uint8_t* key);
int encrypt_cbc(int mode, uint8_t* key);

#endif
