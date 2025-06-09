#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a_str;
    int b;
    cout << "Enter an integer: ";
    cin >> a_str;
    cout << "Enter the position from the right: ";
    cin >> b;

    if (b < 1 || b > a_str.length())
    {
        cout << "The position is out of range." << endl;
    }
    else
    {
        cout << "The " << b << "th digit from the right is " << a_str[a_str.length() - b] << endl;
    }

    return 0;
}
