#include <math.h>
#include "quad.h"

static double dist(Point a, Point b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

double quad_perimeter(const Quadrilateral* q){
    double p = 0.0;
    p += dist(q->p[0], q->p[1]);
    p += dist(q->p[1], q->p[2]);
    p += dist(q->p[2], q->p[3]);
    p += dist(q->p[3], q->p[0]);
    return p;
}

