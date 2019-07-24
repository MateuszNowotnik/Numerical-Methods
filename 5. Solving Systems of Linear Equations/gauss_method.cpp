#include <iostream>
using namespace std;

int determinant(double mat[3][4]) {
   int det = 0;
   det=mat[0][0]*mat[1][1]*mat[2][2]+mat[0][1]*mat[1][2]*mat[2][0]+mat[0][2]*mat[1][0]*mat[2][1]-(mat[2][0]*mat[1][1]*mat[0][2]+mat[2][1]*mat[1][2]*mat[0][0]+mat[2][2]*mat[1][0]*mat[0][1]);
   return det;
}
int main ()
{
    double a[3][4], x[3], s;
    cout << "This program works for system of 3 linear equations of 3 variables" << endl;
    cout << "Form of the input: a1 a2 a3 d" << endl;

    cout << "Type in coefficients and result of every equation: " << endl;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            cin >> a[i][j];

    x[0] = 0;
    x[1] = 0;
    x[2] = 0;

    if ((determinant(a))==0) {
        cout << "The matrix is singular ==> can't be solved by Gaussian Elimination";
        return 0;
    }

    for (int k = 0; k < 2; k++) {
        for (int i=k+1; i < 3; i++) {
            for (int j=k+1; j < 3; j++) {
                a[i][j] -= ((a[i][k]*a[k][j])/a[k][k]);
            }
        a[i][3] -= ((a[i][k]*a[k][3])/a[k][k]);
        }
    }


    x[2] = a[2][3]/a[2][2];

    for (int i = 2; i > -1; i--) {
        s = 0;
        for (int j=i+1; j < 3; j++) {
            s += a[i][j]*x[j];
        }
        x[i] = (a[i][3]-s)/a[i][i];
    }

    cout << endl;
    for (int m = 0; m < 3; m++) {
        cout << "x" << m+1 << " = " << x[m] << endl;
    }

    return 0;
}
