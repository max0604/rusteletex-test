#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>
#include "aes.h"

int decrypt_cbc(const uint8_t* key, uint8_t* plain_text);
int encrypt_cbc(const uint8_t* key, uint8_t* plain_text);

#endif
