#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double cheb_phi(int k, double x){
    switch (k)
    {
        case 0: return 1.0;
        case 1: return x;
        case 2: return 2.0*pow(x,2) - 1.0;
        case 3: return 4.0*pow(x,3) - 3.0*x;
        case 4: return 8.0*pow(x,4) - 8.0*pow(x,2) + 1.0;
        case 5: return 16.0*pow(x,5) - 20.0*pow(x,3) + 5.0*x;
        default:
            printf("Error: k must be 0..5\n");
            exit(1);
    }
}

static void SamplePoly(const int N, const int NumPts,
                       const double b[], const double x[],
                       double y[]){
    for (int i = 0; i < NumPts; i++)
    {
        double sum = 0.0;
        for (int k = 0; k <= N; k++)
        {
            sum += b[k] * cheb_phi(k, x[i]);
        }
        y[i] = sum;
    }
}

static void WritePoly(const int NumPts, const double x[], const double y[]){
    FILE *fid = fopen("poly.data", "w");
    if (!fid) {
        printf("Error: cannot open poly.data for writing.\n");
        exit(1);
    }

    for (int i = 0; i < NumPts; i++)
        fprintf(fid, "%.16e %.16e\n", x[i], y[i]);

    fclose(fid);
}

int main(){
    const int Nmax = 5;
    int N;

    printf("\n Input polynomial degree (0-%d): ", Nmax);
    if (scanf("%d", &N) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (N < 0 || N > Nmax)
    {
        printf(" Invalid value N = %d.\n", N);
        printf(" N must satisfy: 0 <= N <= %d\n\n", Nmax);
        return 1;
    }
    printf("\n");

    double b[Nmax + 1];
    for (int i = 0; i <= N; i++)
    {
        printf(" Set b[%d]: ", i);
        if (scanf("%lf", &b[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }
    printf("\n");

    // set x-coordinates in [-1,1]
    const int NumPts = 201;
    double x[NumPts];
    for (int i = 0; i < NumPts; i++)
        x[i] = -1.0 + i * (2.0 / (NumPts - 1.0));

    // compute and write y(x)
    double y[NumPts];
    SamplePoly(N, NumPts, b, x, y);
    WritePoly(NumPts, x, y);

    system("python3 PlotPoly.py");

    return 0;
}
