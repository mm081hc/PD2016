#include <iostream>
using namespace std;

int main ()
{
	int a, b, c, max;
	cin >> a >> b >> c;
	
	if (a == 1)  //�Ya = 1�A��Xb + c 
		cout << b + c;
	if (a == 2)  //�Ya = 2�A��X|b - c| 
	{
		if (b - c >= 0)  //�P�_b - c�����t�A�Y�����A��Xb - c 
			cout << b - c;
		if (b - c < 0)  //�P�_b - c�����t�A�Y���t�A��Xc - b 
			cout << c - b;		
	}
	if (a == 3) //�Ya = 3�A��Xbc
		cout << b * c;
	if (a == 4)  //�Ya = 4�Ab���H��c���Hb���l�Ƭ�0�A��X1 
	{
		if (b != c)  //�Yb������c�A�P�_b���Hc�Bc���Hb���l�ơA�䤤���@��0�ɿ�X1 
		{
			if (b % c == 0)
				cout << "1";
			if (c % b == 0)
				cout << "1";
		}
		if (b == c)  //�Yb = c�A��X1 
			cout << "1";
		if (b % c != 0)  //�Yb���Hc�Mc���Hb���l�ƬҤ���0�A��X0 
		{
			if (c % b != 0)
				cout << "0";
		} 
	}
	if (a == 5)  //�Ya = 5�A���b + c, bc, |b - c|�j�p 
	{
		if (b + c >= b * c)  //���b + c�Mbc���j�p�A���j���Ȧs�Jmax 
			max = b + c;
		if (b + c < b * c)
			max = b * c;
		if (b - c >= max)  //���max�ȩM|b - c|���j�p�A���j���Ȧs�Jmax 
			max = b - c;
		if (c - b >= max)
			max = c - b;
		
		cout << max;  //�̫��Xmax���� 
	}
	
	return 0;
}
