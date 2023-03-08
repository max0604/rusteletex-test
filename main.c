#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "utils.h"

static void phex(uint8_t* str, int len);
void generate_key(uint8_t* key, size_t lenth);

int main(int argc, char* argv[])
{
    if(argc != 4) {
        printf("usage: ./rusteletex-test login passwd key-lenth\n"); return -1;
    }

    char* login = argv[1];
    char* passwd = argv[2];
    int key_lenth = atoi(argv[3]);
    int mode = 0;

    if(strlen(login) > 16 || strlen(passwd) > 16) {
        printf("Input error: login or passwd lenth more than 16 bytes\n"); return -1;
    }
    printf("Passed: login = %s, passwd = %s, key_lenth = %d\n", login, passwd, key_lenth);

    srand(time(NULL));

    switch (key_lenth) {
        case 128: { mode = AES128; } break;
        case 192: { mode = AES192; } break;
        case 256: { mode = AES256; } break;
        default: printf("Input error: key_lenth must be 128 or 192 or 256 bits (AES standart)\n"); return -1;
    }

    uint8_t key[16];
    generate_key(key, sizeof(key));
    printf("Key:\n");
    phex(key, 16);

    char check[16];
    memset(check, 0, sizeof(check));
    memcpy(check, login, strlen(login));

    printf("Before encrypt:\n");
    phex((uint8_t*)check, 16);
    encrypt_cbc(mode, key, (uint8_t*)check);
    printf("After encrypt:\n");
    phex((uint8_t*)check, 16);
    decrypt_cbc(mode, key, (uint8_t*)check);
    printf("After decrypt:\n");
    phex((uint8_t*)check, 16);

    if(0 == memcmp((char*)check, login, strlen(login))) { printf("Success, login = %s\n", (char*)check); }
    else{ printf("Fail, login = %s\n", (char*)check); }

    memset(check, 0, sizeof(check));


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
