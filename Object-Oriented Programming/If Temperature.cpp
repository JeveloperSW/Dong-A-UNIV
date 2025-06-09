#include<iostream>
using namespace std;

int main()
{
    int number;
    double fd, cd;

    cout << "Select an option (1: Fahrenheit->Celsius, 2: Celsius->Fahrenheit): ";
    cin  >> number;
    if(number == 1)
    {
        cout << "Enter Fahrenheit temperature: ";
        cin >> fd;
        cd = 5.0 / 9.0 * (fd - 32.0);
        cout.precision(5);
        cout << fixed;
        cout << "The Celsius temperature is " << cd << "." << endl;
    }
    else if(number == 2)
    {
        cout << "Enter Celsius temperature: ";
        cin >> cd;
        fd = cd * 9.0 / 5.0 + 32.0;
        cout.precision(5);
        cout << fixed;
        cout << "The Fahrenheit temperature is " << fd << "." << endl;
    }
    else
    {
        cout << "Please enter either 1 or 2.";
    }
    
    return 0;
}
