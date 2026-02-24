#include <stdio.h>
#include "poly.h"

int main(){
    term *A = NULL;
    term *B = NULL;

    //example 
    PolyAddTerm(&A,  3.0, 4);
    PolyAddTerm(&A, -2.0, 1);
    PolyAddTerm(&A,  7.0, 0);

    PolyAddTerm(&B, -1.0, 4);
    PolyAddTerm(&B,  5.0, 2);
    PolyAddTerm(&B,  2.0, 1);
    PolyAddTerm(&B, -9.0, 0);

    printf("A(x) = ");
    PolyPrint(A);
    printf("B(x) = ");
    PolyPrint(B);

    term *C = PolyAdd(A, B);
    printf("C(x) = A(x) + B(x) = ");
    PolyPrint(C);

    double x;
    printf("\nEnter x for evaluation: ");
    if (scanf("%lf", &x) != 1) {
        printf("Input error.\n");
        PolyFree(&A);
        PolyFree(&B);
        PolyFree(&C);
        return 1;
    }

    printf("A(%.6g) = %.10g\n", x, PolyEval(A, x));
    printf("B(%.6g) = %.10g\n", x, PolyEval(B, x));
    printf("C(%.6g) = %.10g\n", x, PolyEval(C, x));

    PolyFree(&A);
    PolyFree(&B);
    PolyFree(&C);
    return 0;
}