#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256

void swap(unsigned char *a, unsigned char *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

int KSA(char *key, unsigned char *S)
{

    // 配列Sの初期化(S[0]=0, S[1]=1....S[255]=255)
    for (int i = 0; i < N; i++) S[i] = i;
    
    // KSAで初期ストリームを生成
    int j = 0;
    int len = strlen(key);
    for (int i = 0; i < N; i++)
    {
        j = (j + S[i] + key[i % len]) % N;
        swap(&S[i], &S[j]);
    }

    return 0;
}

int PRGA(unsigned char *S, char *text, unsigned char *encrypted_text)
{

    int i = 0;
    int j = 0;
    for (size_t n = 0, len = strlen(text); n < len; n++)
    {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        int K = S[(S[i] + S[j]) % N];
        encrypted_text[n] = K ^ text[n];
    }

    return 0;
}

int RC4(char *key, char *text, unsigned char *encrypted_text)
{

    unsigned char S[N];

    KSA(key, S);
    PRGA(S, text, encrypted_text);
    return 0;
}

int main(int argc, char *argv[])
{
    printf("RC4 module\n");

    // RC4のkeyは短いと簡単に推測されてしまうため、実際に使用する場合は注意が必要
    char *key = "testkey";
    char *text = "this is test.";

    unsigned char *encrypted_text = malloc(sizeof(int) * strlen(text));
    RC4(key, text, encrypted_text);

    printf("This is encrypted text\n");
    printf("==> ");
    for (size_t i = 0, len = strlen(text); i < len; i++)
    {
        printf("%02hhX", encrypted_text[i]);
    }
    printf("\n");

    unsigned char *decrypted_text = malloc(sizeof(int) * strlen(encrypted_text));
    RC4(key, encrypted_text, decrypted_text);

    printf("This is decrypted text\n");
    printf("==> ");
    for (size_t i = 0, len = strlen(text); i < len; i++)
    {
        printf("%c", decrypted_text[i]);
    }

    return 0;
}