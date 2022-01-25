#include <iostream>
using namespace std;

int main()
{
	int num;
	cin >> num;
	
	while (num > 0)
	{
		for (int i = 1; i <= num; i++)
		{
			if(num % i == 0 && num != i)
				cout << i << " ";
			if (num == i)
				cout << i << "\n";
		}
		
		cin >> num;
	}

	
	return 0;
 } 
