
#include <stdio.h>
#include <math.h>

const double Precision = 1E-6;

int SolveSquare (double a, double b, double c, double* adr1, double* adr2)
    {
    double discriminant = b*b - 4*a*c;
    if (a != 0)
        {
        if (discriminant > 0)
            {
            *adr1 = (-b - sqrt (discriminant)) / (2*a);
            *adr2 = (-b + sqrt (discriminant)) / (2*a);
            return 2;
            }
        if (discriminant == 0)
            {
            *adr1 = b / (2*a);
            return 1;
            }
        if (discriminant < 0)
            {
            printf ("No roots ");
            return 0;
            }
        }
        else
        {
        printf (" a=0, root of linear equation: x = %lg\n", -c / b);
        }
    }

int main()
    {
    double a = 0;
    double b = 0;
    double c = 0;
    double x1 = 0;
    double x2 = 0;
    scanf ("%lg%lg%lg", &a, &b, &c);
    int nRoots = SolveSquare (a, b, c, &x1, &x2);
    if (nRoots == 2)
        {
        printf ("x1 = %+lg\n"  "x2 = %+lg\n", x1, x2);
        }
    if  (nRoots == 1)
        {
        printf ("x = %lg\n", x1) ;
        }
    }




