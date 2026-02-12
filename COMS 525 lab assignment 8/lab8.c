#include <stdio.h>
#include <math.h>

double factorial(int n)
{
    if (n <= 1) {
        return 1.0;
    }
    return n * factorial(n - 1);
}


double myexp(double x)
{
    const double e = 2.718281828459;
    int x0 = (int)round(x);
    double r = x - (double)x0;

    int N = 25;
    double s = 0.0;

    for (int k = 0; k <= N; k++) {
        s += pow(r, k) / factorial(k);
    }

    return pow(e, x0) * s;
}

int main(void)
{
    FILE *fp = fopen("exp.data", "w");
    if (fp == NULL) {
        printf("Cannot open exp.data\n");
        return 1;
    }

    for (int i = 0; i <= 50; i++) {
        double x = 0.02 * i;
        double y = myexp(x);
        fprintf(fp, "%.2f  %.15f\n", x, y);
    }

    fclose(fp);
    printf("Done. Data written to exp.data\n");
    return 0;
}
