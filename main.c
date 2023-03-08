#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "utils.h"

static void phex(uint8_t* str, int len);
void generate_key(uint8_t* key, size_t lenth);
extern int mode; // For runtime mode choose

int main(int argc, char* argv[])
{
    if(argc != 4) {
        printf("usage: ./rusteletex-test login passwd key-lenth\n"); return -1;
    }

    char* login = argv[1];
    char* passwd = argv[2];
    int key_lenth = atoi(argv[3]);

    if(strlen(login) > 16 || strlen(passwd) > 16) {
        printf("Input error: login or passwd lenth more than 16 bytes\n"); return -1;
    }
    printf("Passed: login = %s, passwd = %s, key_lenth = %d\n", login, passwd, key_lenth);

    srand(time(NULL));

    uint8_t key16[16];
    uint8_t key24[24];
    uint8_t key32[32];
    uint8_t* key_ptr;
    uint8_t check16[16];
    uint8_t check24[24];
    uint8_t check32[32];
    uint8_t* check_ptr;

    switch (key_lenth) {
        case 128: { mode = AES128; key_ptr = key16; check_ptr = check16;} break;
        case 192: { mode = AES192; key_ptr = key24; check_ptr = check24;} break;
        case 256: { mode = AES256; key_ptr = key32; check_ptr = check32;} break;
        default: printf("Input error: key_lenth must be 128 or 192 or 256 bits (AES standart)\n"); return -1;
    }

    generate_key(key_ptr, key_lenth/8);
    printf("Key:\n");
    phex((uint8_t*)key_ptr, key_lenth/8);

    memset(check_ptr, 0, key_lenth/8);
    memcpy(check_ptr, login, strlen(login));

    //printf("Before encrypt:\n");
    //phex(check_ptr, key_lenth/8);
    encrypt_cbc(key_ptr, check_ptr);
    printf("After encrypt:\n");
    phex(check_ptr, key_lenth/8);
    decrypt_cbc(key_ptr, check_ptr);
    //printf("After decrypt:\n");
    //phex(check_ptr, key_lenth/8);

    if(0 == memcmp((char*)check_ptr, login, strlen(login))) { printf("Success, login = %s\n", (char*)check_ptr); }
    else{ printf("Fail, login = %s\n", (char*)check_ptr);  return -1;}
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

void generate_key(uint8_t* key, size_t lenth)
{
    for (size_t i = 0; i < lenth; i++) {
        key[i] = rand() % 256;
    }
}


#if 0
Написать программу на языке Си,
дающую возможность шифровать и расшифровать введенный пользователем логин и
пароль алгоритмом AES. Длина ключа задается пользователем. Сам ключ генерируется автоматически.
Программа должна состоять из следующих модулей:
1) Основной модуль
2) Модуль, хранящий функции для работы с паролями и уведомлениями пользователя о внесённых данных
3) Модуль, обеспечивающий работу шифрования.
4) Доп. модули на усмотрение программиста

Реализовать проверку на корректность ввода, а также на то,
что после проведенного шифрования и последующей расшифровки
логин и пароль пользователя остался верным. Выложить код на публичный репозиторий github
#endif
