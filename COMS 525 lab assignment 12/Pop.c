#include <stdlib.h>
#include "node.h"

void PopInterval(node **top, double *a, double *b, double *fa, double *fb, int *level){
    if (*top == NULL) return;

    node *temp = *top;
    *a = temp->a;
    *b = temp->b;
    *fa = temp->fa;
    *fb = temp->fb;
    *level = temp->level;

    *top = temp->next;
    free(temp);
}