#include <iostream>
using namespace std;

int main()
{
	int r, g, b, n, k, num = 0, r1, g1, b1;  // num: �L�a���ƶq�Fr1, g1, b1: �C����J��r, g, b��   
	cin >> r >> g >> b;
	cin >> n;
	cin >> k;
	
	for (int i = 1; i <= n; i++)  // ���J������<=n���A�~���J�U�@��rgb�� 
	{
		cin >> r1 >> g1 >> b1;

		if ((r1 > r + k) || (r1 < r - k) || (g1 > g + k) ||
			(g1 < g - k) || (b1 > b + k) || (b1 < b - k)) 
			num++;  // �p�G��J��rgb�ȶW�X�d��+-k�A�L�a��+1 
	}
	
	cout << num;  // ��X�L�a�� 
	
	return 0;
}
