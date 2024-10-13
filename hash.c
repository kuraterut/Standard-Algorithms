#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct Node{
   int value;
   char name[MAX_SIZE];
   struct Node *next;
}Node;

int str_to_index(char *str, int size){
    int len = strlen(str);
    int ans = 0;
    for (int i = 0; i < len; i++){
        ans+=(int)str[i];
    }
    return ans%size;
}

char* free_str(char *str){
    free(str);
    str = (char*) calloc(MAX_SIZE+2, sizeof(char));
    return str;
}

Node* add(Node *root, char *name, int val){
//    Node* cur_node = arr;
    Node* tmp = (Node*) malloc(sizeof(Node));
    strcpy(tmp->name, name);
    tmp->value = val;
    tmp->next = NULL;
//    if (cur_node == NULL){
//        arr = tmp;
//        return arr;
//    }
//    while(arr->next!=NULL){
//        arr = arr->next;
//
//    }
//    printf("1");
//    arr->next = tmp;
//    return cur_node;

    if(root == NULL){
        root = tmp;
        return root;
    }
    Node* cur = root;
    Node* parent = NULL;
    while(cur != NULL){
        parent = cur;
        cur = cur->next;
    }
    parent->next = tmp;
    printf("%s %s", parent->name, parent->next->name);

    return root;
}

int get_val(Node** arr, char* name, int size){
    int index = str_to_index(name, size);
    Node *cur_node = arr[index];
    while(cur_node != NULL){
        if (strcmp(cur_node->name, name) == 0){
            return cur_node->value;
        }
        cur_node = cur_node->next;
    }
    return 0;
}


int main(void){
    int N, index, val;
    char *name = (char*) calloc(MAX_SIZE+2, sizeof(char));
    scanf("%d", &N);
    Node **arr = (Node**)malloc(N*sizeof(Node*));
    for (int i = 0; i < N; i++){
        arr[i] = NULL;
    }
    for(int i = 0; i < N; i++){
        scanf("%s", name);
        scanf("%d", &val);
        index = str_to_index(name, N);
        arr[index] = add(arr[index], name, val);
        name = free_str(name);
    }
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%s", name);
        printf("%d", get_val(arr, name, N));
        name = free_str(name);
    }

    return 0;
}