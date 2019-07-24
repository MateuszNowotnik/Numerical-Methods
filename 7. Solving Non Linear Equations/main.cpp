#include <iostream>
#include <math.h>
using namespace std;

double fun(double x)
{
    return (x*x*x*x)-625;
}

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

double solvEQ(double a, double b, double eps, bool RN)
{
    double xPrev, xCurr;
    if(fun(a) > 0 && derivative(a, 2) > 0) {
        if(RN == true) {
            cout << "\nUsing Regula-Falsi method:" << endl << endl;
            xPrev = b;
            do{
                xCurr = xPrev - (fun(xPrev)/(fun(a)-fun(xPrev)))*(a-xPrev);
                cout << xCurr << endl;
                xPrev = xCurr;
            } while (fabs(fun(xCurr)) > eps);
        }

        if(RN == false) {
            cout << "\n\nUsing Newton method:" << endl << endl;
            xPrev = a;
            do {
                xCurr = xPrev - (fun(xPrev)/(derivative(xPrev, 1)));
                cout << xCurr << endl;
                xPrev = xCurr;
            } while (fabs(fun(xCurr)) > eps);
        }
    }

    if(fun(b) > 0 && derivative(b, 2) > 0) {
        if(RN == true) {
            cout << "\nUsing Regula-Falsi method:" << endl << endl;
            xPrev = a;
            do {
                xCurr = xPrev - (fun(xPrev)/(fun(b)-fun(xPrev)))*(b-xPrev);
                cout << xCurr << endl;
                xPrev = xCurr;
            } while (fabs(fun(xCurr)) > eps);
        }

        if(RN == false) {
            cout << "\n\nUsing Newton method:" << endl << endl;
            xPrev = b;
            do {
                xCurr = xPrev - (fun(xPrev)/(derivative(xPrev, 1)));
                cout << xCurr << endl;
                xPrev = xCurr;
            } while (fabs(fun(xCurr)) > eps);
        }
    }
}



int main()
{
    double a, b;
    double eps;

    cout << "Enter the interval: ";
    cin >> a; cin >> b;

    if ((b < a) || (b == a)) {
        cout << "\nFAIL: Wrong interval!\n";
        return false;
    }

    cout << "Enter the accuracy: ";
    cin >> eps;

    // true -> regula-falsi ; false -> Newton
    solvEQ(a,b,eps, true);
    solvEQ(a,b,eps, false);

    return 0;
}
