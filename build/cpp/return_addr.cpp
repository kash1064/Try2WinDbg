#include <stdio.h>

int ret_func()
{
    printf("Call ret_func\n");
    return 0;
}

int evil_func()
{
    printf("Cracked!!!\n");
    return 0;
}

int main()
{
    printf("Start main\n");
    ret_func();
    printf("Return ret_func\n");
    return 0;
}