#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "poly.h"

static term* NewTerm(double coef, int exp){
    term *t = (term*)malloc(sizeof(term));
    if (!t) {
        printf("Error: malloc failed.\n");
        exit(1);
    }
    t->coef = coef;
    t->exp  = exp;
    t->next = NULL;
    return t;
}

void PolyAddTerm(term **head, double coef, int exp){
    if (coef == 0.0) return;

    if (*head == NULL || (*head)->exp < exp) {
        term *t = NewTerm(coef, exp);
        t->next = *head;
        *head = t;
        return;
    }

    term *prev = NULL;
    term *cur  = *head;

    while (cur != NULL && cur->exp > exp) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != NULL && cur->exp == exp) {
        cur->coef += coef;
        if (fabs(cur->coef) < 1e-12) {
            if (prev == NULL) {
                *head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
        }
        return;
    }

    term *t = NewTerm(coef, exp);
    prev->next = t;
    t->next = cur;
}

term* PolyAdd(const term *A, const term *B){
    term *C = NULL;

    const term *pa = A;
    const term *pb = B;

    while (pa != NULL) {
        PolyAddTerm(&C, pa->coef, pa->exp);
        pa = pa->next;
    }
    while (pb != NULL) {
        PolyAddTerm(&C, pb->coef, pb->exp);
        pb = pb->next;
    }
    return C;
}

double PolyEval(const term *head, double x){
    double sum = 0.0;
    const term *p = head;
    while (p != NULL) {
        sum += p->coef * pow(x, p->exp);
        p = p->next;
    }
    return sum;
}

void PolyPrint(const term *head){
    if (head == NULL) {
        printf("0\n");
        return;
    }

    const term *p = head;
    int first = 1;

    while (p != NULL) {
        double c = p->coef;
        int e = p->exp;

        if (!first) {
            if (c >= 0) printf(" + ");
            else { printf(" - "); c = -c; }
        } else {
            if (c < 0) { printf("-"); c = -c; }
            first = 0;
        }

        if (e == 0) {
            printf("%.6g", c);
        } else if (e == 1) {
            if (fabs(c - 1.0) < 1e-12) printf("x");
            else printf("%.6g*x", c);
        } else {
            if (fabs(c - 1.0) < 1e-12) printf("x^%d", e);
            else printf("%.6g*x^%d", c, e);
        }

        p = p->next;
    }
    printf("\n");
}

void PolyFree(term **head){
    term *cur = *head;
    while (cur != NULL) {
        term *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
}