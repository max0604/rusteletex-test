#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "utils.h"

extern int mode;

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

    return encrypt_and_decrypt_login_and_passwd(key_ptr, check_ptr, key_lenth/8, login, passwd);
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
