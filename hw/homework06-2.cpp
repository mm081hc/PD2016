#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int x = 0;  // batting record
	int plate = 0, hit = 0, atbat = 0, hitwalk = 0, baseTotal = 0;
	// plate: plate appearances // hit: number of hits
	// hitwalk: number of hits and walks // baseTotal: number of total bases
	int AVG = 0, OBP = 0, SLG = 0;
	
	while (cin >> x)  // 輸入x 
	{
		plate++; 
		if (x != 0)  // 若x = -1, 1~4，hitwalk + 1 
			hitwalk++;
		if (x != -1)  // 若x = 0~4，atbat + 1 
			atbat++;
		if (x != 0 && x != -1) // 若x = 1~4，hit + 1，計算base總和 
		{
			hit++;
			baseTotal += x;
		}
	}
	
	/* 計算至小數點後三位並無條件捨去的方法: 
	將分子乘以1000後，除以分母(此時為int，餘數被捨棄) 
	輸出時轉換為float，再除以1000
	並用fixed、setprecision記錄至小數點後第三位 */

	OBP = hitwalk * 1000 / plate; 
	if (atbat == 0)  // 若分母為0，則值為0 
		AVG = SLG = 0;
	else
	{
		AVG = hit * 1000 / atbat;
		SLG = baseTotal * 1000 / atbat;
	}

	cout << fixed << setprecision(3) << static_cast<float>(AVG) / 1000 << " ";
	cout << fixed << setprecision(3) << static_cast<float>(OBP) / 1000 << " ";
	cout << fixed << setprecision(3) << static_cast<float>(SLG) / 1000;
	
	return 0;
}
