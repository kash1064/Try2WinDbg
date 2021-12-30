#ifndef __BASE64_H__
#define __BASE64_H__

// Data

// Base64 tables
static const char BASE64_TABLE[] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

static const char BASE64_TABLE_URL[] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"};

static const char BASE64_TABLE_CUSTOM1[] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"};

static const int BASE64_TABLE_LENGTH = {
    sizeof(BASE64_TABLE) / sizeof(BASE64_TABLE[0]) - 1};

// enum型で使用するBase64Tableの種類を定義
typedef enum tagBASE64_TYPE
{
    BASE64_TYPE_STANDARD,
    BASE64_TYPE_URL,
    BASE64_TYPE_CUSTOM1
} BASE64_TYPE;

typedef struct tagBASE64_SPEC
{
    BASE64_TYPE type;
    const char *table;
    char pad;
    char *lineSep;
    int lineSepLength;
} BASE64_SPEC;

static const BASE64_SPEC BASE64_SPECS[] = {
    {BASE64_TYPE_STANDARD, BASE64_TABLE, '=', NULL, 0},
    {BASE64_TYPE_URL, BASE64_TABLE_URL, '=', NULL, 0},
    {BASE64_TYPE_CUSTOM1, BASE64_TABLE_CUSTOM1, '=', NULL, 0}
};

static const size_t BASE64_SPECS_LENGTH = {
    sizeof(BASE64_SPECS) / sizeof(BASE64_SPECS[0])
};

// Export function
char *base64Encode(const char *data, const size_t size, const BASE64_TYPE type);
char *base64Decode(const char *base64, size_t *retSize, const BASE64_TYPE type);

// Test data
typedef struct tagBASE64_TEST {
    BASE64_TYPE type;
    const char *data;
    size_t size;
    const char *base64;
} BASE64_TEST;

static const BASE64_TEST BASE64_TESTS[] = {
    {BASE64_TYPE_STANDARD, "this is test", 12, "dGhpcyBpcyB0ZXN0"},
    {BASE64_TYPE_STANDARD, "Hello", 5, "SGVsbG8="},
    {BASE64_TYPE_STANDARD, "Fan-Fan-Fun!!", 13, "RmFuLUZhbi1GdW4hIQ=="},
    {BASE64_TYPE_STANDARD, "AAA", 3, "QUFB"},
};

static const size_t BASE64_TESTS_LENGTH = {sizeof(BASE64_TESTS) / sizeof(BASE64_TESTS[0])};

#endif // !__BASE64_H__