#include <iostream>
using namespace std;

int main()
{
	int n = 0, m = 0, seqMain[1000] = {0}, seqTarget[50] = {0}, num = 0;
	// seqMain: Main sequence // seqTarget: Target sequence
	// num: 若Target sequence存在於Main sequence，紀錄seqTarget[0]在Main sequence的位置 
	bool exist = 0; 
	/*exist: 判斷Target sequence是否存在於Main sequence 
	若存在為1，不存在為0*/
	
	cin >> n;  // 輸入Main sequence 
	for (int i = 0; i < n; i++)
		cin >> seqMain[i];
	
	cin >> m;  // 輸入Target sequence
	for (int j = 0; j < m; j++)
		cin >> seqTarget[j];
	
	for (int i = 0; (i < n - m + 1) && (exist != 1); i++) // i: Main sequence裡第i + 1項
	{
		/*若Target sequence存在於Main sequence，
		則其首項(seqTarget[0])必與Main sequence裡其中一數相同， 
		故先檢測seqTarget[0]是否和seqMain[i]相等，再檢測數列是否存在於Main sequence*/
		
		if (seqTarget[0] == seqMain[i])
		{
			exist = 1;
			num = i;  // 若Target sequence的首項與seqMain[i]相同，紀錄當時的i值(位置) 
			
			for (int k = i, j = 0; j < m; k++, j++)  // 檢查數列裡的每一項是否和seqMain[i] ~ seqMain[i+m-1]相同 
			{
				if (seqTarget[j] != seqMain[k])  
				{
					exist = 0;
					break;
					//若Target sequence內有數和Main sequence的不相同，exist = 0並跳出此迴圈 
				}
			}	
		}
	}
	
	
	if (exist == 0)  //若Target sequence不存在於Main sequence，輸出0 
		cout << exist;
	else
		cout << num + 1;  //若存在，輸出其在Main sequence的位置 (第num+1項) 
		
	return 0;
}
