#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

double fun(double a, double b, double c, double x, double y)
{
    return (a*y)+(b*exp(c*x));
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

    double a, b, c, d, e, h, sumdy;
    cout << "Give parameters: ";
    cin >> a; cin >> b; cin >> c; cin >> d; cin >> e; cin >> h;
    double x0 = 0;
    double y0 = d; // initial condition
    int arrSize = (e/h);

    double x[arrSize][4];
    double y[arrSize][4];
    double k[arrSize][4];
    double dy[arrSize][4];

    cout << "\ni\t" << "x\t" << "y" << endl << endl;

    for (int i = 0; i <= arrSize; i++) {

    	x[i][0] = x0;
    	y[i][0] = y0;

        globalError << y[i][0] - analytSol(x[i][0]) << ",";
        X << x[i][0] << ",";
        Y << y[i][0] << ",";

        /* for calculating simple error for Y2
        if (i%2 == 0) {
            X << x[i][0] << ",";
            Y << y[i][0] << ",";
        } */

    	if (i == 0) {
    		k[i][0] = h*fun(a, b, c, x[i][0], y[i][0]);
		} else {
			k[i][0] = k[i-1][3];
		}
    	dy[i][0] = k[i][0];

    	cout << i << "\t" << x[i][0] << "\t" << y[i][0] << endl;

		x[i][1] = x0 + (0.5)*h;
		y[i][1] = y0 + (0.5)*k[i][0];
    	k[i][1] = h*fun(a, b, c, x[i][1], y[i][1]);
    	dy[i][1] = 2*k[i][1];

    	cout << i << "\t" << x[i][1] << "\t" << y[i][1] << endl;

    	x[i][2] = x0 + (0.5)*h;
		y[i][2] = y0 + (0.5)*k[i][1];
    	k[i][2] = h*fun(a, b, c, x[i][2], y[i][2]);
    	dy[i][2] = 2*k[i][2];

    	cout << i << "\t" << x[i][2] << "\t" << y[i][2] << endl;

    	x[i][3] = x0 + h;
		y[i][3] = y0 + k[i][2];
    	k[i][3] = h*fun(a, b, c, x[i][3], y[i][3]);
    	dy[i][3] = k[i][3];

    	cout << i << "\t" << x[i][3] << "\t" << y[i][3] << endl;

    	x0 = x[i][3];
    	sumdy = ((dy[i][0] + dy[i][1] + dy[i][2] + dy[i][3]))/6;
    	y0 = y0 + sumdy; // sum + y0

    	cout << endl;
	}

	X.close();
	Y.close();
	globalError.close();
    return 0;
}
