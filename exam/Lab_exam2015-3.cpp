#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int B = 0, n = 0, w[10000] = {0}, box[10000] = {0}, unusedMax = 0, wNum = 0, boxNum = 0;
	cin >> B;
	for (int i = 0; ;i++)
	{
		cin >> w[i];
		if (w[i] == -1)
		{
			wNum = i;
			break;
		}
	}
	sort (w, w + wNum);
	reverse (w, w + wNum);
	
	for (int i = 0; i < wNum; i++)
	{
		for (int j = 0; j < wNum; j++)
		{
			if (box[j] + w[i] <= B)
			{
				box[j] += w[i];
				break;
			}
		}
	}
//	for (int i = 0; i < wNum; i++)
//		cout << w[i] << " ";
	for (int i = 0; i <= wNum; i++)
	{
		if (box[i] == 0)
		{
			boxNum = i;
			break;
		}
	}
	for (int i = 0; i < boxNum; i++)
	{
		if(B - box[i] > unusedMax)
			unusedMax = B - box[i];
	}
	
	cout << boxNum << " " << unusedMax;

	return 0;
}
