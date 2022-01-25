#include <iostream>
using namespace std;

int main()
{
	int n = 0, r[210] = {0}, s[210] = {0}, team = 0, winNum = 0, loseNum = 0;
	double win[22] = {0}, game[22] = {0};
	double pro = 0, max = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i] >> r[i];
		game[s[i]]++;
		if (r[i] == 1)
		{
			win[s[i]]++;
		}
	}
	
//	for (int i = 1; i <= 21; i++)
//		cout << game[i] << " " << win[i] << endl;
	
	for (int i = 1; i <= 21; i++)
	{
		pro = win[i] / game[i];
		if (pro > max)
		{
			max = pro;
			team = i;
			winNum = win[i];
			loseNum = game[i] - win[i];
		}
//		cout << pro << " " << max << endl;
	}
	// ¿é¤J¶W¹L21¿é¥X0 
	
	cout << team << " " << winNum << " " << loseNum;
	return 0;
}
