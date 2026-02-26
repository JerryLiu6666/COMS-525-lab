#ifndef __NODE_H__
#define __NODE_H__

#include <stddef.h>


typedef struct node node;
struct node{
    double a, b;       
    double fa, fb;     
    int level;         
    node* next;
};

void PushInterval(double a, double b, double fa, double fb, int level, node **top);
void PopInterval(node **top, double *a, double *b, double *fa, double *fb, int *level);
double PeekLeft(node* top); // just for demo (peek a)
void GetStackSize(node* top, int *stack_size);
void DisplayStack(node* top);
void DeleteStack(node **top);

double f(int func_id, double x);
int BisectionWithStack(int func_id,
                       double a0, double b0,
                       double tol_x, double tol_f,
                       int max_level,
                       double roots[], int max_roots);

#endif