#include <iostream>
using namespace std;

int costTotal ()

int main()
{
	int demand[3][7] = {0}, demandDay[7] = {0}, demandSum = 0;;
	int fullWage = 0, partWage = 0, compen = 0, fullHired = 0;
	cin >> fullHired;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			cin >> demand[i][j];
			demandDay[i] += demand[i][j];
			demandSum += demand[i][j];
		}
	}  // ºâ¨C¤Ñªº? 
	cin >> fullWage >> partWage >> compen;
	
	int fullDay[7] = {0}, partDay[7] = {0};
	int fullSche[3][7] = {0}, partSche[3][7] = {0};
	
	demandSum = demandSum / 5;
	
	for (int i = 0; i < 7; i++)
	{
		fullDay[i] = demandDay[i] + demandDay[(i+2)%7] + demandDay[(i+4)%7] - 2 * demandSum;
	}
	
	
	return 0;
}
