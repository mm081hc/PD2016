#include <iostream>
using namespace std;

int main()
{
	int n = 0, p[150] = {0}, s[110][110] = {0};
	int min = 0, ijSum = 0, sum = 0;
	// min: setup time�`�M���̤p�� // ijSum: i+j // sum: ��l��setup time�`�M 
	int iPos = 0, jPos = 0, pTime = 0, sTime = 0;
	// iPos, jPos: min�ɪ�i, j�� // pTime: sum of processing times // sTime: sum of setup times
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> p[i]; 
		pTime += p[i];  // �p��processing times���`�M 
	}
	for (int i = 1; i <= n; i++) 
		for(int j = 1; j <= n; j++) 
			cin >> s[i][j]; 
	
	for (int i = 1; i < n; i++)
		sum += s[i][i+1];  // �p���l��setup time�`�M
	min = sum;  // �O��lsetup time�`�M����e�̤p��
	
	for (int i = 1; i < n; i++)  // ������m���� 
	{
		for (int j = i + 1; j <= n; j++)
		{
			/*�p��setup time:
			�洫�L��m��setup time�M�쥻���ۤ�A�̦h�ۮt4�Ӽ�
			�Ys[i-1][i], s[i][i+1], s[j-1][j], s[j][j+1]
			�G������l���o�|�ӭȡA�A�[�W�洫�᪺�o�|�ӭȡA�Y����e��setup time*/
			if (j == i + 1)  // ij�۾F 
			sTime = sum - s[i-1][i] - s[i][j] - s[j][j+1]
						+ s[i-1][j] + s[j][i] + s[i][j+1];
						
			else  // ��l���p 
			sTime = sum - s[i-1][i] - s[i][i+1] - s[j-1][j] - s[j][j+1]
						+ s[i-1][j] + s[j][i+1] + s[j-1][i] + s[i][j+1];

			if (sTime < min || (sTime == min && i + j <= ijSum))
			{
				// �Y
				min = sTime;  // ��min, ijSum, iPos, jPos 
				ijSum = i + j;
				iPos = i;
				jPos = j;
			}
//			cout << sTime << " ";
		}
//		cout << pTime << " " << pTime + min << " " << min << endl;
	}
	
	for (int i = 1; i <= n; i++)  // ��X���� 
	{
		if (i == iPos)  // ����i�Ӧ�m�A�אּj 
			cout << jPos << " ";
		else if (i == jPos)  // ����j�Ӧ�m�A�אּi 
			cout << iPos << " ";
		else
			cout << i << " ";
	}
	cout << pTime + min;  // ��X�ɶ��`�M 
	
	return 0;
}
