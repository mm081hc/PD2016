#include <iostream>
using namespace std;

int main()
{
	int r, g, b, n, k, num = 0, r1, g1, b1;  // num: 印壞的數量；r1, g1, b1: 每次輸入的r, g, b值   
	cin >> r >> g >> b;
	cin >> n;
	cin >> k;
	
	for (int i = 1; i <= n; i++)  // 當輸入的次數<=n次，繼續輸入下一個rgb值 
	{
		cin >> r1 >> g1 >> b1;

		if ((r1 > r + k) || (r1 < r - k) || (g1 > g + k) ||
			(g1 < g - k) || (b1 > b + k) || (b1 < b - k)) 
			num++;  // 如果輸入之rgb值超出範圍+-k，印壞數+1 
	}
	
	cout << num;  // 輸出印壞數 
	
	return 0;
}
