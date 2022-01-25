#include <iostream>
using namespace std;

int main()
{
	int nodeNum = 0, edgeNum = 0;  // nodeNum: 輸入的n // edgeNum: 輸入的m 
	int node[30010][2] = {0}, edge[10010] = {0}, path[10010] = {0};
	// node: 輸入的node // edge: 計算node的相鄰數 // path: 輸入的path 
	cin >> nodeNum >> edgeNum;
	int** adjacList = new int* [nodeNum+1];  // adjacList: adjacency list 
	for (int i = 0; i < edgeNum; i++)
	{
		cin >> node[i][0] >> node[i][1];  // 將輸入的值記在node 
		edge[node[i][0]]++;  // 計算node[i][0], node[i][1]相鄰數的個數，存入edge 
		edge[node[i][1]]++;
	}
	for (int i = 1; i <= nodeNum; i++)  // 從adjacList[1]開始(方便對應輸入的path) 
		adjacList[i] = new int [edge[i]];  // 開動態二維陣列

	int count[10010] = {0};  // count: 紀錄分配至adjacList[i][j]的j值
	for (int i = 0; i < edgeNum; i++)  // 將輸入的值分配到adjacList陣列內 
	{
		adjacList[node[i][0]][count[node[i][0]]] = node[i][1];  // 對應node[i][0]行 
		adjacList[node[i][1]][count[node[i][1]]] = node[i][0];  // 對應node[i][1]行 
		count[node[i][0]]++; 
		count[node[i][1]]++;
	}
	
	int pathNum = 0;
	while (cin >> path[pathNum])  // 輸入path 
		pathNum++;

	bool exist = 0;  // 檢查兩數是否相連，若相連則為1 
	for (int i = 0; i < pathNum - 1; i++)
	{
		for (int j = 0; j < edge[path[i]]; j++)  
			if (path[i+1] == adjacList[path[i]][j])
				exist = 1;  // 找path[i]的陣列，若path[i+1]與其中的數相等，則為相連(exist設為1) 
				
		if (exist == 0)  // 若不相連，輸出兩數 
		{
			if (path[i] <= path[i+1])
				cout << path[i] << " " << path[i+1] << endl;
			else
				cout << path[i+1] << " " << path[i] << endl;
		}
		exist = 0;  // 將exist重設為0 
	}
	
	return 0;
}
