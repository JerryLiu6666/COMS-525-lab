#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

void usage(char *prog) {
    fprintf(stderr, "Usage: %s <thread_count> <N>\n", prog);
    fprintf(stderr, "  thread_count should be 1, 2, 4, or 8\n");
    fprintf(stderr, "  N should be > 2\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
    }

    int thread_count = atoi(argv[1]);
    int N = atoi(argv[2]);

    if (thread_count <= 0 || N <= 2) {
        usage(argv[0]);
    }

    srand((unsigned)time(NULL));

    int **img = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        img[i] = (int *)malloc(N * sizeof(int));
    }

    int M = N - 2;
    double **blur = (double **)malloc(M * sizeof(double *));
    for (int i = 0; i < M; i++) {
        blur[i] = (double *)malloc(M * sizeof(double));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            img[i][j] = rand() % 256;
        }
    }

    double start, end;

#ifdef _OPENMP
    start = omp_get_wtime();
#pragma omp parallel for num_threads(thread_count) collapse(2)
#endif
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            int sum = 0;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    sum += img[i + di][j + dj];
                }
            }

            blur[i - 1][j - 1] = sum / 9.0;
        }
    }

#ifdef _OPENMP
    end = omp_get_wtime();
#else
    start = 0.0;
    end = 0.0;
#endif

    printf("N = %d, threads = %d, walltime = %e seconds\n", N, thread_count, end - start);

    printf("Sample blurred values (first 5x5 block):\n");
    int limit = (M < 5) ? M : 5;
    for (int i = 0; i < limit; i++) {
        for (int j = 0; j < limit; j++) {
            printf("%8.2f ", blur[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        free(img[i]);
    }
    free(img);

    for (int i = 0; i < M; i++) {
        free(blur[i]);
    }
    free(blur);

    return 0;
}