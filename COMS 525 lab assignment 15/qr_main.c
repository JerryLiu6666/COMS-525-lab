#include <stdio.h>
#include "matrix.h"
#include "trimatrix.h"

void Hessenberg(const matrix* A, trimatrix* T);
void QRA(trimatrix* T);

matrix build_A(int n){
    matrix A = new_matrix(n, n);

    for (int i = 1; i <= n; i++){
        mget(A, i, i) = 2.0 / 4.0;

        if (i > 1)
            mget(A, i, i - 1) = 1.0 / 4.0;

        if (i < n)
            mget(A, i, i + 1) = 1.0 / 4.0;
    }

    return A;
}

int main(void){
    int ns[2] = {6, 12};

    for (int k = 0; k < 2; k++){
        int n = ns[k];
        printf("\n========== n = %d ==========\n", n);

        matrix A = build_A(n);
        trimatrix T = new_trimatrix(n);

        Hessenberg(&A, &T);
        QRA(&T);

        printf("Eigenvalues:\n");
        for (int i = 1; i <= n; i++){
            printf("%f\n", tget(&T, i, i));
        }

        delete_trimatrix(&T);
        delete_matrix(&A);
    }

    return 0;
}
