#include <iostream>
using namespace std;

int main ()
{
	double d[7] = {0}, dMemo[7] = {0};
	// d: ��J��demands // dMemo: �Pd�ۦP�A�Ψ��٭�d
	double* dptr[13];  // dptr: �Ψӫ��Vd�}�C�A��K�p��ѼƶW�L������ 
	double fullBest[7] = {0}, partBest[7] = {0};  // fullBest, partBest: �̫��X���̨θ� 
	double priceFull = 0, pricePart = 0, fullMin = 0;
	// priceFull, pricePart: ��JF, P // fullMin: full-time agents�`�� 
	for (int i = 0; i < 13; i++)  // �]�wdptr���V����m�A�W�L6��: dptr[7]���Vd[0], dptr[8]���Vd[1]... 
		dptr[i] = &d[i % 7];
		
	for (int i = 0; i < 7; i++)  // ��J
	{
		cin >> d[i];
		dMemo[i] = d[i];
		fullMin += d[i];  // ��l��
	}
	cin >> priceFull >> pricePart;

	double sumMin = 0, startMin = d[0];
	// sumMin: total cost // startMin: min index of starting day 
	for (int i = 0; i < 7; i++)
	{
		sumMin += d[i] * pricePart;  // ��l�� 
	}
//		cout << sumMin << " ";
	for (int i = 0; i < 7; i++)
	{
		bool changeMin = 0;  // changeMin: �ΨӧP�_�O�_�����̤p�ȡA�Y�����h��1 
		double fulltime[7] = {0}, parttime[7] = {0};
		// fulltime, parttime: ��i+1�Ѷ}�l��full-time agents, part-time agents schedule 
		for (int k = 0; k < 7; k++)
		{
			bool last = 1;  // last: �ΨӧP�_�O�_��last iteration�A�Y���O�h��0				
			int day = i + k;  // �q��i+1�Ѷ}�l
			if (i + k > 6)
				day = i + k - 7;  // �}�C��m��0~6�A�Yi+k > 6�A�h�q0�}�l��_ 				
			
			if (*dptr[day] > 0)
			{
//				cout << *dptr[day] << " " << day << endl;
				int agentNum = *dptr[day];  // agentNum: ���tagents��	
				for (int j = 0; j < 7; j++)  // �P�_�O�_��last iteration
				{
					if(j < 5)
					{
						if (*dptr[day+j] > agentNum)
						{ // �Y�᤭�Ѧ���agentNum���@�Ӥ���0�A�h�Dlast iteration 
							last = 0;
							break;
						}						
					}	
					else if (*dptr[day+j] > 0)  // �Y���Ѿldemands�A�h�Dlast iteration 
						last = 0;

				}
//				cout << endl;
//				for (int j = 0; j < 7; j++)
//					cout << d[j] << " "; 
//				cout << endl;
//				for (int j = 0; j < 13; j++)
//					cout << *dptr[j] << " "; 				
//				cout << endl << " last is: " << last << endl;
				
				if (last == 0)  // �Dlast iteration 
				{
					for (int j = 0; j < 5; j++)   // �qd[]�������Ҥ��tagents
						*dptr[day+j] -= agentNum;
					fulltime[day] += agentNum;  // �O�U�ثe���t��full-time agents��					
				}
				else  // last iteration 
				{
					double dCal[7] = {0}, jPos = 0, priceMin = 0;
					// dCal: ����d[] // jPos: ����priceMin�ɪ�j��  // priceMin: min of price 
					for (int j = 0; j < 7; j++)
					{
						if (d[j] > 0)
						{
							dCal[j] = d[j];  // �����ثe������demands
							priceMin += d[j] * pricePart;
						}
					}
					for (int j = 1; j <= agentNum; j++)  // �C���W�[�@��full-time agents�A�p�����
					{
						double partNum = 0;  // partNum: number of part-time agents
						for (int l = 0; l < 7; l++)  // ���ݨD��A�p��part time��
							if (dCal[l] > 0)
							{
								dCal[l]--;
								partNum += dCal[l];
							}
						double price = j * priceFull + partNum * pricePart;
						/* price: last iteration�ɡA���tfull-time agents, part-time agents�ܥ�����demands
						�p�⦹���t�����B�j�p*/
						if (price < priceMin)  // �Y���B���U�̤p���B�p�A����priceMin�ðO�Uj 
						{
							jPos = j;
							priceMin = price;
						}
					}
					fulltime[day] += jPos;  // �O�U�ثe���t��full-time agents��	
					for (int j = 0; j < 7; j++)   // ����part-time agents�� 
					{ 
						if (d[j] > jPos)
							parttime[j] = d[j] - jPos;
					}					
					break; 
				}
			} 
		}
/*		cout << endl << "full: ";
		for (int k = 0; k < 7; k++)
			cout << fulltime[k] << " ";
		cout << endl << "part: ";
		for (int k = 0; k < 7; k++)
			cout << parttime[k] << " ";		
		cout << endl << " ----------------- " << endl;
*/
		double partSum = 0, fullSum = 0;
		// partSum: number of part-time agents // fullSum: number of full-time agents
		for (int k = 0; k < 7; k++)  // �p��agents�� 
		{
			fullSum += fulltime[k];
			partSum += parttime[k];	
		}
		double sum = fullSum * priceFull + partSum * pricePart;  // �p��totol cost
		if (sum < sumMin)  // �Ytotol cost��̤p�Ȥp�AchangeMin = 1 
			changeMin = 1;
		else if (sum == sumMin)  // �Ytotal cost�ۦP 
		{
			if(fullSum < fullMin)  // ���number of full-time agents
				changeMin = 1;
			else if (fullSum == fullMin)  // �Ynumber of full-time agents�ۦP 
				if (fulltime[i] < startMin)  // ���index of starting day 
					changeMin = 1;
		}
		
		if (changeMin == 1)  // �����̤p�� 
		{
			for (int k = 0; k < 7; k++)
			{
				fullBest[k] = fulltime[k];
				partBest[k] = parttime[k];
			}
			sumMin = sum;
			startMin = fulltime[i];
			fullMin = fullSum;			
		}
//		cout <<sum << " " << sumMin << endl;
		for (int k = 0; k < 7; k++)  // �٭�d�}�C������
			d[k] = dMemo[k];
	}

	for (int i = 0; i < 6; i++)  // ��X 
		cout << fullBest[i] << " ";
	cout << fullBest[6] << endl;
	for (int i = 0; i < 6; i++)
		cout << partBest[i] << " ";
	cout << partBest[6];
	
	return 0;
}
