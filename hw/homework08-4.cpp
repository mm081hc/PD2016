#include <iostream>
using namespace std;

int main()
{
	int nodeNum = 0, edgeNum = 0;  // nodeNum: ��J��n // edgeNum: ��J��m 
	int node[30010][2] = {0}, edge[10010] = {0}, path[10010] = {0};
	// node: ��J��node // edge: �p��node���۾F�� // path: ��J��path 
	cin >> nodeNum >> edgeNum;
	int** adjacList = new int* [nodeNum+1];  // adjacList: adjacency list 
	for (int i = 0; i < edgeNum; i++)
	{
		cin >> node[i][0] >> node[i][1];  // �N��J���ȰO�bnode 
		edge[node[i][0]]++;  // �p��node[i][0], node[i][1]�۾F�ƪ��ӼơA�s�Jedge 
		edge[node[i][1]]++;
	}
	for (int i = 1; i <= nodeNum; i++)  // �qadjacList[1]�}�l(��K������J��path) 
		adjacList[i] = new int [edge[i]];  // �}�ʺA�G���}�C

	int count[10010] = {0};  // count: �������t��adjacList[i][j]��j��
	for (int i = 0; i < edgeNum; i++)  // �N��J���Ȥ��t��adjacList�}�C�� 
	{
		adjacList[node[i][0]][count[node[i][0]]] = node[i][1];  // ����node[i][0]�� 
		adjacList[node[i][1]][count[node[i][1]]] = node[i][0];  // ����node[i][1]�� 
		count[node[i][0]]++; 
		count[node[i][1]]++;
	}
	
	int pathNum = 0;
	while (cin >> path[pathNum])  // ��Jpath 
		pathNum++;

	bool exist = 0;  // �ˬd��ƬO�_�۳s�A�Y�۳s�h��1 
	for (int i = 0; i < pathNum - 1; i++)
	{
		for (int j = 0; j < edge[path[i]]; j++)  
			if (path[i+1] == adjacList[path[i]][j])
				exist = 1;  // ��path[i]���}�C�A�Ypath[i+1]�P�䤤���Ƭ۵��A�h���۳s(exist�]��1) 
				
		if (exist == 0)  // �Y���۳s�A��X��� 
		{
			if (path[i] <= path[i+1])
				cout << path[i] << " " << path[i+1] << endl;
			else
				cout << path[i+1] << " " << path[i] << endl;
		}
		exist = 0;  // �Nexist���]��0 
	}
	
	return 0;
}
