#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

int main()
{
	int n = 0;
	int b = 0;
	int sum = 0;
	
	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		cin >> b; 
		if (b == 2)
		{
			char x[11] = {0};
			cin >> x;
			for (int j = 0; j < strlen(x); j++)
			{
				sum += static_cast<int>(x[strlen(x)-1-j]-48) * pow(2, j);
			}
		}
		
		else if (b == 10)
		{
			int x = 0;
			cin >> x;
			sum += x;	
		}
	}
	cout << hex << uppercase << sum << endl;
	
	return 0;
}


