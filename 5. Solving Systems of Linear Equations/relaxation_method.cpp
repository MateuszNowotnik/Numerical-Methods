#include <iostream>
#include <math.h>
using namespace std;

double fabsMax(double a, double b, double c)
{
    a = fabs(a); b = fabs(b); c = fabs(c);
    double maxim = fmax(a, b);
    return fmax(maxim, c);
}

void convTest(double a[3][4])
{
    if (a[0][0] < a[0][1] + a[0][2]) {throw "Convergence Test Failed";}
    if (a[1][1] < a[1][0] + a[1][2]) {throw "Convergence Test Failed";}
    if (a[2][2] < a[2][0] + a[2][1]) {throw "Convergence Test Failed";}
}

int main()
{
    int k, n, xIndex[3];
    double e, a[3][4], maxVal[3], temp;
    double x[3], prevX[3], r[3], maxVal2, tempNum;
    bool stopAcc = false;

    cout << "This program works for system of 3 linear equations of 3 variables [in the form: a1*x1 + a2*x2 + a3*x3 = d]" << endl;
    cout << "Form of the input: a1 a2 a3 d" << endl;

    cout << "Type in coefficients and result of every equation: " << endl;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            cin >> a[i][j];

    cout << "Give the accuracy: ";
    cin >> e;

    for (int i = 0; i < 3; i++) {
        maxVal[i] = fabsMax(a[0][i], a[1][i], a[2][i]); // find max value of i-th column and store it in the maxVal array
        for (int j = 0; j < 3; j++) {
            if (maxVal[i] == fabs(a[j][i])) {
                if (i != j) { // swap rows if the max value is not on the diagonal
                    for (int k = 0; k < 4; k++) {
                        temp = a[i][k];
                        a[i][k] = a[j][k];
                        a[j][k] = temp;
                    }
                }
            }
        }
    }

    convTest(a); // check the convergence

    for (int i = 0; i < 3; i++) {
        xIndex[i] = 0;
        x[i] = 0;
        prevX[i] = 0;

        r[i] = a[i][3];
    }
    n = 0;

    while (stopAcc == false) {
        n++;
        maxVal2 = fabsMax(r[0], r[1], r[2]);
        for (int i = 0; i < 3; i++) {
            if (maxVal2 == fabs(r[i])) {
                tempNum = r[i]/maxVal[i]; // calculate the approximate x[i]
                x[i] += tempNum;
                if (fabs(tempNum - prevX[i]) < e) { // stop if the epsilon is bigger than the assumed accuracy
                    stopAcc = true;
                    break;
                }
                prevX[i] = tempNum;
                for (int j = 0; j < 3; j++)
                    r[j] += -(a[j][i]*prevX[i]); // calculate the residuals
            }
        }
    }

    cout << "\nSolution:" << endl;
    cout << "x1" << " = " << x[0] << endl;
    cout << "x2" << " = " << x[1] << endl;
    cout << "x3" << " = " << x[2] << endl;
    cout << "# of iterations: " << n << endl;

    return 0;
}
