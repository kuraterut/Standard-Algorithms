#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node* right;
    struct Node* left;
    int height;
    int key;
}Node;

Node* new_tree(int key){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->key = key;
    tmp->height = 1;
    return tmp;
}

int height(Node* head){
    if (head == NULL){
        return 0;
    }
    else{
        return head->height;
    }
}

int balance_factor(Node* head){
    return height(head->right)-height(head->left);
}

void fixheight(Node* head)
{
    unsigned char hl = height(head->left);
    unsigned char hr = height(head->right);
    head->height = (hl>hr?hl:hr)+1;
}

Node* rotateright(Node* head){
    Node* left_node = head->left;
    head->left = left_node->right;
    left_node->right = head;
    fixheight(head);
    fixheight(left_node);
    return left_node;
}

Node* rotateleft(Node* head){
    Node* right_node = head->right;
    head->right = right_node->left;
    right_node->left = head;
    fixheight(head);
    fixheight(right_node);
    return right_node;
}

Node* balance(Node* p) // балансировка узла p
{
    fixheight(p);
    if (balance_factor(p) == 2) {
        if (balance_factor(p->right) < 0){
            p->right = rotateright(p->right);
        }
        return rotateleft(p);
    }
    if (balance_factor(p) == -2) {
        if (balance_factor(p->left) > 0){
            p->left = rotateleft(p->left);
        }
        return rotateright(p);
    }
    return p;
}

Node* add_node(Node* head, int key){
    if (head == NULL){
       return new_tree(key);
    }
    if (head->key < key){
        head->left = add_node(head->left, key);
    }
    else if(head->key > key){
        head->right = add_node(head->right, key);
    }
    return balance(head);
}

int search(Node* head, int key){
    if (head == NULL){
        return 0;
    }
    if (head->key < key){
        return search(head->right, key);
    }
    else if(head->key > key){
        return search(head->left, key);
    }
    else{
        return head->key;
    }
}

int main(void){
    int N, cur_N;
    scanf("%d", &N);
    Node* tree = NULL;
    for (int i = 0; i < N; i++){
        scanf("%d", &cur_N);
        tree = add_node(tree, cur_N);
        printf("%d", search(tree, cur_N));
    }
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        scanf("%d", &cur_N);
        printf("%d", search(tree, cur_N));
    }
    return 0;
}