#include <iostream>

using namespace std;

int main()
{
double x;
cin >> x;
while (!(x > 100))
{
x = x * 2;
}
cout << x;
return 0;
}