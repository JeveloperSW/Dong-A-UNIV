#include <iostream>
#include <cmath>
using namespace std;

int main() 
{
    int n, sum1 = 0, sum2 = 0, sum3 = 0;
    cout << "Enter n: ";
    cin >> n;
    for (int i = 1; i <= n; i++) 
    {
        sum1 += i;           // 1 + 2 + ... + n
        sum2 += pow(i, 2);   // 1^2 + 2^2 + ... + n^2
        sum3 += pow(i, 3);   // 1^3 + 2^3 + ... + n^3
    }
    cout << "The value of sum1 is " << sum1 << endl;
    cout << "The value of sum2 is " << sum2 << endl;
    cout << "The value of sum3 is " << sum3 << endl;

    return 0;
}
