#include <iostream>
using namespace std;

int main ()
{
	int d[7] = {0}, schedule[7] = {0};
	// d: ��J��demands // schedule: �̫��X��schedule 
	for (int i = 0; i < 7; i++)  // ��J
		cin >> d[i];
		
	for (int i = 0; i < 7; i++)
	{
		if (d[i] > 0)  // �Y�һ�ĵ��� > 0 
		{
			int policeNum = d[i];  // policeNum: ���tĵ��Ʀ�day(i+1) 
			for (int j = 0; j < 5; j++)   // �qd[]�����Ҥ��t��ĵ���(policeNum) 
			{ 
				if (i + j > 6)  // �}�C��m��0~6�A�Yi+j > 6�A�h�q0�}�l��_
					d[i+j-7] -= policeNum;
				else
					d[i+j] -= policeNum;
			}
			schedule[i] += policeNum;  // �O�U�C�Ѥ��t��ĵ���
		}
	}

	for (int i = 0; i < 6; i++)
		cout << schedule[i] << " ";
	cout << schedule[6];
	return 0;
}
