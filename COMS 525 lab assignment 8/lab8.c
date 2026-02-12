#include <stdio.h>
#include <math.h>

// recursive factorial function (like lecture example)
unsigned long long factorial(int n)
{
    if (n <= 1) {
        return 1ULL;              // base case
    } else {
        return (unsigned long long)n * factorial(n - 1);
    }
}

// exp(x) by Taylor expansion around x0 = round(x)
// exp(x) = e^(x0) * exp(r), where r = x - x0 (small)
// exp(r) ~= sum_{k=0}^N r^k / k!
double myexp(double x)
{
    const double e = 2.718281828459;   // given constant in the assignment
    int x0 = (int)round(x);            // closest integer
    double r = x - (double)x0;

    // Taylor series for exp(r)
    // N can be ~20-30 for good accuracy when |r| <= 0.5
    const int N = 25;
    double s = 0.0;

    for (int k = 0; k <= N; k++) {
        double term = pow(r, (double)k) / (double)factorial(k);
        s += term;
    }

    // e^(x0) * exp(r)
    return pow(e, (double)x0) * s;
}

int main(void)
{
    // create an output file (like the lecture file I/O example)
    FILE *outfile = fopen("exp.data", "w");
    if (outfile == NULL) {
        printf("Error: cannot open exp.data for writing.\n");
        return 1;
    }

    // x = 0, 0.02, ..., 1
    for (int i = 0; i <= 50; i++) {
        double x = 0.02 * (double)i;
        double y = myexp(x);

        // two columns: x  exp(x)
        fprintf(outfile, "%23.16e  %23.16e\n", x, y);
    }

    fclose(outfile);

    printf("Done. Data written to exp.data\n");
    return 0;
}
