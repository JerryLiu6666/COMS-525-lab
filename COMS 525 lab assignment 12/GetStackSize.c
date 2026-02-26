#include "node.h"

void GetStackSize(node* top, int *stack_size){
    int count = 0;
    node *p = top;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    *stack_size = count;
}