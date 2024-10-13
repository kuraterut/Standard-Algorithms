#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    struct Node* right;
    struct Node* left;
    struct Node* parent;
    int key;
}Node;

Node* new_tree(Node *root, int key){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->right = NULL;
    tmp->left = NULL;
    tmp->parent = NULL;
    tmp->key = key;
    root = tmp;
    return root;
}

Node* add(Node* root, int key){
    if(root == NULL){
        return new_tree(root, key);
    }
    Node* cur = root;
    Node* parent = NULL;
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->key = key;
    while(cur != NULL){
        if(key == cur->key){
            return root;
        }
        parent = cur;
        if(key < cur->key){
            cur = cur->left;
        }
        else{
            cur = cur->right;
        }
    }
    tmp->parent = parent;
    tmp->left = tmp->right = NULL;
    if (key < parent->key){parent->left = tmp;}
    else{parent->right = tmp;}
    return root;
}

Node *search(Node* root, int key){
    Node* head = root;
    while(head != NULL && head->key != key){
        if (key < head->key){
            head = head->left;
        }
        else{
            head = head->right;
        }
    }
    return head;
}

Node *min(Node* root){
    Node* head = root;
    while (head->left != NULL){
        head = head->left;
    }
    return head;
}

Node *delete(Node* root, int key){
    Node* del_elem = NULL;
    del_elem = search(root, key);
    if (del_elem == NULL || del_elem == root){return root;}
    Node* parent_del = del_elem->parent;
//1 Случай
    if (del_elem->right == NULL && del_elem->left == NULL){
        if(parent_del->left == del_elem){parent_del->left = NULL;}
        else{parent_del->right = NULL;}
        free(del_elem);
    }

//2.1 Случай
    else if(del_elem->right == NULL && del_elem->left != NULL){
        if(parent_del->left == del_elem){parent_del->left = del_elem->left;}
        else{parent_del->right = del_elem->left;}
        del_elem->left->parent = parent_del;
        free(del_elem);
    }

//2.2 Случай
    else if(del_elem->right != NULL && del_elem->left == NULL){
        if(parent_del->left == del_elem){parent_del->left = del_elem->right;}
        else{parent_del->right = del_elem->right;}
        del_elem->right->parent = parent_del;
        free(del_elem);
    }

//3 Случай
    else if(del_elem->right != NULL && del_elem->left != NULL){
        Node* min_right = min(del_elem->right);
        min_right->parent->left = min_right->right;
        del_elem->left->parent = del_elem->right->parent = min_right;
        min_right->left = del_elem->left;
        min_right->right = del_elem->right;
        min_right->parent = parent_del;
        if(parent_del->left == del_elem){parent_del->left = min_right;}
        else{parent_del->right = min_right;}
        free(del_elem);
    }

    return root;
}

int main(void){
    char symb[2];
    int cur_key, N;
    Node* root = NULL;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%s", symb);
        scanf("%d", &cur_key);
        if (symb[0] == 'A'){
            root = add(root, cur_key);
        }
        else if(symb[0] == 'D'){
            root = delete(root, cur_key);
        }
        else if(symb[0] == 'S'){
            Node* ans_node = search(root, cur_key);

            if(ans_node != NULL){
                printf("%d", ans_node->key);
            }
            else{
                printf("Nope");
            }
        }
    }

    return 0;
}