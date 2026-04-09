#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long long N = 10000000;
    long long count = 0;

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();

        #pragma omp for reduction(+:count)
        for (long long i = 0; i < N; i++) {
            double x = rand_r(&seed) / (double)RAND_MAX;
            double y = rand_r(&seed) / (double)RAND_MAX;

            if (x*x + y*y <= 1.0)
                count++;
        }
    }

    double pi = 4.0 * count / N;
    printf("OpenMP PI = %f\n", pi);

    return 0;
}