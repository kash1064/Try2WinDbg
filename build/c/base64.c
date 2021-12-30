
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base64.h"

char *base64Encode(const char *data, const size_t size, const BASE64_TYPE type)
{
    BASE64_SPEC base64_spec;
    size_t length;
    char *base64;
    char *cursor;
    int lineLength;
    int i;
    int j;

    if (data == NULL) {
        return NULL;
    }

    // base64_specの初期化
    base64_spec = BASE64_SPECS[0];
    for (i = 0; i < (int)BASE64_SPECS_LENGTH; i++) {
        if (BASE64_SPECS[i].type == type) {
            base64_spec = BASE64_SPECS[i];
            break;
        }
    }

    // エンコード後の文字列格納領域の確保
    length = ((size * 4) / 3) + 3;

    // mallocの戻り値は確保したメモリブロックを指すポインタ
    base64 = malloc(length);
    if (base64 == NULL) {
        return NULL;
    }

    cursor = base64;
    lineLength = 0;

    // 3文字単位でエンコードを行う(エンコード後は4文字になる)
    for (i = 0, j = size; j > 0; i += 3, j -= 3) {
        if (j == 1) {
            *(cursor++) = base64_spec.table[(data[i + 0] >> 2 & 0x3f)];
            *(cursor++) = base64_spec.table[(data[i + 0] << 4 & 0x30)];
            *(cursor++) = base64_spec.pad;
            *(cursor++) = base64_spec.pad;
        }
        else if (j == 2) {
            *(cursor++) = base64_spec.table[(data[i + 0] >> 2 & 0x3f)];
            *(cursor++) = base64_spec.table[(data[i + 0] << 4 & 0x30) | (data[i + 1] >> 4 & 0x0f)];
            *(cursor++) = base64_spec.table[(data[i + 1] << 2 & 0x3c)];
            *(cursor++) = base64_spec.pad;
        }
        else {
            *(cursor++) = base64_spec.table[(data[i + 0] >> 2 & 0x3f)];
            *(cursor++) = base64_spec.table[(data[i + 0] << 4 & 0x30) | (data[i + 1] >> 4 & 0x0f)];
            *(cursor++) = base64_spec.table[(data[i + 1] << 2 & 0x3c) | (data[i + 2] >> 6 & 0x03)];
            *(cursor++) = base64_spec.table[(data[i + 2] << 0 & 0x3f)];
        }
    }
    *cursor = 0;

    return base64;
}

char *base64Decode(const char *base64, size_t *retSize, const BASE64_TYPE type)
{
    BASE64_SPEC base64_spec;
    char table[0x80];
    size_t length;
    char *data;
    char *cursor;
    int i;
    int j;

    if (base64 == NULL) {
        return NULL;
    }

    // base64_specの初期化
    base64_spec = BASE64_SPECS[0];
    for (i = 0; i < (int)BASE64_SPECS_LENGTH; i++) {
        if (BASE64_SPECS[i].type == type) 
        {
            base64_spec = BASE64_SPECS[i];
            break;
        }
    }

    // デコードするBase64文字列用のメモリ領域の確保
    length = strlen(base64);
    data = malloc(length * 3 / 4 + 3);
    if (data == NULL) {
        return NULL;
    }

    memset(table, 0x80, sizeof(table));
    for (i = 0; i < BASE64_TABLE_LENGTH; i++) {
        table[base64_spec.table[i] & 0x7f] = i;
    }

    cursor = data;
    for (i = 0, j = 0; i < (int)length; i++, j = i % 4) {
        char ch;
        if (base64[i] == base64_spec.pad)
        {
            break;
        }
        ch = table[base64[i] & 0x7f];
        if (ch & 0x80) {
            continue;
        }
        if (j == 0) {
            *cursor = ch << 2 & 0xfc;
        }
        else if (j == 1) {
            *(cursor++) |= ch >> 4 & 0x03;
            *cursor = ch << 4 & 0xf0;
        }
        else if (j == 2) {
            *(cursor++) |= ch >> 2 & 0x0f;
            *cursor = ch << 6 & 0xc0;
        }
        else {
            *(cursor++) |= ch & 0x3f;
        }
    }
    *cursor = 0;
    *retSize = cursor - data;

    return data;
}

int main(void) {
    int i;
    for (i = 0; i < (int)BASE64_TESTS_LENGTH; i++) {
        BASE64_TEST test;
        char *data;
        char *base64;
        size_t size;

        test = BASE64_TESTS[i];

        base64 = base64Encode(test.data, test.size, test.type);
        printf("BASE64(\"%s\") = \"%s\"\n", test.data, base64);
        assert(strcmp(base64, test.base64) == 0);

        data = base64Decode(base64, &size, test.type);
        printf("DATA(\"%s\") = \"%s\"\n", base64, data);
        assert(size == test.size);
        assert(memcmp(data, test.data, size) == 0);

        free(base64);
        free(data);
    }

    return 0;
}
