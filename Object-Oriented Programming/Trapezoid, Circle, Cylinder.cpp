#include <iostream>
using namespace std;

int main()
{
    const double PI =  3.141592;
    double a, b, h;

    cout << "Enter 3 real numbers: ";
    cin >> a >> b >> h;

    double trapezoidArea = (a + b) * h / 2.0;
    double circleArea = PI * a * a;
    double cylinderVolume = PI * a * a * h;
    double cylinderSurfaceArea = 2 * PI * a * (a + h);

    cout << "The area of a trapezoid with bottom base " << a << ", top base " << b << ", and height " << h << " is " << trapezoidArea << "." << endl;
    cout << "The area of a circle with radius " << a << " is " << circleArea << "." << endl;
    cout << "The volume of a cylinder with radius " << a << " and height " << h << " is " << cylinderVolume << "." << endl;
    cout << "The surface area of a cylinder with radius " << a << " and height " << h << " is " << cylinderSurfaceArea << "." << endl;

    return 0;
}
