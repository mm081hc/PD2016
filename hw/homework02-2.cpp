#include <iostream>
using namespace std;

int main()
{
	int n, m, k, T, i = 1, sum = 0;
	// n: Τn  m: 计  k: 材k  T: 氨ゎ计  i: 砆计  sum: 材k计ぇ羆㎝ 
	cin >> n >> m >> k >> T;
	
	while (i <= T) 
	{
		if (i % n == k && i % 10 != m && i % m != 0)
			/* i % n == k: 耞i琌材k计 
			璝i材k计iЮ计ぃmiぃm计盢isum */
			sum = sum + i;
		i = i + 1;
	}
	
	cout << sum;  //块羆㎝ 
	
	return 0;
 } 
