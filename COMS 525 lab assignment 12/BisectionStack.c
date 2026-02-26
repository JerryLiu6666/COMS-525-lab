#include <math.h>
#include "node.h"

//example
double f(int func_id, double x){
    switch (func_id) {
        case 1: 
            return x*x*x - x - 2.0;
        case 2: 
            return cos(x) - x;
        default:
            return x*x*x - x - 2.0;
    }
}

int BisectionWithStack(int func_id,
                       double a0, double b0,
                       double tol_x, double tol_f,
                       int max_level,
                       double roots[], int max_roots){
    node *top = NULL;
    int nroots = 0;

    double fa0 = f(func_id, a0);
    double fb0 = f(func_id, b0);

    PushInterval(a0, b0, fa0, fb0, 0, &top);

    while (top != NULL) {
        double a, b, fa, fb;
        int level;
        PopInterval(&top, &a, &b, &fa, &fb, &level);

        if (fa * fb > 0.0) continue;

        double mid = 0.5 * (a + b);
        double fm  = f(func_id, mid);

        if (fabs(b - a) < tol_x || fabs(fm) < tol_f || level >= max_level) {
            if (nroots < max_roots) roots[nroots++] = mid;
            continue;
        }

        double a1 = a, b1 = mid, fa1 = fa, fb1 = fm;
        double a2 = mid, b2 = b, fa2 = fm, fb2 = fb;

        if (fa2 * fb2 <= 0.0) PushInterval(a2, b2, fa2, fb2, level + 1, &top);
        if (fa1 * fb1 <= 0.0) PushInterval(a1, b1, fa1, fb1, level + 1, &top);
    }

    DeleteStack(&top);
    return nroots;
}
