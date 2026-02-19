#include <math.h>
#include "quad.h"

static double dot2(double ax, double ay, double bx, double by){
    return ax*bx + ay*by;
}

static double norm2(double ax, double ay){
    return sqrt(ax*ax + ay*ay);
}

void quad_angles(const Quadrilateral* q, double angles_out[4]){
    const double PI = 3.14159265358979323846;

    for (int i = 0; i < 4; i++) {
        int iprev = (i + 3) % 4;   // i-1
        int inext = (i + 1) % 4;   // i+1

        double ux = q->p[iprev].x - q->p[i].x;
        double uy = q->p[iprev].y - q->p[i].y;
        double vx = q->p[inext].x - q->p[i].x;
        double vy = q->p[inext].y - q->p[i].y;

        double nu = norm2(ux, uy);
        double nv = norm2(vx, vy);

        if (nu < 1e-12 || nv < 1e-12) {
            angles_out[i] = 0.0;
            continue;
        }

        double c = dot2(ux, uy, vx, vy) / (nu * nv);

        if (c > 1.0) c = 1.0;
        if (c < -1.0) c = -1.0;

        double theta = acos(c);              // radians
        angles_out[i] = theta * 180.0 / PI;  // degrees
    }
}
