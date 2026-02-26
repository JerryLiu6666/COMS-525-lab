#include <stdio.h>
#include <math.h>
#include "node.h"

int main(){
    int func_id;
    double a, b, tol_x, tol_f;
    int max_level;

    printf("Choose function:\n");
    printf(" 1) f(x) = x^3 - x - 2\n");
    printf(" 2) f(x) = cos(x) - x\n");
    printf("Enter func_id: ");
    if (scanf("%d", &func_id) != 1) return 1;

    printf("Enter interval [a b]: ");
    if (scanf("%lf %lf", &a, &b) != 2) return 1;

    printf("Enter tol_x (e.g. 1e-6): ");
    if (scanf("%lf", &tol_x) != 1) return 1;

    printf("Enter tol_f (e.g. 1e-10): ");
    if (scanf("%lf", &tol_f) != 1) return 1;

    printf("Enter max_level (e.g. 60): ");
    if (scanf("%d", &max_level) != 1) return 1;

    double roots[100];
    int n = BisectionWithStack(func_id, a, b, tol_x, tol_f, max_level, roots, 100);

    printf("\nResults:\n");
    printf("f(a)=%.6e, f(b)=%.6e\n", f(func_id, a), f(func_id, b));
    printf("Found %d root candidate(s):\n", n);
    for (int i = 0; i < n; i++) {
        double r = roots[i];
        printf(" root[%d] = %.12f, f(root)=%.6e\n", i, r, f(func_id, r));
    }

    if (n == 0) {
        printf("No root found (or no sign-change subintervals).\n");
        printf("Tip: choose [a,b] such that f(a)*f(b) <= 0.\n");
    }

    return 0;
}