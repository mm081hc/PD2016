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
	
	while (cin >> x)  // ��Jx 
	{
		plate++; 
		if (x != 0)  // �Yx = -1, 1~4�Ahitwalk + 1 
			hitwalk++;
		if (x != -1)  // �Yx = 0~4�Aatbat + 1 
			atbat++;
		if (x != 0 && x != -1) // �Yx = 1~4�Ahit + 1�A�p��base�`�M 
		{
			hit++;
			baseTotal += x;
		}
	}
	
	/* �p��ܤp���I��T��õL����˥h����k: 
	�N���l���H1000��A���H����(���ɬ�int�A�l�ƳQ�˱�) 
	��X���ഫ��float�A�A���H1000
	�å�fixed�Bsetprecision�O���ܤp���I��ĤT�� */

	OBP = hitwalk * 1000 / plate; 
	if (atbat == 0)  // �Y������0�A�h�Ȭ�0 
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
