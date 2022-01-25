#include <iostream>
using namespace std;

int main ()
{
	int a, b, c, max;
	cin >> a >> b >> c;
	
	if (a == 1)  //若a = 1，輸出b + c 
		cout << b + c;
	if (a == 2)  //若a = 2，輸出|b - c| 
	{
		if (b - c >= 0)  //判斷b - c的正負，若為正，輸出b - c 
			cout << b - c;
		if (b - c < 0)  //判斷b - c的正負，若為負，輸出c - b 
			cout << c - b;		
	}
	if (a == 3) //若a = 3，輸出bc
		cout << b * c;
	if (a == 4)  //若a = 4，b除以或c除以b的餘數為0，輸出1 
	{
		if (b != c)  //若b不等於c，判斷b除以c、c除以b的餘數，其中有一為0時輸出1 
		{
			if (b % c == 0)
				cout << "1";
			if (c % b == 0)
				cout << "1";
		}
		if (b == c)  //若b = c，輸出1 
			cout << "1";
		if (b % c != 0)  //若b除以c和c除以b之餘數皆不為0，輸出0 
		{
			if (c % b != 0)
				cout << "0";
		} 
	}
	if (a == 5)  //若a = 5，比較b + c, bc, |b - c|大小 
	{
		if (b + c >= b * c)  //比較b + c和bc的大小，較大之值存入max 
			max = b + c;
		if (b + c < b * c)
			max = b * c;
		if (b - c >= max)  //比較max值和|b - c|的大小，較大之值存入max 
			max = b - c;
		if (c - b >= max)
			max = c - b;
		
		cout << max;  //最後輸出max的值 
	}
	
	return 0;
}
