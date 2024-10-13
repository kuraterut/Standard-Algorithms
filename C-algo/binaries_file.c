#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>


int main(void){
    FILE *file_input, *file_r;
    file_input = fopen("1.bin", "ab+");
    int k = 10;
    fwrite(&k, sizeof(int), 1, file_input);
    fclose(file_input);
    file_r = fopen("1.bin", "rb");
    int p;
    fread(&p, sizeof(int), 1, file_r);
    printf("%d", p);
    fclose(file_r);
    return 0;
}
