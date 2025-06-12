#include <iostream>
using namespace std;

int main() 
{
    int number;
    cout << "Enter an integer: ";
    cin >> number;
    cout << "Multiples of 3 or 5 less than or equal to " << number << ":" << endl;
    cout << "-------------" << endl;

    int count = 0; 
    for (int i = 1; i <= number; i++)
    { 
        if (i % 3 == 0 || i % 5 == 0) 
        {
            cout << i << endl;
            count++;
        }
    }

    cout << "-------------" << endl;
    cout << "Total " << count << " numbers." << endl;

    return 0;
}
