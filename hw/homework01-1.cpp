#include <iostream>
using namespace std;

int main()
{
int a, b, c;

cin >> a;
while (a < 0)
	cin >> a;

cin >> b;
while (b < 0)
	cin >> b;

cin >> c;
while (c < 0)
	cin >> c;

int d = a + b + c;
if (d == 300)
	cout << "Wonderful!\n";
return 0;
}

