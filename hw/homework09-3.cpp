#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

int main()
{
	char input[10000] = {0};  // ��J���y�l 
	char delim[7] = {' ', '-', '.', ',', '?', '!'};  // ���βŸ�
	char search[10][50] = {0};  // keywords
	int containNum[10] = {0};  // �p���r�X�{�ƶq
	
	cin.getline(input, 10000);  // ��J�y�l 
	for (int i = 0; i < strlen(input); i++)  // �N��J���y�l�����ର�p�g 
		if (isupper(input[i]) != 0)
			input[i] = tolower(input[i]);

	int num = 0;  // num: keywords��		
	while (cin >> search[num])  // ��Jkeywords
	{
		for (int i = 0; i < strlen(search[num]); i++)  // �N��J��keywords�����ର�p�g 
			if (isupper(search[num][i]) != 0)
				search[num][i] = tolower(search[num][i]);
		num++;
	}

	char* start = strtok(input, delim);  // start: �����Ĥ@�ӳ�r�B 
	while (start != nullptr) 
	{
		for (int i = 0; i < num; i++)  // ���keywords(�Msearch[i]���) 
			if (strcmp(start, search[i]) == 0)
				containNum[i]++;  // �Y�Pkeywords(search[i])�ۦP�A�ƶq(containNum[i])++
		start = strtok(nullptr, delim);  // �Nstart�]���U�@�ӳ�r�A�Y�S���h����j�� 
	}
	
	for (int i = 0; i < num - 1; i++)  // ��X�ƶq 
		cout << containNum[i] << " ";
	cout << containNum[num-1];
	
	return 0;
 } 
