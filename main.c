#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"

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
    printf("login = %s, passwd = %s, key_lenth = %d\n", login, passwd, key_lenth);

    switch (key_lenth) {
        case 128: { mode = AES128; } break;
        case 192: { mode = AES192; } break;
        case 256: { mode = AES256; } break;
        default: printf("Input error: key_lenth must be 128 or 192 or 256 bits (AES standart)\n"); return -1;
    }

    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

    int exit = encrypt_cbc(mode, key) + decrypt_cbc(mode, key);
    (void)exit;

    return 0;
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
