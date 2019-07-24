#include <iostream>
using namespace std;

// initialize the initial vector
void initVec(int v, double y[1][3])
{
    switch(v) {
        case 1:
            y[0][0] = 1; y[0][1] = 0; y[0][2] = 0;
            break;
        case 2:
            y[0][0] = 0; y[0][1] = 1; y[0][2] = 0;
            break;
        case 3:
            y[0][0] = 0; y[0][1] = 0; y[0][2] = 1;
            break;
        default:
            cout << "Something's wrong!" << endl;
    }
}

int main()
{
    double A[3][3];
    double y[9][3] = {0};
    double eigenvalue, quot[3];
    bool oscQuot = true;
    int v = 0;

    double g1 = 15.76404;
    double g2 = 6.22446;
    double g3 = 1.0;


    cout << "3x3 matrix A:" << endl;


    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> A[i][j];

    while (oscQuot == true){
        // initial vector y(0)
        initVec(++v, y);

        // obtaining the iterations of vector 'y'
        for (int i = 1; i < 9; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                y[i][j] += y[i-1][k]*A[k][j];

        // calculating the quotients
        quot[0] = y[8][0]/y[7][0];
        quot[1] = y[8][1]/y[7][1];
        quot[2] = y[8][2]/y[7][2];


        // changing the value of initial vector if the values of quotients are oscillating
        if (quot[0] != quot[2])
            oscQuot = false;
    }

    // calculating the eigenvalue as the arithmetic mean of all quotients
    eigenvalue = (quot[0] + quot[1] + quot[2])/3.0;

    /*
    // Krylov
    for (int i = 0; i < 3; i++) {
        cout << endl;
        for (int j = 0; j < 4; j++)
            cout << y[j][i] << " ";
    }
    cout << endl << endl;
    */

    cout << "\nHighest modulus eigenvalue: " << eigenvalue << endl;

    cout << "\nHighest corresponding eigenvector: " << endl;
    for (int i = 0; i < 3; i++)
        cout << y[8][i] << endl;

    cout << "\nAfter normalization: " << endl;
    cout << y[8][0]/max(max(y[8][0],y[8][1]),y[8][2]) << endl;
    cout << y[8][1]/max(max(y[8][0],y[8][1]),y[8][2]) << endl;
    cout << y[8][2]/max(max(y[8][0],y[8][1]),y[8][2]) << endl;

    return 0;
}
