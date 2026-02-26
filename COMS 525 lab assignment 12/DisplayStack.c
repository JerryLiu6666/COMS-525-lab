#include <stdio.h>
#include "node.h"

static void PrintNode(node* top){
    printf(" |%3d |%12.6f |%12.6f |%12.3e |%12.3e |\n",
           top->level, top->a, top->b, top->fa, top->fb);
    if (top->next == NULL) return;
    PrintNode(top->next);
}

void DisplayStack(node* top){
    if (top == NULL) {
        printf(" Stack is empty.\n");
        return;
    }

    printf(" ---------------------------------------------------------------\n");
    printf(" |Lvl|      a      |      b      |    f(a)    |    f(b)    |\n");
    printf(" ---------------------------------------------------------------\n");
    PrintNode(top);
    printf(" ---------------------------------------------------------------\n");
}