#include <iostream>
using namespace std;

int main()
{
	int n = 0, m = 0, seqMain[1000] = {0}, seqTarget[50] = {0}, num = 0;
	// seqMain: Main sequence // seqTarget: Target sequence
	// num: �YTarget sequence�s�b��Main sequence�A����seqTarget[0]�bMain sequence����m 
	bool exist = 0; 
	/*exist: �P�_Target sequence�O�_�s�b��Main sequence 
	�Y�s�b��1�A���s�b��0*/
	
	cin >> n;  // ��JMain sequence 
	for (int i = 0; i < n; i++)
		cin >> seqMain[i];
	
	cin >> m;  // ��JTarget sequence
	for (int j = 0; j < m; j++)
		cin >> seqTarget[j];
	
	for (int i = 0; (i < n - m + 1) && (exist != 1); i++) // i: Main sequence�̲�i + 1��
	{
		/*�YTarget sequence�s�b��Main sequence�A
		�h�䭺��(seqTarget[0])���PMain sequence�̨䤤�@�ƬۦP�A 
		�G���˴�seqTarget[0]�O�_�MseqMain[i]�۵��A�A�˴��ƦC�O�_�s�b��Main sequence*/
		
		if (seqTarget[0] == seqMain[i])
		{
			exist = 1;
			num = i;  // �YTarget sequence�������PseqMain[i]�ۦP�A������ɪ�i��(��m) 
			
			for (int k = i, j = 0; j < m; k++, j++)  // �ˬd�ƦC�̪��C�@���O�_�MseqMain[i] ~ seqMain[i+m-1]�ۦP 
			{
				if (seqTarget[j] != seqMain[k])  
				{
					exist = 0;
					break;
					//�YTarget sequence�����ƩMMain sequence�����ۦP�Aexist = 0�ø��X���j�� 
				}
			}	
		}
	}
	
	
	if (exist == 0)  //�YTarget sequence���s�b��Main sequence�A��X0 
		cout << exist;
	else
		cout << num + 1;  //�Y�s�b�A��X��bMain sequence����m (��num+1��) 
		
	return 0;
}
