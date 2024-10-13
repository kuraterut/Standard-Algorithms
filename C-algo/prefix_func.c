#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int* prefix_func(char *str, int len){
    int *pi = (int*) malloc(len*sizeof(int));
    for (int i = 0; i < len; i++){
        pi[i] = 0;
    }
    int j = 0;
    for (int i = 1; i < len; i++){
        if (str[i] != str[j]){
            while(j!=0 && str[i] != str[j]){
                j = pi[j - 1];
            }
            if (j == 0){
                pi[i] = 0;
            }
            if (str[i] == str[j]){
                pi[i] = j+1;
                j++;
            }
        }
        else if (str[i] == str[j]){
            pi[i] = j+1;
            j++;
        }
    }
    return pi;
}

int main(void){
    char *string = (char*) calloc(1002, sizeof(char));
    scanf("%s", string);
    int len = strlen(string);
    int *pi_ans;
    pi_ans = prefix_func(string, len);
    for(int i = 0; i < len; i++){
        printf("%d ", pi_ans[i]);
    }
}
