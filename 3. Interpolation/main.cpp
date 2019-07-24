#undef __STRICT_ANSI__
#include <cmath>
#include <windows.h>
#include <iostream>
using namespace std;

double f(double x)
{
    //return (pow(x, 15.0)+3*pow (x, 14.0)+2*pow (x, 13.0)-10*pow (x, 10.0)+pow (x, 9.0)+2*pow (x, 6.0)+4*pow (x, 5.0)+3*pow (x, 4.0)-9*pow (x, 3.0)+61*pow (x, 2.0)-554*pow (x, 1.0));
    return (5/((x*x)+2));
    //return (sqrt(x*x));
    //return (cos(x));
}

double F(double xi[], double yi[], double wi[], int n, double x, bool finalWi)
{
    double F = 0;
    for(int i = 0; i <= n; i ++ )
    {
        wi[i] = 1;
        for(int j = 0; j<=n;j++)
        {
            if(j!=i)
                // the auxiliary polynomials
                wi[i] *= (x-xi[j])/(xi[i]-xi[j]);
        }
        F += wi[i]*yi[i];
    }

    if(finalWi == true) {
        for (int i = 0; i < n+1; i++) {
            cout << "wi[" << i << "] : "<< wi[i] << endl;
        }
    }

    return F;
}

void maxError(double xi[], double yi[], int a, int b, int n, double wi[], double x, bool finalWi)
{
    // find max error in the interval determined by a and b with the step equal to 0.01
    double err1,xmax,fxmax;
    double i = a;
    double err2 = f(a) - F(xi, yi, wi, n, x, finalWi);
    while(i <= b) {
        err1 = f(i) - F(xi, yi, wi, n, x, finalWi);
        err2 = max(err2, err1);
        if(err2==err1)
        {
            xmax=i;
            fxmax=f(xmax);
        }
        i+=0.01;
    }

    cout << "Max error: " << fabs(err2) << endl;
    cout << "xMax: " << xmax << endl;
    cout << "f(xMax): " << fxmax << endl;
}

int main()
{
    int n;
    double a, b, x, arg;

    double inter = 0;
    bool finalWi = false;

    cout << "Enter number of values: ";
    cin >> n;

    cout << "Enter the interval: ";
    cin >> a; cin >> b;

    cout << "Enter the value of x: ";
    cin >> x;

    if ((x < a) || (x > b)) {
        cout << "\nFAIL: x is outside of the interval!\n";
        return false;
    }

    double xiLag[n+1];
    double xiCheb[n+1];
    double yiLag[n+1];
    double yiCheb[n+1];
    double wi[n+1];
    double ri[n+1];

    // step, xi[0] xi[n+1] and their function values for the Lagrange method
    inter = (b-a)/(n);
    xiLag[0] = a;
    xiLag[n+1] = b;
    yiLag[0] = f(xiLag[0]);
    yiLag[n+1] = f(xiLag[n+1]);

    xiCheb[0] = a;
    xiCheb[n+1] = b;
    yiCheb[0] = f(xiCheb[0]);
    yiCheb[n+1] = f(xiCheb[n+1]);
    arg = M_PI/(2*n+2);

    for (int i = 1; i <= n+1; i++) {
        // Lagrange xi, yi
        xiLag[i] = xiLag[i-1] + inter;
        yiLag[i] = f(xiLag[i]);

        // Chebyshev xi, yi
        xiCheb[i] = 0.5*((b-a)*cos(arg*(2*n+1-2*i))+b+a);
        yiCheb[i] = f(xiCheb[i]);
    }

    finalWi = true;

    // Task 1
    cout << "\nLagrange: " << endl;
    cout << "\nInterpolation function: " << F(xiLag, yiLag, wi, n, x, finalWi) << endl;
    cout << "Interpolated function: " << f(x) << endl << endl;
    finalWi = false;
    maxError(xiLag, yiLag, a, b, n, wi, x, finalWi);
    // Task 2
    finalWi = true;
    cout << "Chebyshev: " << endl;
    cout << "\nInterpolation function: " << F(xiCheb, yiCheb, wi, n, x, finalWi) << endl;
    cout << "Interpolated function: " << f(x) << endl << endl;

    finalWi = false;
    // Task 3
    maxError(xiCheb, yiCheb, a, b, n, wi, x, finalWi);

    system("PAUSE");

    return 0;
}
