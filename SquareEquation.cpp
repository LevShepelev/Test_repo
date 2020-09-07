#include <stdio.h>
#include <math.h>

const double epsilon = 1e-7;
int Solvelinear (double a, double b, double* adr1)
    {
    printf("Your equation if linear, ");
    if (fabs (a) > epsilon)
        {
        printf ("1 root, x = %lg\n", -b / a);
        *adr1 = -b / a;
        }
    if ((fabs (a) < epsilon) && (fabs (b) < epsilon))
        printf ("Infinite number of roots");
    if ((fabs (a) < epsilon) && (fabs (b) > epsilon))
        printf ("No roots");
    }
int SolveSquare (double a, double b, double c, double* adr1, double* adr2)
    {
    double discriminant = b*b - 4*a*c;
    if (fabs (a) > epsilon)
        {
        if (discriminant > epsilon)
            {
            *adr1 = (-b - sqrt (discriminant)) / (2*a);
            *adr2 = (-b + sqrt (discriminant)) / (2*a);
            return 2;
            }
        if (fabs (discriminant) < epsilon)
            {
            *adr1 = b / (2*a);
            return 1;
            }
        if (discriminant < -epsilon)
            {
            printf ("No roots");
            return 0;
            }
        }
        else
        Solvelinear (b, c, adr1);
    }

int main()
    {
    printf ("Square Equation Solver 2020\nWrite coefficient a, b, c\n");
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int sc = scanf ("%lg%lg%lg", &a, &b, &c);
    fflush (stdin);
    while (sc != 3)
        {
        printf ("Incorrect input, try again:\n");
        sc = scanf ("%lg%lg%lg", &a, &b, &c);
        fflush (stdin);
        }
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




