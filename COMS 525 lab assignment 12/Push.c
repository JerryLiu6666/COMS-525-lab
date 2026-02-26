#include <stdlib.h>
#include "node.h"

void PushInterval(double a, double b, double fa, double fb, int level, node **top){
    node *temp = (node*)malloc(sizeof(struct node));
    temp->a = a;
    temp->b = b;
    temp->fa = fa;
    temp->fb = fb;
    temp->level = level;

    temp->next = *top;
    *top = temp;
}
