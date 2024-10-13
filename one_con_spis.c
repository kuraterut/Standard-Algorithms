#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

int check_neg(Node* root){
    while(root != NULL){
        if(root->data < 0){
            return 1;
        }
        root = root->next;
    }
    return 0;
}

Node* ret_right_neg(Node* root_neg){
    Node* head_neg = root_neg;
    while(root_neg != NULL){
        if (root_neg->next != NULL) {
            if (root_neg->next->data >= 0) {
                root_neg->next = NULL;
            }
        }
        root_neg = root_neg->next;
    }

    return head_neg;
}

Node* ret_right_pos(Node* root_pos){
    Node* head_pos = root_pos;
    while(root_pos != NULL){
        if (root_pos->next != NULL) {
            if (root_pos->next->data < 0) {
                root_pos->next = NULL;
            }
        }
        root_pos = root_pos->next;
    }
    return head_pos;
}

Node* ret_connect(Node* pos_list, Node* neg_list){
    Node* head = pos_list;
    while(pos_list->next != NULL){
//        printf("debug ");
        pos_list = pos_list->next;
    }
    pos_list->next = neg_list;
    return head;
}

Node* min_node(Node* root){
    Node* min = root;

    while(root!=NULL){
        if(min->data > root->data){
            min = root;
        }
        root = root->next;
    }
    return min;
}

Node* all_pos_coonect(Node* pos, Node* last){
    Node* head = pos;
    while(pos->next!=NULL){
        pos = pos->next;
    }
    last->next = NULL;
    pos->next = last;
    return head;
}

Node* transform(Node *root){
    Node* head_neg = NULL;
    Node* head_pos = NULL;
    Node* cur_neg = NULL;
    Node* cur_pos = NULL;
    int flag_head_neg, flag_head_pos;
    flag_head_neg = flag_head_pos = 0;

    if (check_neg(root) == 1){
        while (root != NULL){

            if (root->data < 0){
                if (flag_head_neg == 0){
                    head_neg = root;
                    flag_head_neg = 1;
                    cur_neg = head_neg;

                }
                else{
                    cur_neg->next = root;
                    cur_neg = root;
                }
            }
            else{
                if (flag_head_pos == 0){
                    head_pos = root;
                    flag_head_pos = 1;
                    cur_pos = head_pos;
                }
                else{
                    cur_pos->next = root;
                    cur_pos = root;
                }
            }
            root = root->next;
        }
        head_neg = ret_right_neg(head_neg);
        head_pos = ret_right_pos(head_pos);
        return ret_connect(head_neg, head_pos);
    }
    else{
        head_neg = min_node(root);
        head_pos = root;
        cur_pos = root;
        while(cur_pos != NULL){
            if(cur_pos->next == head_neg){
                cur_pos->next = cur_pos->next->next;
                break;
            }
            cur_pos = cur_pos->next;
        }

        return all_pos_coonect(head_pos, head_neg);
    }
}

Node* add(Node* last_node, int data){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->next = NULL;
    tmp->data = data;
    last_node->next = tmp;
    return last_node;
}

Node* create_list(int data){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->next = NULL;
    tmp->data = data;
    return tmp;
}

int main(void){
    int N, cur_num;

    scanf("%d", &N);
    scanf("%d", &cur_num);

    Node* head = create_list(cur_num);
    Node* cur = head;
    for (int i = 0; i < N-1; i++){
        scanf("%d", &cur_num);
        cur = add(cur, cur_num);
        cur = cur->next;
    }
    head = transform(head);
    while(head!=NULL){
        printf("%d ", head->data);
        head = head->next;
    }
}

