#include <iostream>
#include <math.h>
using namespace std;

double integrand(double x, double y, int n, int integ)
{
    double pi = atan(1)*4;

    if (integ == 1) {
        if (y == 1) // x > a && x < b
            return x*sin(pi*n*x);
        else
            return y*sin(pi*n*x);
    }
    if (integ == 2) {
        if (y == 1)
            return x*cos(pi*n*x);
        else
            return y*cos(pi*n*x);
    }
    if (integ == 3) {
        if (y == 1)
            return x;
        else
            return y;
    }
}

// ----------------------------------------- BEGIN OF INTEGRATION-----------------------------------
double *XsForRect(double a, double h, int m)
{
    double *x = new double[m];

    for (int i = 1; i <= m; i++) {
        x[i-1] = a+((double)i - (0.5))*h;
    }

    return x;
}

// using rectangular method for calculating integrals (n=0,m=20)
double integralRect(double a, double b, double y, int n, int integ)
{
    double h, *x;
    int m = 20;
    double sum = 0;
    h = (b-a)/m;
    x = XsForRect(a, h, m);

    for (int i = 0; i < m; i++) {
        sum += integrand(x[i], y, n, integ);
    }
    return sum*h;
}
// ----------------------------------------- END OF INTEGRATION-----------------------------------

double funSum(double x, double L, double A[], double B[], int n)
{
    double pi = atan(1)*4;
    double sum = 0;

    for (int i = 1; i < n; i++) {
        sum += A[i]*sin((pi*i*x)/L) + B[i]*cos((pi*i*x)/L);
    }

    return sum;
}


int main()
{
    double pi = atan(1)*4;
    int n;
    double L, Ai, Bi, B0, w;
    int subinter; //how many sub-intervals in the interval (a,b)

    cout << "How many loops (n): ";
    cin >> n;
    double A[n] = {0};
    double B[n] = {0};

    cout << "Give the value of sub-intervals: ";
    cin >> subinter;
    double intervs[subinter][2];
    double y[subinter] = {0};

    cout << "Give each sub-interval and solution: ";
    for (int i = 0; i < subinter; i++) {
        cin >> intervs[i][0]; // a
        cin >> intervs[i][1]; // b
        cin >> y[i];
    }

    L = (intervs[subinter-1][1]-intervs[0][0])/2; // (b-a)/2

    for (int i = 1; i < n; i++) {
        Ai = 0; Bi = 0; B0 = 0;
        for (int j = 0; j < subinter; j++) {
            Ai += integralRect(intervs[j][0], intervs[j][1], y[j], i, 1);
            Bi += integralRect(intervs[j][0], intervs[j][1], y[j], i, 2);
            B0 += integralRect(intervs[j][0], intervs[j][1], y[j], i, 3);
        }
        A[i] += Ai/L;
        B[i] += Bi/L;
    }

    w = -1.0;
    while (w < 1) {
        cout << B0/(2*L) + funSum(w, L, A, B, n) << endl;
        w += 0.1;
    }

    /*
    for (int i = 1; i < n; i++) {
        cout << A[i] << endl;
    }
    cout << "---------" << endl;
    for (int i = 1; i < n; i++) {
        cout << B[i] << endl;
    }
    */

    return 0;
}
