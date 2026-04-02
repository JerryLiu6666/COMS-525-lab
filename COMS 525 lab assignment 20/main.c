#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double simpson_rule(double (*f)(double, void *), double a, double b, void *params) {
    double c = 0.5 * (a + b);
    return (b - a) * (f(a, params) + 4.0 * f(c, params) + f(b, params)) / 6.0;
}

double adaptive_simpson(double (*f)(double, void *), double a, double b, double tol, void *params) {
    double qab = simpson_rule(f, a, b, params);
    double c = 0.5 * (a + b);
    double qac = simpson_rule(f, a, c, params);
    double qcb = simpson_rule(f, c, b, params);

    double err = fabs(qac + qcb - qab) / 15.0;

    if (err < tol) {
        return qac + qcb;
    } else {
        return adaptive_simpson(f, a, c, 0.5 * tol, params) +
               adaptive_simpson(f, c, b, 0.5 * tol, params);
    }
}

typedef struct {
    double x0;
} VParams;

double rho(double x) {
    return exp(-x * x);
}

double integrand_V(double x, void *params) {
    VParams *p = (VParams *)params;
    double x0 = p->x0;

    if (fabs(x - x0) < 1e-12) {
        return -2.0 * x0 * exp(-x0 * x0);
    }

    return (rho(x) - rho(x0)) / fabs(x - x0);
}

double compute_V(double x0, double tol) {
    VParams p;
    p.x0 = x0;

    double a = -1.0, b = 1.0;
    double integral = adaptive_simpson(integrand_V, a, b, tol, &p);
    double logterm = rho(x0) * log((b - x0) / (x0 - a));

    return integral + logterm;
}

typedef struct {
    double x;
} J0Params;

double integrand_J0(double theta, void *params) {
    J0Params *p = (J0Params *)params;
    return cos(p->x * sin(theta));
}

double compute_J0(double x, double tol) {
    J0Params p;
    p.x = x;
    return adaptive_simpson(integrand_J0, 0.0, M_PI, tol, &p) / M_PI;
}

int main() {
    const double tol = 1.0e-8;

    FILE *f1 = fopen("potential.data", "w");
    if (!f1) {
        printf("Cannot open potential.data\n");
        return 1;
    }

    int n1 = 200;
    for (int i = 1; i < n1; i++) {
        double x0 = -1.0 + 2.0 * i / (double)n1;

        if (x0 <= -1.0 + 1e-12 || x0 >= 1.0 - 1e-12) continue;

        double V = compute_V(x0, tol);
        fprintf(f1, "%.12f %.12f\n", x0, V);
    }
    fclose(f1);

    FILE *f2 = fopen("bessel.data", "w");
    if (!f2) {
        printf("Cannot open bessel.data\n");
        return 1;
    }

    int n2 = 500;
    for (int i = 0; i <= n2; i++) {
        double x = 50.0 * i / (double)n2;
        double j0 = compute_J0(x, tol);
        fprintf(f2, "%.12f %.12f\n", x, j0);
    }
    fclose(f2);

    printf("Done.\n");
    printf("Generated potential.data and bessel.data\n");

    return 0;
}