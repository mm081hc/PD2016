#include <iostream>
using namespace std;

int main()
{
	double white = 0, black = 0;
	// white: M white balls // black: N black balls 
	int whiteL = 0, whiteH = 0, blackL = 0, blackH = 0;
	// whiteL: mL // whiteH: mH // blackL: nL // blackH: nH
	cin >> white >> black >> whiteL >> whiteH >> blackL >> blackH;
	
	int whitePos = 0, blackPos = 0;
	// whitePos: m white balls in box1
	// blackPos: n black balls in box1
	double winChance = 0, max = 0;
	// winChance: winning chance in box1 + winning chance in box2
	// max: max of winning chance
	
	for (double i = whiteL; i <= whiteH; i++) // put i white balls in box1
	{
		for (double j = blackL; j <= blackH; j++) // put j black balls in box1
		{
			winChance = (white - i) / (white + black - i - j) + i / (i + j);
			// winning chance in box1 = (white - i) / (white + black - i - j)
			// winning chance in box2 = i / (i + j)
			
			if (winChance > max)  // if winChance > max, record i & j 
			{
				max = winChance;
				whitePos = i;
				blackPos = j;
			}
		}
	}
	
	cout << whitePos << " " << blackPos;
	
	return 0;
}
