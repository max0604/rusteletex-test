#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>
#include "aes.h"

int decrypt_cbc(const uint8_t* key, uint8_t* plain_text);
int encrypt_cbc(const uint8_t* key, uint8_t* plain_text);

int encrypt_and_decrypt_login_and_passwd(uint8_t* key_ptr, uint8_t* check_ptr, size_t len, char* login, char* passwd);

#endif
