#include <iostream>
using namespace std;

int main()
{
	int n, m, k, T, i = 1, sum = 0;
	// n: ��n�H �F m: �Ʀr �F k: ��k�H �F T: ����� �F i: �Q�s�쪺�Ʀr �F sum: ��k�H�s���Ʀr���`�M 
	cin >> n >> m >> k >> T;
	
	while (i <= T) 
	{
		if (i % n == k && i % 10 != m && i % m != 0)
			/* i % n == k: �P�_i�O�_����k�H�s���� 
			�Yi����k�H�s���ƥBi�����Ƥ���m�Bi����m�����ơA�Ni�[��sum */
			sum = sum + i;
		i = i + 1;
	}
	
	cout << sum;  //��X�`�M 
	
	return 0;
 } 
