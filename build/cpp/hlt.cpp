#include <stdio.h>

void non_task()
{
    printf("Non task\n");
    return;
}

int main()
{
    printf("Start HLT\n");
    __asm__("hlt\n\t");

    non_task();
    printf("End HLT\n");
    return 0;
}