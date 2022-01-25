#include <iostream>
using namespace std;

int main ()
{
	double d[7] = {0}, dMemo[7] = {0};
	// d: 輸入之demands // dMemo: 與d相同，用來還原d
	double* dptr[13];  // dptr: 用來指向d陣列，方便計算天數超過的情形 
	double fullBest[7] = {0}, partBest[7] = {0};  // fullBest, partBest: 最後輸出的最佳解 
	double priceFull = 0, pricePart = 0, fullMin = 0;
	// priceFull, pricePart: 輸入F, P // fullMin: full-time agents總數 
	for (int i = 0; i < 13; i++)  // 設定dptr指向的位置，超過6時: dptr[7]指向d[0], dptr[8]指向d[1]... 
		dptr[i] = &d[i % 7];
		
	for (int i = 0; i < 7; i++)  // 輸入
	{
		cin >> d[i];
		dMemo[i] = d[i];
		fullMin += d[i];  // 初始化
	}
	cin >> priceFull >> pricePart;

	double sumMin = 0, startMin = d[0];
	// sumMin: total cost // startMin: min index of starting day 
	for (int i = 0; i < 7; i++)
	{
		sumMin += d[i] * pricePart;  // 初始化 
	}
//		cout << sumMin << " ";
	for (int i = 0; i < 7; i++)
	{
		bool changeMin = 0;  // changeMin: 用來判斷是否替換最小值，若替換則為1 
		double fulltime[7] = {0}, parttime[7] = {0};
		// fulltime, parttime: 第i+1天開始的full-time agents, part-time agents schedule 
		for (int k = 0; k < 7; k++)
		{
			bool last = 1;  // last: 用來判斷是否為last iteration，若不是則為0				
			int day = i + k;  // 從第i+1天開始
			if (i + k > 6)
				day = i + k - 7;  // 陣列位置為0~6，若i+k > 6，則從0開始算起 				
			
			if (*dptr[day] > 0)
			{
//				cout << *dptr[day] << " " << day << endl;
				int agentNum = *dptr[day];  // agentNum: 分配agents數	
				for (int j = 0; j < 7; j++)  // 判斷是否為last iteration
				{
					if(j < 5)
					{
						if (*dptr[day+j] > agentNum)
						{ // 若後五天扣掉agentNum有一個不為0，則非last iteration 
							last = 0;
							break;
						}						
					}	
					else if (*dptr[day+j] > 0)  // 若仍剩餘demands，則非last iteration 
						last = 0;

				}
//				cout << endl;
//				for (int j = 0; j < 7; j++)
//					cout << d[j] << " "; 
//				cout << endl;
//				for (int j = 0; j < 13; j++)
//					cout << *dptr[j] << " "; 				
//				cout << endl << " last is: " << last << endl;
				
				if (last == 0)  // 非last iteration 
				{
					for (int j = 0; j < 5; j++)   // 從d[]中扣除所分配agents
						*dptr[day+j] -= agentNum;
					fulltime[day] += agentNum;  // 記下目前分配的full-time agents數					
				}
				else  // last iteration 
				{
					double dCal[7] = {0}, jPos = 0, priceMin = 0;
					// dCal: 紀錄d[] // jPos: 紀錄priceMin時的j值  // priceMin: min of price 
					for (int j = 0; j < 7; j++)
					{
						if (d[j] > 0)
						{
							dCal[j] = d[j];  // 紀錄目前未完成demands
							priceMin += d[j] * pricePart;
						}
					}
					for (int j = 1; j <= agentNum; j++)  // 每次增加一個full-time agents，計算價格
					{
						double partNum = 0;  // partNum: number of part-time agents
						for (int l = 0; l < 7; l++)  // 更改需求表，計算part time數
							if (dCal[l] > 0)
							{
								dCal[l]--;
								partNum += dCal[l];
							}
						double price = j * priceFull + partNum * pricePart;
						/* price: last iteration時，分配full-time agents, part-time agents至未完成demands
						計算此分配的金額大小*/
						if (price < priceMin)  // 若金額比當下最小金額小，替換priceMin並記下j 
						{
							jPos = j;
							priceMin = price;
						}
					}
					fulltime[day] += jPos;  // 記下目前分配的full-time agents數	
					for (int j = 0; j < 7; j++)   // 紀錄part-time agents數 
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
		for (int k = 0; k < 7; k++)  // 計算agents數 
		{
			fullSum += fulltime[k];
			partSum += parttime[k];	
		}
		double sum = fullSum * priceFull + partSum * pricePart;  // 計算totol cost
		if (sum < sumMin)  // 若totol cost比最小值小，changeMin = 1 
			changeMin = 1;
		else if (sum == sumMin)  // 若total cost相同 
		{
			if(fullSum < fullMin)  // 比較number of full-time agents
				changeMin = 1;
			else if (fullSum == fullMin)  // 若number of full-time agents相同 
				if (fulltime[i] < startMin)  // 比較index of starting day 
					changeMin = 1;
		}
		
		if (changeMin == 1)  // 替換最小值 
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
		for (int k = 0; k < 7; k++)  // 還原d陣列中的值
			d[k] = dMemo[k];
	}

	for (int i = 0; i < 6; i++)  // 輸出 
		cout << fullBest[i] << " ";
	cout << fullBest[6] << endl;
	for (int i = 0; i < 6; i++)
		cout << partBest[i] << " ";
	cout << partBest[6];
	
	return 0;
}
