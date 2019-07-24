#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

double fun(double x, double y)
{
    return (-2*y+7*pow(2.71,-2*x));
}

double analytSol(double x)
{
    return (7*x-10)/(exp(2*x));
}

int main()
{
    ofstream X, Y, globalError, localError;
    X.open ("dataGraphX.txt");
    Y.open ("dataGraphY.txt");
    globalError.open ("globalError.txt");

    double h,maxv=5;
    cout << "Enter value of h: ";
    cin >> h;

    int arrsize=(5/h);
    double x[arrsize];
    double y[arrsize];
    double func[arrsize];

    x[0] = 0;
    //y[0] = -10;
    func[0] = 27;

    cout << "\ni\t\t" << "x\t\t" << "y" << endl << endl;

    for(int i=0; i<=arrsize; i++) {
        x[i] = x[0]+i*h;
        if (i == 0) {
            y[i] = -10;
        } else {
            y[i] = y[i-1] + (h*func[i-1]);
        }
        globalError << y[i] - analytSol(x[i]) << ",";
        //X << x[i] << ",";
        //Y << y[i] << ",";

        // for calculating simple error for Y2
        if (i%2 == 0) {
            X << x[i] << ",";
            Y << y[i] << ",";
        } //

        func[i] = fun(x[i],y[i]);
        cout << i << "		" << x[i] << "		" << y[i] << "		" << endl;
    }


    return 0;
}
