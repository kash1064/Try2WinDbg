#include <stdio.h>
#include <stdlib.h>

void readFile()
{
    FILE *fd;
	char fname[] = "test.txt";
    char buf[100+1];
    int chr;

    fd = fopen(fname, "r");

	if(fd == NULL) {
		printf("%s file not open!\n", fname);
		return;
	} 
    else {
		printf("%s file opened!\n", fname);
        fgets(buf, 100, fd);
        printf("%s\n", buf);
    }
    fclose(fd);
    return;
}

int main(int argc, char *argv[])
{
    printf("Hello\n");
    readFile();
    return 0;
}