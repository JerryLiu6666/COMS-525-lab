#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

// Same A as my last lab 
static matrix build_A(int n){
    matrix A = new_matrix(n, n);
    for (int i = 1; i <= n; i++) {
        mget(A, i, i) = 2.0 / 4.0;
        if (i > 1) mget(A, i, i - 1) = 1.0 / 4.0;
        if (i < n) mget(A, i, i + 1) = 1.0 / 4.0;
    }
    return A;
}

static vector rand_v0(int n){
    vector v = new_vector(n);
    for (int i = 1; i <= n; i++) {
        vget(v, i) = (rand() + 1.0) / (RAND_MAX + 2.0);  // (0,1)
    }
    return v;
}

int main(void){
    srand((unsigned)time(NULL));

    const double TOL = 1e-12;
    const int MaxIters = 5000;

    int ns[2] = {5, 10};

    for (int t = 0; t < 2; t++) {
        int n = ns[t];
        printf("========== n = %d ==========\n", n);

        matrix A = build_A(n);

        // Power Iteration
        vector vP = rand_v0(n);
        double lamP = PowerIteration(&A, &vP, TOL, MaxIters);
        printf("PowerIteration:            lambda = %.15e\n", lamP);
        free_vector(&vP);

        // Shifted Inverse Iteration (mu = 0)
        vector v0 = rand_v0(n);
        double lam0 = ShiftedInverseIteration(&A, &v0, 0.0, TOL, MaxIters);
        printf("ShiftedInverseIteration:   mu=0   lambda = %.15e\n", lam0);
        free_vector(&v0);

        // Shifted Inverse Iteration (mu = 2)
        vector v2 = rand_v0(n);
        double lam2 = ShiftedInverseIteration(&A, &v2, 2.0, TOL, MaxIters);
        printf("ShiftedInverseIteration:   mu=2   lambda = %.15e\n", lam2);
        free_vector(&v2);

        // Rayleigh Quotient Iteration
        vector vR = rand_v0(n);
        double lamR = RayleighQuotientIteration(&A, &vR, TOL, 200);
        printf("RayleighQuotientIteration:        lambda = %.15e\n", lamR);
        free_vector(&vR);

        free_matrix(&A);
        printf("\n");
    }

    return 0;
}