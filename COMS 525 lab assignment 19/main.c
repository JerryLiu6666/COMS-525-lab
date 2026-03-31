#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#ifndef N
#define N 100000000
#endif

void init_signal(double *x, long long n)
{
    #pragma omp parallel for
    for (long long i = 0; i < n; i++)
    {
       
        x[i] = sin(0.00001 * i) + cos(0.00002 * i) + 2.0;
    }
}

void normalize_2norm_fine(double *x, long long n, int thread_count)
{
    double sumsq = 0.0;

    #pragma omp parallel for num_threads(thread_count) reduction(+:sumsq)
    for (long long i = 0; i < n; i++)
    {
        sumsq += x[i] * x[i];
    }

    double norm2 = sqrt(sumsq);

    #pragma omp parallel for num_threads(thread_count)
    for (long long i = 0; i < n; i++)
    {
        x[i] /= norm2;
    }
}


void normalize_maxnorm_fine(double *x, long long n, int thread_count)
{
    double maxval = 0.0;

    #pragma omp parallel for num_threads(thread_count) reduction(max:maxval)
    for (long long i = 0; i < n; i++)
    {
        double temp = fabs(x[i]);
        if (temp > maxval)
            maxval = temp;
    }

    #pragma omp parallel for num_threads(thread_count)
    for (long long i = 0; i < n; i++)
    {
        x[i] /= maxval;
    }
}


void normalize_2norm_coarse(double *x, long long n, int thread_count)
{
    double sumsq = 0.0;

    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank = omp_get_thread_num();
        long long chunk = n / thread_count;
        long long start = my_rank * chunk;
        long long end = (my_rank == thread_count - 1) ? n : start + chunk;

        double local_sum = 0.0;
        for (long long i = start; i < end; i++)
        {
            local_sum += x[i] * x[i];
        }

        #pragma omp critical
        {
            sumsq += local_sum;
        }

        #pragma omp barrier

        double norm2 = sqrt(sumsq);

        for (long long i = start; i < end; i++)
        {
            x[i] /= norm2;
        }
    }
}

void normalize_maxnorm_coarse(double *x, long long n, int thread_count)
{
    double maxval = 0.0;

    #pragma omp parallel num_threads(thread_count)
    {
        int my_rank = omp_get_thread_num();
        long long chunk = n / thread_count;
        long long start = my_rank * chunk;
        long long end = (my_rank == thread_count - 1) ? n : start + chunk;

        double local_max = 0.0;
        for (long long i = start; i < end; i++)
        {
            double temp = fabs(x[i]);
            if (temp > local_max)
                local_max = temp;
        }

        #pragma omp critical
        {
            if (local_max > maxval)
                maxval = local_max;
        }

        #pragma omp barrier

        for (long long i = start; i < end; i++)
        {
            x[i] /= maxval;
        }
    }
}

int main()
{
    long long n = N;
    int thread_list[5] = {1, 2, 4, 8, 16};

    double *x = (double *) malloc(n * sizeof(double));
    if (x == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("N = %lld\n\n", n);

    printf("==== Fine-grained 2-norm ====\n");
    for (int k = 0; k < 5; k++)
    {
        int threads = thread_list[k];
        init_signal(x, n);

        double t1 = omp_get_wtime();
        normalize_2norm_fine(x, n, threads);
        double t2 = omp_get_wtime();

        printf("Threads = %2d, Time = %.6f sec\n", threads, t2 - t1);
    }

    printf("\n==== Fine-grained max norm ====\n");
    for (int k = 0; k < 5; k++)
    {
        int threads = thread_list[k];
        init_signal(x, n);

        double t1 = omp_get_wtime();
        normalize_maxnorm_fine(x, n, threads);
        double t2 = omp_get_wtime();

        printf("Threads = %2d, Time = %.6f sec\n", threads, t2 - t1);
    }

    printf("\n==== Coarse-grained 2-norm ====\n");
    for (int k = 0; k < 5; k++)
    {
        int threads = thread_list[k];
        init_signal(x, n);

        double t1 = omp_get_wtime();
        normalize_2norm_coarse(x, n, threads);
        double t2 = omp_get_wtime();

        printf("Threads = %2d, Time = %.6f sec\n", threads, t2 - t1);
    }

    printf("\n==== Coarse-grained max norm ====\n");
    for (int k = 0; k < 5; k++)
    {
        int threads = thread_list[k];
        init_signal(x, n);

        double t1 = omp_get_wtime();
        normalize_maxnorm_coarse(x, n, threads);
        double t2 = omp_get_wtime();

        printf("Threads = %2d, Time = %.6f sec\n", threads, t2 - t1);
    }

    free(x);
    return 0;
}