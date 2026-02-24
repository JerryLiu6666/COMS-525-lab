#ifndef __POLY_H__
#define __POLY_H__

typedef struct term term;

struct term {
    int exp;        
    double coef;    
    term *next;
};

void PolyAddTerm(term **head, double coef, int exp);     
term* PolyAdd(const term *A, const term *B);             

double PolyEval(const term *head, double x);
void PolyPrint(const term *head);

void PolyFree(term **head);

#endif