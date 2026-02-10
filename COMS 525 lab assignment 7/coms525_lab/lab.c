#include <stdio.h>
#include <math.h>

int main(){
    int n = 5;
    int factorial = 1;
    int i;

    for (i = 1; i <= n; i++)
    {
        factorial = factorial * i;
    }

    printf("Factorial of n = %i is %i\n", n, factorial);

    double x = 1.0;
    double expx;

    expx = exp(x);
    printf("exp(%f) = %f\n", x, expx);

    double y = 2.0;
    double logy;

    logy = log(y);
    printf("log(%f) = %f\n", y, logy);

    return 0;
}
