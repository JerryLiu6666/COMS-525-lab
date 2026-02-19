#ifndef __QUAD_H__
#define __QUAD_H__

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p[4];        
    double area;
    double perimeter;
    double angles[4];  
} Quadrilateral;

double quad_perimeter(const Quadrilateral* q);
double quad_area(const Quadrilateral* q);
void quad_angles(const Quadrilateral* q, double angles_out[4]);

#endif
