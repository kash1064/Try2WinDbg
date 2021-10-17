#include <stdio.h>

int main()
{
    printf("Start HLT\n");
    __asm__("hlt\n\t");
    return 0;
}