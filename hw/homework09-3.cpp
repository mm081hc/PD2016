#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

int main()
{
	char input[10000] = {0};  // 輸入的句子 
	char delim[7] = {' ', '-', '.', ',', '?', '!'};  // 分割符號
	char search[10][50] = {0};  // keywords
	int containNum[10] = {0};  // 計算單字出現數量
	
	cin.getline(input, 10000);  // 輸入句子 
	for (int i = 0; i < strlen(input); i++)  // 將輸入的句子全部轉為小寫 
		if (isupper(input[i]) != 0)
			input[i] = tolower(input[i]);

	int num = 0;  // num: keywords數		
	while (cin >> search[num])  // 輸入keywords
	{
		for (int i = 0; i < strlen(search[num]); i++)  // 將輸入的keywords全部轉為小寫 
			if (isupper(search[num][i]) != 0)
				search[num][i] = tolower(search[num][i]);
		num++;
	}

	char* start = strtok(input, delim);  // start: 紀錄第一個單字處 
	while (start != nullptr) 
	{
		for (int i = 0; i < num; i++)  // 對比keywords(和search[i]比較) 
			if (strcmp(start, search[i]) == 0)
				containNum[i]++;  // 若與keywords(search[i])相同，數量(containNum[i])++
		start = strtok(nullptr, delim);  // 將start設為下一個單字，若沒有則停止迴圈 
	}
	
	for (int i = 0; i < num - 1; i++)  // 輸出數量 
		cout << containNum[i] << " ";
	cout << containNum[num-1];
	
	return 0;
 } 
