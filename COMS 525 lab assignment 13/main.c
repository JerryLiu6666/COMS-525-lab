#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

static double urand01(void){
    return (rand() + 1.0) / (RAND_MAX + 2.0);
}

static double grand01(void){
    double u1 = urand01();
    double u2 = urand01();
    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

static matrix build_blur_A(int n){
    matrix A = new_matrix(n, n);
    for (int i = 1; i <= n; i++) {
        mget(A, i, i) = 2.0 / 4.0;
        if (i > 1) mget(A, i, i - 1) = 1.0 / 4.0;
        if (i < n) mget(A, i, i + 1) = 1.0 / 4.0;
    }
    return A;
}

static vector build_test_x(int n){
    vector x = new_vector(n);
    int i1 = n / 4;     
    int i2 = n / 2;     
    for (int i = 1; i <= n; i++) {
        if (i >= i1 && i <= i2) vget(x, i) = 1.0;
        else vget(x, i) = 0.0;
    }
    return x;
}

static double rel_error(const vector* x_true, const vector* x_rec){
    vector diff = vector_sub(x_true, x_rec);
    double num = vector_norm2(&diff);
    double den = vector_norm2(x_true);
    free_vector(&diff);
    return num / den;
}

static vector add_noise(const vector* b, double sigma){
    vector y = vector_copy(b);
    for (int i = 1; i <= y.size; i++) {
        vget(y, i) += sigma * grand01();
    }
    return y;
}

// Solve Ax = b 
static vector solve_linear_system(const matrix* A, const vector* b){
    matrix Ac = matrix_copy(A);
    vector bc = vector_copy(b);
    vector x = solve(&Ac, &bc);
    free_matrix(&Ac);
    free_vector(&bc);
    return x;
}

static vector solve_tikhonov(const matrix* A, const vector* b, double lambda){
    matrix AT = matrix_transpose(A);
    matrix ATA = matrix_mult(&AT, A);

    matrix M = matrix_copy(&ATA);
    for (int i = 1; i <= M.rows; i++) mget(M, i, i) += lambda;

    vector rhs = matrix_vector_mult(&AT, b);
    
    vector x = solve_linear_system(&M, &rhs);

    free_matrix(&AT);
    free_matrix(&ATA);
    free_matrix(&M);
    free_vector(&rhs);
    return x;
}

int main(void){
    srand((unsigned)time(NULL));

    int ns[2] = {64, 128};
    double sigmas[3] = {1e-6, 1e-4, 1e-2};
    double lambdas[3] = {1e-6, 1e-4, 1e-2};

    for (int ni = 0; ni < 2; ni++) {
        int n = ns[ni];
        printf("========== n = %d ==========\n", n);

        matrix A = build_blur_A(n);
        vector x = build_test_x(n);
        vector b = matrix_vector_mult(&A, &x);  

        for (int si = 0; si < 3; si++) {
            double sigma = sigmas[si];
            vector b_noisy = add_noise(&b, sigma);

            vector x_rec = solve_linear_system(&A, &b_noisy);
            double e_direct = rel_error(&x, &x_rec);

            printf("[Direct] sigma = %.0e, relerr = %.6e\n", sigma, e_direct);

            for (int li = 0; li < 3; li++) {
                double lambda = lambdas[li];
                vector x_reg = solve_tikhonov(&A, &b_noisy, lambda);
                double e_reg = rel_error(&x, &x_reg);
                printf("  [Tikh]  lambda = %.0e, relerr = %.6e\n", lambda, e_reg);
                free_vector(&x_reg);
            }

            free_vector(&x_rec);
            free_vector(&b_noisy);
        }

        free_matrix(&A);
        free_vector(&x);
        free_vector(&b);

        printf("\n");
    }

    return 0;
}
