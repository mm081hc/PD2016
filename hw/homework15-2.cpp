#include <iostream>
using namespace std;

int main()
{
	int m, n, a = 2, b = 0;
	cin >> m >> n;

	while (a < m)
	{
		int i = 2;
		if (a % 10 != n)
		{
			while (a >= i * i)
			{
				if (a % i == 0)
					b = 1;
				i++;
			}
			if (b == 0 && a != 2)
				{
					if (n == 2 && a == 3)
						cout << a;
					else 
						cout << " " << a;
				}
			if (a == 2)
				cout << a;
		}
		a++;
		b = 0;
	}
	
		cout << "\n";
	
	return 0;
}
