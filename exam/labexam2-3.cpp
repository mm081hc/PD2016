#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <stdio.h> 
using namespace std;

int main()
{
	int n = 0;
	char data[1010][1010] = {0}, date[8] = {0}, delim[2] = {' '};
	int product[26] = {0}, dis[26][1010] = {0};
	cin >> n;
	
	
	for(int i = 0; i < n; i++)
	{
		cin.getline(data[i], 1010);
	}
	cin >> date;
	date[4] = ' ';
	if (date[5] == '0')
	{
		date[5] = date[6];
		date[6] = ' ';
	}
	
	for (int i = 0; i < n; i++)
	{
		if (strncmp(data[i], date, 7) == 0)
		{
			cout << data[i] << endl;
			int count = 0, num = 0;
			char* start = strok(data, delim);
			while (start != nullptr)
			{
				count++;
				if (count == 5)
				{
					for (int j = 0; j < strlen(start); j++)
					{
						num += (start-48) * pow(10, j);
					}
				}
				else if (count == 6)
				{
					product[start-65]++;
					dis[start-65][num]++;
				}
				start = strok(data, delim);
			}
			
		}
		
	}
	
	return 0;
}

