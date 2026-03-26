#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double pdf(double S, double S0, double r, double sigma, double T) {
    double mu = log(S0) + (r - 0.5 * sigma * sigma) * T;
    double denom = S * sigma * sqrt(2 * M_PI * T);
    double exponent = -pow(log(S) - mu, 2) / (2 * sigma * sigma * T);
    return exp(exponent) / denom;
}

double integrand(double S, double K, double S0, double r, double sigma, double T) {
    if (S < K) return 0.0;
    return (S - K) * pdf(S, S0, r, sigma, T);
}

double simpson_parallel(double a, double b, int N,
                        double K, double S0, double r, double sigma, double T,
                        int threads) {

    double h = (b - a) / N;
    double sum = 0.0;

    #pragma omp parallel for num_threads(threads) reduction(+:sum)
    for (int i = 0; i <= N; i++) {
        double S = a + i * h;
        double fx = integrand(S, K, S0, r, sigma, T);

        if (i == 0 || i == N)
            sum += fx;
        else if (i % 2 == 0)
            sum += 2 * fx;
        else
            sum += 4 * fx;
    }

    return (h / 3.0) * sum;
}

double normal_cdf(double x) {
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

double black_scholes(double S0, double K, double r, double sigma, double T) {
    double d1 = (log(S0/K) + (r + 0.5*sigma*sigma)*T) / (sigma*sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    return S0 * normal_cdf(d1) - K * exp(-r*T) * normal_cdf(d2);
}

int main() {

    double S0 = 100;
    double K = 100;
    double r = 0.05;
    double T = 1.0;
    double sigma = 0.2;

    double Smax = 5 * S0;   
    int N = 10000000;       

    int thread_list[5] = {1, 2, 4, 8, 16};

    printf("Threads\tSimpson Price\tTime\n");

    for (int t = 0; t < 5; t++) {
        int threads = thread_list[t];

        double start = omp_get_wtime();

        double integral = simpson_parallel(K, Smax, N,
                            K, S0, r, sigma, T, threads);

        double price = exp(-r * T) * integral;

        double end = omp_get_wtime();

        printf("%d\t%.6f\t%.6f sec\n", threads, price, end - start);
    }

    double exact = black_scholes(S0, K, r, sigma, T);
    printf("\nBlack-Scholes Exact: %.6f\n", exact);

    return 0;
}