#include <iostream>
#include <algorithm>  // sort�w�q�󦹼��Y�� 
using namespace std;

int main()
{
	int n, dia, sum[4] = {0}, min = 0;  // dia = number of diamonds�Fsum��4�H�U�۪��_���ơA�@�}�l�Ҭ�0 
	cin >> n;
	
	for (int j = 1; j <= n; j++)  // j: ��j����J
	{
		cin >> dia;  // ���J���Ƥp��n�A��Jdia
		for (int i = 0; i < 4; i++)
		{
			if (sum[i] < sum[min])
				min = i;  // �Ysum[i]���e�̤p�Ȥp�A��s�̤p�Ȫ�����
				/* �]i�q0�}�l�W�[�A�G�Y�ϫ᭱���H�_���ƻP�e�����H�ۦP�A
				���󦡤��|���ߡA���|���̤p�ȵ��СC�Y�O�����P�_�_���ƬۦP�����p */
		}
		sum[min] = sum[min] + dia;  // �N�_�����t���_���Ƴ̤֪��H 
	}
	
	sort (sum, sum+4);  // �̤p��j�Ƨǥ|�H���_����
	cout << sum[0] << " " << sum[1] << " " << sum[2] << " " << sum[3];
	
	return 0;
}
