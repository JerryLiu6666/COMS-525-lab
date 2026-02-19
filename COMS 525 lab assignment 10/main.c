#include <stdio.h>
#include "quad.h"

int main(void){
    Quadrilateral q;

    printf("Enter 4 vertices (x y) in order around the quadrilateral:\n");
    for (int i = 0; i < 4; i++) {
        printf("p%d (x y): ", i);
        if (scanf("%lf %lf", &q.p[i].x, &q.p[i].y) != 2) {
            printf("Input error.\n");
            return 1;
        }
    }

    q.perimeter = quad_perimeter(&q);
    q.area      = quad_area(&q);
    quad_angles(&q, q.angles);

    printf("\nQuadrilateral info:\n");
    for (int i = 0; i < 4; i++) {
        printf("p%d = (%.6f, %.6f)\n", i, q.p[i].x, q.p[i].y);
    }

    printf("\nPerimeter = %.10f\n", q.perimeter);
    printf("Area      = %.10f\n", q.area);

    printf("\nInner angles (degrees):\n");
    for (int i = 0; i < 4; i++) {
        printf("angle at p%d = %.10f\n", i, q.angles[i]);
    }

    return 0;
}