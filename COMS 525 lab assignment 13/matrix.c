#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

matrix new_matrix(const int rows, const int cols){
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    assert(rows > 0);
    assert(cols > 0);

    mat.val = (double*)malloc(sizeof(double) * (size_t)rows * (size_t)cols);
    assert(mat.val != NULL);

    for (int i = 0; i < rows * cols; i++) mat.val[i] = 0.0;
    return mat;
}

vector new_vector(const int size){
    vector vec;
    vec.size = size;
    assert(size > 0);

    vec.val = (double*)malloc(sizeof(double) * (size_t)size);
    assert(vec.val != NULL);

    for (int i = 0; i < size; i++) vec.val[i] = 0.0;
    return vec;
}

void free_matrix(matrix* mat){
    if (!mat) return;
    free(mat->val);
    mat->val = NULL;
    mat->rows = 0;
    mat->cols = 0;
}

void free_vector(vector* vec){
    if (!vec) return;
    free(vec->val);
    vec->val = NULL;
    vec->size = 0;
}

void print_matrix_full(const matrix* mat, char* varname){
    assert(mat->rows > 0 && mat->cols > 0);
    printf("\n %.100s =\n", &varname[1]);
    for (int i = 1; i <= mat->rows; i++) {
        printf(" | ");
        for (int j = 1; j <= mat->cols; j++) {
            printf("%10.3e", mgetp(mat, i, j));
            if (j < mat->cols) printf(", ");
            else printf(" ");
        }
        printf("|\n");
    }
    printf("\n");
}

void print_vector_full(const vector* vec, char* varname){
    assert(vec->size > 0);
    printf("\n %.100s =\n", &varname[1]);
    printf(" | ");
    for (int i = 1; i <= vec->size; i++) {
        printf("%10.3e", vgetp(vec, i));
        if (i < vec->size) printf(", ");
    }
    printf(" |^T\n\n");
}

void print_scalar_full(const double* z, char* varname){
    printf("\n %.100s =\n", &varname[1]);
    printf(" %10.3e \n\n", *z);
}

matrix matrix_add(const matrix* A, const matrix* B){
    assert(A->rows == B->rows && A->cols == B->cols);
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(C, i, j) = mgetp(A, i, j) + mgetp(B, i, j);
    return C;
}

matrix matrix_sub(const matrix* A, const matrix* B){
    assert(A->rows == B->rows && A->cols == B->cols);
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(C, i, j) = mgetp(A, i, j) - mgetp(B, i, j);
    return C;
}

matrix matrix_mult(const matrix* A, const matrix* B){
    assert(A->cols == B->rows);
    matrix C = new_matrix(A->rows, B->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= B->cols; j++)
            for (int k = 1; k <= A->cols; k++)
                mget(C, i, j) += mgetp(A, i, k) * mgetp(B, k, j);
    return C;
}

matrix matrix_dot_mult(const matrix* A, const matrix* B){
    assert(A->rows == B->rows && A->cols == B->cols);
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(C, i, j) = mgetp(A, i, j) * mgetp(B, i, j);
    return C;
}

vector vector_add(const vector* x, const vector* y){
    assert(x->size == y->size);
    vector z = new_vector(x->size);
    for (int i = 1; i <= x->size; i++) vget(z, i) = vgetp(x, i) + vgetp(y, i);
    return z;
}

vector vector_sub(const vector* x, const vector* y){
    assert(x->size == y->size);
    vector z = new_vector(x->size);
    for (int i = 1; i <= x->size; i++) vget(z, i) = vgetp(x, i) - vgetp(y, i);
    return z;
}

double vector_dot_mult(const vector* x, const vector* y){
    assert(x->size == y->size);
    double z = 0.0;
    for (int i = 1; i <= x->size; i++) z += vgetp(x, i) * vgetp(y, i);
    return z;
}

vector matrix_vector_mult(const matrix* A, const vector* x){
    assert(A->cols == x->size);
    vector Ax = new_vector(A->rows);
    for (int i = 1; i <= A->rows; i++) {
        double tmp = 0.0;
        for (int j = 1; j <= x->size; j++) tmp += mgetp(A, i, j) * vgetp(x, j);
        vget(Ax, i) = tmp;
    }
    return Ax;
}

matrix matrix_copy(const matrix* A){
    matrix C = new_matrix(A->rows, A->cols);
    for (int i = 0; i < A->rows * A->cols; i++) C.val[i] = A->val[i];
    return C;
}

vector vector_copy(const vector* b){
    vector c = new_vector(b->size);
    for (int i = 0; i < b->size; i++) c.val[i] = b->val[i];
    return c;
}

matrix matrix_transpose(const matrix* A){
    matrix AT = new_matrix(A->cols, A->rows);
    for (int i = 1; i <= A->rows; i++)
        for (int j = 1; j <= A->cols; j++)
            mget(AT, j, i) = mgetp(A, i, j);
    return AT;
}

double vector_norm2(const vector* x){
    double s = 0.0;
    for (int i = 1; i <= x->size; i++) s += vgetp(x, i) * vgetp(x, i);
    return sqrt(s);
}

vector solve(matrix* A, vector* b){
    const int n = A->rows;
    assert(A->rows == A->cols);
    assert(b->size == n);

    vector x = new_vector(n);

    for (int i = 1; i <= n - 1; i++) {
        int p = i;
        double maxA = 0.0;
        for (int j = i; j <= n; j++) {
            double tmp = fabs(mgetp(A, j, i));
            if (tmp > maxA) { maxA = tmp; p = j; }
        }
        if (maxA <= 1.0e-14) {
            printf("Cannot invert system (singular)\n");
            exit(1);
        }

        if (p != i) {
            for (int j = 1; j <= n; j++) {
                double t = mgetp(A, i, j);
                mgetp(A, i, j) = mgetp(A, p, j);
                mgetp(A, p, j) = t;
            }
            double tb = vgetp(b, i);
            vgetp(b, i) = vgetp(b, p);
            vgetp(b, p) = tb;
        }

        for (int j = i + 1; j <= n; j++) {
            double dm = mgetp(A, j, i) / mgetp(A, i, i);
            for (int k = 1; k <= n; k++)
                mgetp(A, j, k) = mgetp(A, j, k) - dm * mgetp(A, i, k);
            vgetp(b, j) = vgetp(b, j) - dm * vgetp(b, i);
        }
    }

    vget(x, n) = vgetp(b, n) / mgetp(A, n, n);
    for (int j = 1; j <= n - 1; j++) {
        double sum = 0.0;
        for (int k = (n - j + 1); k <= n; k++)
            sum += mgetp(A, n - j, k) * vget(x, k);
        vget(x, n - j) = (vgetp(b, n - j) - sum) / mgetp(A, n - j, n - j);
    }

    return x;
}