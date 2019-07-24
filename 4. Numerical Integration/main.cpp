#include <iostream>
#include <math.h>
using namespace std;

// Function
double fun(double x)
{
    return sin(2.5*x)+2*x*cos(0.1*x+1);
}

// calculating a specified order derivative of the function with the accuracy of 0.001
double derivative(double x, int order)
{
    double h = 0.001;
    if (order == 0)
        return fun(x);
    else if (order == 1)
        return (fun(x+h) - fun(x-h)) / (2*h);
    else
        return (derivative(x+h, order-1) - derivative(x-h, order-1)) / (2*h);
}

double *xsForNC(double a, double h, int n)
{
    double *x = new double[n+2];

    for (int i = 0; i <= n; i++)
        x[i] = a+(i*h);

    // x[n+1] -> x for error (x e (x0, xn))
    x[n+1] = (x[n]-x[0])/2;

    return x;
}

double *xsForRect(double a, double h, int m)
{
    double *x = new double[m];

    for (int i = 1; i <= m; i++) {
        x[i-1] = a+((double)i - (0.5))*h;
    }

    return x;
}

double *xsForCheb(double a, double b, double t[], int n)
{
    double *x = new double[n];

    for (int i = 0; i < n; i++)
        x[i] = 0.5*(b+a)+0.5*(b-a)*t[i];

    return x;
}

double maxError(double a, double b, int order)
{
    // find max error in the interval determined by a and b with the step of 0.01
    double err1;
    double err2 = derivative(a, order);
    double i = a;
    while(i <= b) {
        i+=0.01;
        err1 = derivative(i, order);
        err2 = max(err2, err1);
    }

    return fabs(err2);
}

// N-C methods
// m = 1 are for simple, other for composite
double NCmethod(double a, double b, int n, int m, bool err)
{
    double h, *x;
    switch(n) {
        // Rectangle formula
        case 0:
            {
                double sum = 0;
                h = (b-a)/m;
                x = xsForRect(a, h, m);

                if (err == false) {
                    for (int i = 0; i < m; i++) {
                        sum += fun(x[i]);
                    }
                    return sum*h;
                }
                if (m == 1 && err == true) // simple error
                    return (pow(b-a, 3)*maxError(a, b, 2))/24;
                if (m != 1 && err == true) // composite error
                    return (pow(h, 2)*(b-a)*maxError(a, b, 2))/24;
            }

        // Trapezoid formula
        case 1:
            {
                h = (b-a)/m;

                if (m == 1) {
                    x = xsForNC(a, h, n);
                    if (err == false)
                        return (h/2)*(fun(x[0])+fun(x[1]));
                    if (err == true)
                        return (-1*pow(h, 3)*derivative(x[n+1], 2))/12;
                }

                if (m == 4) {
                    x = xsForNC(a, h, m);
                    if (err == false)
                        return (h/2)*(fun(x[0])+2*fun(x[1])+2*fun(x[2])+2*fun(x[3])+fun(x[4]));
                    if (err == true)
                        return ((pow(h, 3)*m)/12)*maxError(a, b, 2);
                }
            }

        // Simpson's formula
        case 2:
            {
                h = (b-a)/(2*m);

                if (m == 1) {
                    x = xsForNC(a, h, n);
                    if (err == false)
                        return ((h/3)*(fun(x[0])+4*fun(x[1])+fun(x[2])));
                    if (err == true)
                        return (-1*pow(h, 5)*derivative(x[n+1], 4))/90;
                }

                if (m == 2) {
                    x = xsForNC(a, h, 2*m);
                    if (err == false)
                        return (h/3)*(fun(x[0])+4*fun(x[1])+2*fun(x[2])+4*fun(x[3])+fun(x[4]));
                    if (err == true)
                        return ((pow(h, 5)*m)/90)*maxError(a, b, 4);
                }
            }

        // Booles' formula
        case 4:
            {
                h=(b-a)/n;

                if (m == 1) {
                    x = xsForNC(a, h, n);
                    if (err == false)
                        return (((2*h)/45)*(7*fun(x[0])+32*fun(x[1])+12*fun(x[2])+32*fun(x[3])+7*fun(x[4])));
                    if (err == true)
                        return (-8*pow(h, 7)*derivative(x[n+1], 6))/945;
                }
            }

        default:
            cout << "Something went wrong!" << endl;
            break;
    }
}

