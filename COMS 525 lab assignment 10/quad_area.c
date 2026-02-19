#include <math.h>
#include "quad.h"

double quad_area(const Quadrilateral* q){
    double s = 0.0;
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
        s += q->p[i].x * q->p[j].y - q->p[j].x * q->p[i].y;
    }
    return 0.5 * fabs(s);
}