// Chebyshev methods
double CHEBmethod(double a, double b, int n, int m, bool err)
{
    double *x, sum, h;
    switch(n) {
        case 2:
            {
                h = (b-a)/2;
                double t[n] = {-0.57735, 0.57735};
                x = xsForCheb(a, b, t, n);

                if (m == 1 && err == false) {
                    sum = fun(x[0])+fun(x[1]);
                    return sum*((b-a)/n);
                }
                if (m == 1 && err == true) {
                    return ((8.0/45.0)*maxError(a, b, 4))/24;
                }
                if (m == 2 && err == false) {
                    x = xsForCheb(a, a+h, t, n);
                    sum = fun(x[0])+fun(x[1]);
                    x = xsForCheb(a+h, a+(2*h), t, n);
                    sum += fun(x[0])+fun(x[1]);
                    return sum;
                }
                if (m == 2 && err == true) {
                    sum = ((8.0/45.0)*maxError(a, a+h, 4))/24;
                    return sum + ((8.0/45.0)*maxError(a+h, a+(2*h), 4))/24;
                }
            }

        case 4:
            {
                if (m == 1 && err == false) {
                    // for other formulas just change 't' and 'sum'
                    double t[n] = {-0.794654, -0.187592, 0.187592, 0.794654};
                    x = xsForCheb(a, b, t, n);
                    sum = (fun(x[0])+fun(x[1])+fun(x[2])+fun(x[3]));
                    return sum*((b-a)/n);
                }
                if (m == 1 && err == true) {
                    return ((32.0/945.0)*maxError(a, b, 4))/24;
                }
            }

        default:
            cout << "Something went wrong!" << endl;
            break;
    }
}

int main()
{
    double a, b;
    cout << "Give interval [a:b]: ";
    cin >> a; cin >> b;

    cout << "\nSIMPLE METHODS:" << endl << endl;
    cout << "Newton-Cotes method:" << endl;
    cout << "(n=0, m=1): " << NCmethod(a, b, 0, 1, false) << " | Error: " << NCmethod(a, b, 0, 1, true) << endl;
    cout << "(n=1, m=1): " << NCmethod(a, b, 1, 1, false) << " | Error: " << NCmethod(a, b, 1, 1, true) << endl;
    cout << "(n=2, m=1): " << NCmethod(a, b, 2, 1, false) << " | Error: " << NCmethod(a, b, 2, 1, true) << endl;
    cout << "(n=4, m=1): " << NCmethod(a, b, 4, 1, false) << " | Error: " << NCmethod(a, b, 4, 1, true) << endl;

    cout << "\nChebyshev method:" << endl;
    cout << "(n=2, m=1): " << CHEBmethod(a, b, 2, 1, false) << " | Error: " << CHEBmethod(a, b, 2, 1, true) << endl;
    cout << "(n=4, m=1): " << CHEBmethod(a, b, 4, 1, false) << " | Error: " << CHEBmethod(a, b, 4, 1, true) << endl;
    cout << endl;


    cout << "\nCOMPOSITE METHODS:" << endl << endl;
    cout << "Newton-Cotes method:" << endl;
    cout << "(n=0, m=4): " << NCmethod(a, b, 0, 4, false) << " | Max Error: " << NCmethod(a, b, 0, 4, true) << endl;
    cout << "(n=1, m=4): " << NCmethod(a, b, 1, 4, false) << " | Max Error: " << NCmethod(a, b, 1, 4, true) << endl;
    cout << "(n=2, m=2): " << NCmethod(a, b, 2, 2, false) << " | Max Error: " << NCmethod(a, b, 2, 2, true) << endl;
    cout << "(n=0, m=20): " << NCmethod(a, b, 0, 20, false) << " | Max Error: " << NCmethod(a, b, 0, 20, true) << endl;

    cout << "\nChebyshev method:" << endl;
    cout << "(n=2, m=2): " << CHEBmethod(a, b, 2, 2, false) << " | Error: " << CHEBmethod(a, b, 2, 2, true) << endl;

    return 0;
}
