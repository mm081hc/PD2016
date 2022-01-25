#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <fstream>
#include <mmsystem.h>
#include <cstdlib>
using namespace std;

const int wid = 6;  // �e�� 
const int len = 23;  // ����
const int good = 200;
const int perfect = 300;
const char line = '|';
const char hit = '=';
const string space = "      ";
const string tempo = "------";
const string key = "������";  // ���ի��U��
double delay = 0;
int score = 0, combo = 0, accuracy = 0, comboMax = 0;
int goodCnt = 0, perfectCnt = 0, missCnt = 0;

HANDLE hIn = GetStdHandle (STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);

void gotoxy (int x, int y)
{// ����y�� 
    static COORD c;  
    c.X = x; c.Y = y;
    SetConsoleCursorPosition (hOut, c);
}
void SetCursorVisible(BOOL _bVisible,DWORD _dwSize)
{// ���ô�� 
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = _bVisible;
	CCI.dwSize = _dwSize;
	SetConsoleCursorInfo(hOut, &CCI);
}

class Tempo
{
private:
	int x;
	int y;
	string graph;
public:
	bool status;  // �����O�_�w���L(0: �����L, 1: �w���L)
	Tempo(string tem)
	{
		this->graph = tem;
		this->x = 0;
		this->y = 0;
		status = 0;
	}
	void set(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void draw()
	{
		gotoxy(this->x, this->y);
		cout << graph;
	}
	bool hitPerfect()
	{
		if (this->graph == tempo && status == 0)
			return true;
		return false;
	}
	bool hitGood(Tempo* ptr1, Tempo* ptr2, Tempo* ptr3)
	{
		if (this->graph == tempo && ptr1->graph == space && ptr2->graph == space
			&& ptr3->graph == space && this->status == 0)
			return true;
		return false;
	}
	bool hitBad(Tempo* ptr1, Tempo* ptr2, Tempo* ptr3, Tempo* ptr4)
	{
		if (this->graph == tempo && ptr1->graph == space && ptr2->graph == space
			&& ptr3->graph == space && ptr4->graph == space && this->status == 0)
			return true;
		return false;
	}
	bool hitMiss()
	{
		if (this->graph == tempo && this->status == 0)
			return true;
		return false;
	}
	void keyPerfect(short keyNum)
	{
		if (GetKeyState(keyNum) < 0)
		{
			gotoxy(40, 9);
			cout << "perfect!";
			score += perfect;
			perfectCnt++;	
			status = 1;
			combo++;
		}
	}
	void keyGood(short keyNum)
	{
		if (GetKeyState(keyNum) < 0)
		{
			gotoxy(40, 9);
			cout << "good!   ";
			score += good;
			goodCnt++;		
			status = 1;
			combo++;
		}	
	}
	void keyBad(short keyNum)
	{// miss
		if (GetKeyState(keyNum) < 0)
		{
			gotoxy(40, 9);
			cout << "miss!!!!";
			status = 1;
			missCnt++;
			combo = 0;
		}
	}
};

/* �C��memo 
0 = �¦� 1 = �Ŧ� 2 = ��� 3 = �ź�� 4 = ���� 5 = ����
6 = ���� 7 = �զ� 8 = �Ǧ� 9 = �H�Ŧ� 10 = �H���
11 = �H�ź�� 12 = �H���� 13 = �H���� 14 = �H���� 15 = �G�զ�
*/
void drawPlayStatic()
{// 4k
	gotoxy(40, 3);
	cout << "score: 0";
	gotoxy(40, 4);
	cout << "combo: 0";
	for (int i = 1; i < 6 + 4*wid; i += wid + 1)
	{
		for (int j = 0; j < len; j++)
		{	
			gotoxy(i, j);
			cout << line;
			if (j == len - 3 && i != 5 + 4*wid)
			{
				SetConsoleTextAttribute(hOut, 11);
				for (int k = 0; k < wid; k++)
				{
					cout << hit;
				}
				SetConsoleTextAttribute(hOut, 7);
			}
		}
	}
}
void drawPlayStatic5k()
{// 5k
	gotoxy(40, 3);
	cout << "score: 0";
	gotoxy(40, 4);
	cout << "combo: 0";
	for (int i = 1; i < 7 + 5*wid; i += wid + 1)
	{
		for (int j = 0; j < len; j++)
		{	
			gotoxy(i, j);
			cout << line;
			if (j == len - 3 && i != 6 + 5*wid)
			{
				SetConsoleTextAttribute(hOut, 11);
				for (int k = 0; k < wid; k++)
				{
					cout << hit;
				}
				SetConsoleTextAttribute(hOut, 7);
			}
		}
	}
}

void drawMainStatic()
{
	gotoxy(2, 0);
	for (int i = 0; i < 25; i++)
		cout << "��";
	gotoxy(2, 12);
	for (int i = 0; i < 25; i++)
		cout << "��";
	gotoxy(15, 13);
	cout << "-press SPACE to continue-";
}
void drawMainButton()
{
	for (int i = 1; i < 11; i++)
	{// �M�ū��� 
		gotoxy(2, i);
		for (int j = 0; j < 50; j++)
			cout << " ";
	}
	gotoxy(18, 2);
	cout << "= = = = = = = = =";
	gotoxy(21, 3);
	cout << " MUSIC GAME ";
	gotoxy(18, 4);
	cout << "= = = = = = = = =";
	gotoxy(22, 6);
	cout << "Game Start";
	gotoxy(22, 7);
	cout << "Tutorial";
	gotoxy(22, 8);
	cout << "Rank";
	gotoxy(22, 9);
	cout << "Quit";	
	gotoxy(19, 6);
	cout << "��";
}
void tutorial()
{
	system("CLS");  // �M���e��	
	drawPlayStatic();
	gotoxy(2, 5);
	cout << tempo;
	gotoxy(2, 7);
	cout << tempo;
	gotoxy(9, 9);
	cout << tempo;
	gotoxy(9, 15);
	cout << tempo;
	gotoxy(16, 12);
	cout << tempo;
	gotoxy(23, 19);
	cout << tempo;
	gotoxy(40, 3);
	cout << "        ";
	gotoxy(40, 4);
	cout << "        ";
	gotoxy(5, len - 2);
	cout << "D";
	gotoxy(12, len - 2);
	cout << "F";
	gotoxy(19, len - 2);
	cout << "J";
	gotoxy(26, len - 2);
	cout << "K";
	gotoxy(35, 1);
	cout << "�C������: ";
	gotoxy(35, 3);
	cout << "1. �y�D�ѥ��ܥk�ҹ���������";
	gotoxy(35, 4);
	cout << "   4k�̧Ǭ�D, F, J, K�C5k��";
	gotoxy(35, 5);
	cout << "   �Ǭ�D, F, SPACE, J, K�C";
	gotoxy(35, 6);	
	cout << "2. �ݦb�`��(------)���U����";
	gotoxy(35, 7); 
	cout << "   �����ɡA���U�۹�������";
	gotoxy(35, 8);
	cout << "   ��C";
	gotoxy(35, 9);
	cout << "3. �C���|�̾ګ��U���ɶ��I��";
	gotoxy(35, 10);
	cout << "   �����P���ơA�@��perfect,";
	gotoxy(35, 11);
	cout << "   good, miss�T�ءC";
	gotoxy(35, 12);
	cout << "4. ���ֵ����ɷ|�̾ڹC������";
	gotoxy(35, 13);
	cout << "   ���X���P�����C";
	gotoxy(35, 15);
	cout << "���`�N �Y�n�ɨ��̨ιC���ĪG";
	gotoxy(35, 16);
	cout << "  ��ĳ�ϥεw�鬰�ѳ����q��";
	gotoxy(35,18);
	cout << "  -press SPACE to continue-";
	Sleep(500);
	while (1)
	{
		if (GetKeyState(VK_SPACE) < 0)
		{
			system("CLS");
			drawMainStatic();
			drawMainButton();			
			break;
		}
	}	
}

void tempoDrop(Tempo* ptr1[], Tempo* ptr2[], Tempo* ptr3[], Tempo* ptr4[], int tempoNum, int song)
{
	score = combo = comboMax = 0;
	goodCnt = perfectCnt = missCnt = 0;	
	clock_t t1, t2, tStart, tEnd;
//	int count = 0;
//	double time[550] = {0};  // �����ɶ�
//	int nMemo[550] = {0};
//	tStart = clock();  // �_�l�ɶ�			
	for (int i = 0; i < tempoNum; i++)
	{
		t1 = clock();
		int n = i + len - 1;
		if (combo > comboMax)  // ����max combo 
			comboMax = combo;
		for (int j = 0; j < len; j++)
		{
			ptr1[n]->set(2, j);
            ptr2[n]->set(9, j);
            ptr3[n]->set(16, j);
            ptr4[n]->set(23, j);											
			if (j >= len - 2) SetConsoleTextAttribute(hOut, 8);
			if (j == len - 3)
			{// perfect
			/*	t2 = clock();  // perfect�ɶ� 
				time[count] = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
				nMemo[count] = n;
				count++;
			*/	if (n == len) 
				{
					if (song == 1)
						PlaySound(TEXT("song1.wav"), NULL, SND_ASYNC); 
					else if (song == 2)
						PlaySound(TEXT("xi-parousia.wav"), NULL, SND_ASYNC);
					else if (song == 3)
						PlaySound(TEXT("Kabaneri.wav"), NULL, SND_ASYNC);
					else if (song == 4)
						PlaySound(TEXT("AOD SS OP2.wav"), NULL, SND_ASYNC);
					else if (song == 5)
						PlaySound(TEXT("Reverence.wav"), NULL, SND_ASYNC);			
				}     
				if (ptr1[n]->hitPerfect()) ptr1[n]->keyPerfect(68);  // D: 68
				else if (ptr2[n]->hitPerfect()) ptr2[n]->keyPerfect(70);  // F: 70
				else if (ptr3[n]->hitPerfect()) ptr3[n]->keyPerfect(74);  // J: 74
				else if (ptr4[n]->hitPerfect())	ptr4[n]->keyPerfect(75);  // K: 75				
				n--;
				continue;		
			}       
			ptr1[n]->draw();
            ptr2[n]->draw();
            ptr3[n]->draw();
            ptr4[n]->draw();
        	if (j >= len - 2) SetConsoleTextAttribute(hOut, 7);
            if (j == len - 1){
				if (ptr1[n]->hitMiss() || ptr2[n]->hitMiss() || ptr3[n]->hitMiss() || ptr4[n]->hitMiss())
            	{// miss
            		combo = 0;
            		missCnt++; 
            		gotoxy(40, 9);
            		cout << "miss!!!!";
				}		
			}
			if (j == len - 2)
			{// good 
            	if(ptr1[n]->hitPerfect()) ptr1[n]->keyGood(68);  // D: 68
				else if (ptr2[n]->hitPerfect()) ptr2[n]->keyGood(70);  // F: 70
				else if (ptr3[n]->hitPerfect()) ptr3[n]->keyGood(74);  // J: 74
				else if (ptr4[n]->hitPerfect()) ptr4[n]->keyGood(75);  // K: 75				
			}
            if (j == len - 4)
            {// perfect
            	if (ptr1[n]->hitPerfect()) ptr1[n]->keyPerfect(68);  // D: 68
				else if (ptr2[n]->hitPerfect()) ptr2[n]->keyPerfect(70);  // F: 70
				else if (ptr3[n]->hitPerfect()) ptr3[n]->keyPerfect(74);  // J: 74
				else if (ptr4[n]->hitPerfect())	ptr4[n]->keyPerfect(75);  // K: 75            	
			}
			if (n > 2 && j == len - 5)
			{// good 
            	if(ptr1[n]->hitGood(ptr1[n-1], ptr1[n-2], ptr1[n-3]))
					ptr1[n]->keyGood(68);  // D: 68
				else if (ptr2[n]->hitGood(ptr2[n-1], ptr2[n-2], ptr2[n-3]))
					ptr2[n]->keyGood(70);  // F: 70
				else if (ptr3[n]->hitGood(ptr3[n-1], ptr3[n-2], ptr3[n-3]))
					ptr3[n]->keyGood(74);  // J: 74
				else if (ptr4[n]->hitGood(ptr4[n-1], ptr4[n-2], ptr4[n-3]))
					ptr4[n]->keyGood(75);  // K: 75				
			}
			if (n > 3 && j == len - 6)
			{// bad (miss)
            	if(ptr1[n]->hitBad(ptr1[n-1], ptr1[n-2], ptr1[n-3], ptr1[n-4]))
					ptr1[n]->keyBad(68);  // D: 68
				else if (ptr2[n]->hitBad(ptr2[n-1], ptr2[n-2], ptr2[n-3], ptr3[n-4]))
					ptr2[n]->keyBad(70);  // F: 70
				else if (ptr3[n]->hitBad(ptr3[n-1], ptr3[n-2], ptr3[n-3], ptr3[n-4]))
					ptr3[n]->keyBad(74);  // J: 74
				else if (ptr4[n]->hitBad(ptr4[n-1], ptr4[n-2], ptr4[n-3], ptr4[n-4]))
					ptr4[n]->keyBad(75);  // K: 75
			}
			n--;
		}
		gotoxy(47, 3);
		cout << score;
		gotoxy(47, 4);
		cout << "      ";
		gotoxy(47, 4);		
		cout << combo;
		t2 = clock();
		while (t2 - t1 < delay)
		{
			t2 = clock();
		}
//		tEnd = clock();
//		time[count] = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
//		count++;				
	}
	SetConsoleTextAttribute(hOut, 7);
/*	ofstream file;
	file.open("song1memoPAM.txt");
	for (int i = 0; i < 500; i++)
		file << time[i] << endl;
	file.close();
*/
}

void tempoDrop5k(Tempo* ptr1[], Tempo* ptr2[], Tempo* ptr3[], Tempo* ptr4[], Tempo* ptr5[], int tempoNum, int song)
{
	score = combo = comboMax = 0;
	goodCnt = perfectCnt = missCnt = 0;	
	clock_t t1, t2, tStart, tEnd;		
	for (int i = 0; i < tempoNum; i++)
	{
		t1 = clock();
		int n = i + len - 1;
		if (combo > comboMax)  // ����max combo 
			comboMax = combo;
		for (int j = 0; j < len; j++)
		{
			ptr1[n]->set(2, j);
            ptr2[n]->set(9, j);
            ptr3[n]->set(16, j);
            ptr4[n]->set(23, j);
            ptr5[n]->set(30, j);
			if (j >= len - 2) SetConsoleTextAttribute(hOut, 8);
			if (j == len - 3)
			{// perfect
				if (n == len) 
						PlaySound(TEXT("Darkness.wav"), NULL, SND_ASYNC);
				if (ptr1[n]->hitPerfect()) ptr1[n]->keyPerfect(68);  // D: 68
				if (ptr2[n]->hitPerfect()) ptr2[n]->keyPerfect(70);  // F: 70
				if (ptr3[n]->hitPerfect())	ptr3[n]->keyPerfect(32);  // space: 32	
				if (ptr4[n]->hitPerfect()) ptr4[n]->keyPerfect(74);  // J: 74
				if (ptr5[n]->hitPerfect())	ptr5[n]->keyPerfect(75);  // K: 75						
				n--;
				continue;		
			}       
			ptr1[n]->draw();
            ptr2[n]->draw();
            ptr3[n]->draw();
            ptr4[n]->draw();
            ptr5[n]->draw();
        	if (j >= len - 2) SetConsoleTextAttribute(hOut, 7);
            if (j == len - 1){
				if (ptr1[n]->hitMiss() || ptr2[n]->hitMiss() || ptr3[n]->hitMiss() || ptr4[n]->hitMiss() || ptr5[n]->hitMiss())
            	{// miss
            		combo = 0;
            		missCnt++; 
            		gotoxy(40, 9);
            		cout << "miss!!!!";
				}		
			}
			if (j == len - 2)
			{// good 
            	if(ptr1[n]->hitPerfect()) ptr1[n]->keyGood(68);  // D: 68
				if (ptr2[n]->hitPerfect()) ptr2[n]->keyGood(70);  // F: 70
				if (ptr3[n]->hitPerfect()) ptr3[n]->keyGood(32);  // space: 32	
				if (ptr4[n]->hitPerfect()) ptr4[n]->keyGood(74);  // J: 74
				if (ptr5[n]->hitPerfect())	ptr5[n]->keyGood(75);  // K: 75
			}
            if (j == len - 4)
            {// perfect
				if (ptr1[n]->hitPerfect()) ptr1[n]->keyPerfect(68);  // D: 68
				if (ptr2[n]->hitPerfect()) ptr2[n]->keyPerfect(70);  // F: 70
				if (ptr3[n]->hitPerfect())	ptr3[n]->keyPerfect(32);  // space: 32	
				if (ptr4[n]->hitPerfect()) ptr4[n]->keyPerfect(74);  // J: 74
				if (ptr5[n]->hitPerfect())	ptr5[n]->keyPerfect(75);  // K: 75
			}
			if (n > 2 && j == len - 5)
			{// good 
            	if(ptr1[n]->hitGood(ptr1[n-1], ptr1[n-2], ptr1[n-3]))
					ptr1[n]->keyGood(68);  // D: 68
				if (ptr2[n]->hitGood(ptr2[n-1], ptr2[n-2], ptr2[n-3]))
					ptr2[n]->keyGood(70);  // F: 70
				if (ptr3[n]->hitGood(ptr3[n-1], ptr3[n-2], ptr3[n-3]))
					ptr3[n]->keyGood(32);  // space: 32
				if (ptr4[n]->hitGood(ptr4[n-1], ptr4[n-2], ptr4[n-3]))
					ptr4[n]->keyGood(74);  // J: 74
				if (ptr5[n]->hitGood(ptr5[n-1], ptr5[n-2], ptr5[n-3]))
					ptr5[n]->keyGood(75);  // K: 75	
			}
			if (n > 3 && j == len - 6)
			{// bad (miss)
            	if(ptr1[n]->hitBad(ptr1[n-1], ptr1[n-2], ptr1[n-3], ptr1[n-4]))
					ptr1[n]->keyBad(68);  // D: 68
				if (ptr2[n]->hitBad(ptr2[n-1], ptr2[n-2], ptr2[n-3], ptr3[n-4]))
					ptr2[n]->keyBad(70);  // F: 70
				if (ptr3[n]->hitBad(ptr3[n-1], ptr3[n-2], ptr3[n-3], ptr3[n-4]))
					ptr3[n]->keyBad(32);  // space: 32
				if (ptr4[n]->hitBad(ptr4[n-1], ptr4[n-2], ptr4[n-3], ptr4[n-4]))
					ptr4[n]->keyBad(74);  // J: 74
				if (ptr5[n]->hitBad(ptr5[n-1], ptr5[n-2], ptr5[n-3], ptr5[n-4]))
					ptr5[n]->keyBad(75);  // K: 75				
			}
			n--;
		}
		gotoxy(47, 3);
		cout << score;
		gotoxy(47, 4);
		cout << "      ";
		gotoxy(47, 4);		
		cout << combo;
		t2 = clock();
		while (t2 - t1 < delay)
		{
			t2 = clock();
		}				
	}
	SetConsoleTextAttribute(hOut, 7);

}
void keyinRank(string name, int score, int song);
void ranking();
void putRank(int);

void gameStart(int song)
{
	system("CLS");  // �M���e��	
	Tempo* ptr1[5000];
    Tempo* ptr2[5000];
    Tempo* ptr3[5000];
    Tempo* ptr4[5000];
    Tempo* ptr5[5000];    
	int c1[5000] = {0};
	int c2[5000] = {0};
	int c3[5000] = {0};
	int c4[5000] = {0};
	int c5[5000] = {0};
	int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, tempoNum = 0;
	if (song == 6) 
		drawPlayStatic5k();
	else
		drawPlayStatic();
	ifstream songFile;
	if (song == 1)
		songFile.open("granat46.5055.txt");
	else if (song == 2)
		songFile.open("parousia41.274.txt");
	else if (song == 3)
		songFile.open("kabaneri45.7053.txt");
	else if (song == 4)
		songFile.open("aod48.367749.txt");
	else if (song == 5)
		songFile.open("Reverence.txt");
	else if (song == 6)
		songFile.open("Darkness.txt");		
	songFile >> tempoNum >> delay; // tempo��
	while (!songFile.eof())
	{// Ū�� 
		double x = 0;
		int c = 0;
		songFile >> x >> c;
		if (c == 0)
		{
			songFile >>	c1[num1];		
			num1++;		
		}
		else if (c == 1)
		{
			songFile >>	c2[num2];
			num2++;		
		}
		else if (c == 2)
		{
			songFile >>	c3[num3];
			num3++;		
		}
		else if (c == 3)
		{
			songFile >>	c4[num4];
			num4++;		
		}
		else if (c == 4)
		{
			songFile >>	c5[num5];
			num5++;				
		}					
	}
	num1 = num2 = num3 = num4 = num5 = 0;
	for(int i = 0; i < tempoNum + 2 * len; i++) {// �]�w�`�� 
		if (i < len || i >= tempoNum)
		{
			ptr1[i] = new Tempo(space);
			ptr2[i] = new Tempo(space);
			ptr3[i] = new Tempo(space);
			ptr4[i] = new Tempo(space);
			ptr5[i] = new Tempo(space);									
		}
        else{
	        if(i == c1[num1] + len - 1){
	        	ptr1[i] = new Tempo(tempo);
				num1++;	
			}
	        else ptr1[i] = new Tempo(space);
	        if(i == c2[num2] + len - 1){
	        	ptr2[i] = new Tempo(tempo);
	        	num2++;
			}  
	        else ptr2[i] = new Tempo(space);
	        if(i == c3[num3] + len - 1){
	        	ptr3[i] = new Tempo(tempo);
	        	num3++;
			}
	        else ptr3[i] = new Tempo(space);
	        if(i == c4[num4] + len - 1){
	        	ptr4[i] = new Tempo(tempo);
	        	num4++;
			}
	        else ptr4[i] = new Tempo(space);
	        if(i == c5[num5] + len - 1){
	        	ptr5[i] = new Tempo(tempo);
	        	num5++;
			}
	        else ptr5[i] = new Tempo(space);	        
		}
	}	
	songFile.close();
	if (song == 6)
		tempoDrop5k(ptr1, ptr2, ptr3, ptr4, ptr5, tempoNum, song);
	else
		tempoDrop(ptr1, ptr2, ptr3, ptr4, tempoNum, song);
	for (int i = 0; i < tempoNum + 2 * len; i++)
	{// delete
		delete ptr1[i];
		delete ptr2[i];
		delete ptr3[i];
		delete ptr4[i];
		delete ptr5[i];						
	}
// ����
	system("CLS");  // �M���e��
	while (kbhit()) getch();  // �M������Ȧs	
	Sleep(100);
	accuracy = (1.5*perfectCnt + 1.25*goodCnt) * 100 / (1.5 * (perfectCnt+goodCnt+missCnt));
	gotoxy(2, 0);
	for (int i = 0; i < 22; i++)
		cout << "��";
	gotoxy(2, 13);
	for (int i = 0; i < 22; i++)
		cout << "��";
	for (int i = 0; i < 12; i++)
	{
		gotoxy(2, 1 + i);
		cout << "|";
		gotoxy(45, 1 + i);
		cout << "|";
	}
	gotoxy(10, 2);		
	if (song == 1)
		cout << "Granat";
	else if (song == 2)
		cout << "Parousia";
	else if (song == 3)
		cout << "Kabaneri of the Iron Fortress";
	else if (song == 4)
		cout << "Sora ga Aozora de aru tame ni";
	else if (song == 5)
		cout << "Reverence";
	else if (song == 6)
		cout << "Darkness";
	gotoxy(10, 4);
	cout << "Score: " << score;
	gotoxy(10, 5);
	cout << "Max Combo: " << comboMax;
	gotoxy(10, 6);
	cout << "Perfect: " << perfectCnt;
	gotoxy(10, 7);
	cout << "Good: " << goodCnt;
	gotoxy(10, 8);
	cout << "Miss: " << missCnt;
	gotoxy(10, 10);
	cout << "Accuracy: " << accuracy << "%";
	gotoxy(10, 11);
	cout << "Rank: ";
	if (accuracy < 70)
		cout << "D";
	else if (accuracy < 80)
		cout << "C";
	else if (accuracy < 90)
		cout << "B";
	else if (accuracy < 95)
		cout << "A";
	else 
		cout << "S";
	gotoxy(23, 11);
	if (missCnt == 0 && goodCnt == 0)
		cout << "<full perfect!>";
	else if (missCnt == 0)
		cout << "<full combo!>";			
// rank
	string name;
	SetCursorVisible(true, 10);  // ��ܴ��
	gotoxy(2, 14);
	cout << "please enter your name:";
	cin >> name;
	SetCursorVisible(false, 100);  // ���ô��
	keyinRank(name, score, song);
	gotoxy(2, 15);
	cout << "-press SPACE to continue-";
	while (1){
		if (GetKeyState(VK_SPACE) < 0)
			break;
	}
	putRank(song);
}
void chooseSong()
{// ��q
	for (int i = 1; i < 11; i++)
	{// �M�ū��� 
		gotoxy(2, i);
		for (int j = 0; j < 50; j++)
			cout << " ";
	}
// x: 13, y: 3~9	
	gotoxy(13, 3);
	cout << "Granat(4k)";  // song1
	gotoxy(13, 4);
	cout << "Parousia(4k)";  // song2
	gotoxy(13, 5);
	cout << "Kabaneri of the Iron Fortress(4k)";  // song3
	gotoxy(13, 6);
	cout << "Sora ga Aozora de aru tame ni(4k)";  // song4
	gotoxy(13, 7);
	cout << "Reverence(4k)";  // song5
	gotoxy(13, 8);
	cout << "Darkness(5k)";
	gotoxy(13, 9);
	cout << "Back";
	gotoxy(10, 3);
	cout << "��";	
	int status = 1; // 0: back, 1: song1, 2: song2, 3: song3, 4: song4, 5: song5, 6: song6
	Sleep(300);
	while (1)
	{
		if (status == 1)
		{		
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(10, 3);
				cout << "   ";
				gotoxy(10, 9);
				cout << "��";
				status = 0;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(10, 3);
				cout << "   ";
				gotoxy(10, 4);
				cout << "��";
				status = 2;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song1 
				gameStart(1);
				drawMainStatic();				
				break;
			}
		}
		else if (status == 2)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(10, 4);
				cout << "   ";
				gotoxy(10, 3);
				cout << "��";
				status = 1;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(10, 4);
				cout << "   ";
				gotoxy(10, 5);
				cout << "��";
				status = 3;
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song2
				gameStart(2);
				drawMainStatic();		
				break;
			}
		}
		else if (status == 3)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(10, 5);
				cout << "   ";
				gotoxy(10, 4);
				cout << "��";
				status = 2;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(10, 5);
				cout << "   ";
				gotoxy(10, 6);
				cout << "��";
				status = 4;				
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song3
				gameStart(3);
				drawMainStatic();
				break;
			}			
		}
		else if (status == 4)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(10, 6);
				cout << "   ";
				gotoxy(10, 5);
				cout << "��";
				status = 3;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(10, 6);
				cout << "   ";
				gotoxy(10, 7);
				cout << "��";
				status = 5;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song4
				gameStart(4);
				drawMainStatic();		
				break;
			}			
		}
		else if (status == 5)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(10, 7);
				cout << "   ";
				gotoxy(10, 6);
				cout << "��";
				status = 4;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(10, 7);
				cout << "   ";
				gotoxy(10, 8);
				cout << "��";
				status = 6;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song5
				gameStart(5);
				drawMainStatic();		
				break;
			}			
		}
		else if (status == 6)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(10, 8);
				cout << "   ";
				gotoxy(10, 7);
				cout << "��";
				status = 5;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(10, 8);
				cout << "   ";
				gotoxy(10, 9);
				cout << "��";
				status = 0;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// back
				gameStart(6);
				drawMainStatic();		
				break;
			}				
		}
		else if (status == 0)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(10, 9);
				cout << "   ";
				gotoxy(10, 8);
				cout << "��";
				status = 6;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(10, 9);
				cout << "   ";
				gotoxy(10, 3);
				cout << "��";
				status = 1;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// back
				break;
			}				
		}		
		Sleep(100);
	}	
}
void drawRanking()
{
	system("CLS");
	drawMainStatic();//�e�n�ج[ 
	for (int i = 1; i < 11; i++)
	{// �M�ū��� 
		gotoxy(2, i);
		for (int j = 0; j < 50; j++)
			cout << " ";
	}
	gotoxy(10, 2);
	cout << "Ranking";
	gotoxy(10, 4);
	cout << "Granat(4k)";  // song1
	gotoxy(10, 5);
	cout << "Parousia(4k)";  // song2
	gotoxy(10, 6);
	cout << "Kabaneri of the Iron Fortress(4k)";  // song3
	gotoxy(10, 7);
	cout << "Sora ga Aozora de aru tame ni(4k)";  // song4
	gotoxy(10, 8);
	cout << "Reverence(4k)";  // song5
	gotoxy(10, 9);
	cout << "Darkness(5k)";
	gotoxy(10, 10);
	cout << "Back";
	gotoxy(7, 4);
	cout << "��";
}


int main ()
{
	SetCursorVisible(false, 100);  // ���ô��	
	drawMainStatic();
	drawMainButton();
	int status = 1;  // 0: quit, 1: start, 2: tutorial, 3: rank
	while (1)
	{
		if (status == 1)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(19, 6);
				cout << "   ";
				gotoxy(19, 9);
				cout << "��";
				status = 0;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(19, 6);
				cout << "   ";
				gotoxy(19, 7);
				cout << "��";
				status = 2;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// ��q 
				chooseSong();
				drawMainButton();				
				Sleep(300);
			}
		}
		else if (status == 2)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(19, 7);
				cout << "   ";
				gotoxy(19, 6);
				cout << "��";
				status = 1;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(19, 7);
				cout << "   ";
				gotoxy(19, 8);
				cout << "��";
				status = 3;
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// �C������ 
				tutorial();
				status = 1;
				Sleep(300);
			}
		}
		else if (status == 3)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(19, 8);
				cout << "   ";
				gotoxy(19, 7);
				cout << "��";
				status = 2;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(19, 8);
				cout << "   ";
				gotoxy(19, 9);
				cout << "��";
				status = 0;				
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// rank
				ranking();
				status = 1;
				Sleep(300);				
			}				
		}
		else if (status == 0)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(19, 9);
				cout << "   ";
				gotoxy(19, 8);
				cout << "��";
				status = 3;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(19, 9);
				cout << "   ";
				gotoxy(19, 6);
				cout << "��";
				status = 1;				
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// �����{��
				
				system("CLS");
				drawMainStatic();
				gotoxy(18, 2);
				cout << "= = = = = = = = =";
				gotoxy(21, 3);
				cout << " MUSIC GAME ";
				gotoxy(18, 4);
				cout << "= = = = = = = = =";
				gotoxy(20, 6);
				cout << " produced by";
				gotoxy(19, 8);
				cout << " ANCIENT  DARK";
				gotoxy(16, 11);
				cout << "2016 Summer released";
				Sleep(100);
				gotoxy(25, 18);
				return 0;
			}			
		}
		Sleep(100);
	}
	getch();
}
void putRank(int status)
{
	ifstream rankFile;
	string names[10];
	int scores[10] = {0};
	if (status == 1)
		rankFile.open("song1Rank.txt");
	else if (status == 2)
		rankFile.open("song2Rank.txt");
	else if (status == 3)
		rankFile.open("song3Rank.txt");
	else if (status == 4)
		rankFile.open("song4Rank.txt");
	else if (status == 5)
		rankFile.open("song5Rank.txt");
	else if (status == 6)
		rankFile.open("song6Rank.txt");
	int c = 0;
	while (!rankFile.eof())
	{
		rankFile >> names[c] >> scores[c];
		c++;
	}
	rankFile.close();
	system("CLS");
	gotoxy(10,1);
	switch (status)
	{
		case 1:
			cout << "Granat(4k)";
			break;
		case 2:
			cout << "Parousia(4k)";
			break;
		case 3:
			cout << "Kabaneri of the Iron Fortress(4k)";
			break;
		case 4:
			cout << "Sora ga Aozora de aru tame ni(4k)";
			break;
		case 5:
			cout << "Reverence(4k)";
			break;
		case 6:
			cout << "Darkness(5k)";
	}
	gotoxy(2, 2);
	for (int i = 0; i < 24; i++)
		cout << "��";
	gotoxy(10, 3);
	cout << "Ranking";
	gotoxy(20, 3);
	cout << "Name";
	gotoxy(40, 3);
	cout << "Score";
	for (int i = 0; i < 10; i++)
	{
		gotoxy(10, 4+i);
		cout << i+1 <<" "; 
		gotoxy(20, 4+i);
		cout << names[i] <<" ";
		gotoxy(40, 4+i);
		cout << scores[i] <<" ";
	}
	gotoxy(2, 14);
	for (int i = 0; i < 24; i++)
		cout << "��";
	gotoxy(14, 16);
	cout << "-press SPACE to continue-";
	Sleep(300);
	while (1)
	{
		if (GetKeyState(VK_SPACE) < 0)
		{
			system("CLS");		
			break;
		}
	}
}
void ranking()
{
	drawRanking();
	int status = 1; // 0: back, 1: song1, 2: song2, 3: song3, 4: song4, 5: song5
	Sleep(300);
	
	while (1)
	{
		if (status == 1)
		{		
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(7, 4);
				cout << "   ";
				gotoxy(7, 10);
				cout << "��";
				status = 0;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(7, 4);
				cout << "   ";
				gotoxy(7, 5);
				cout << "��";
				status = 2;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song1 
				putRank(status);
				drawRanking();
				status = 1;	
			}
		}
		else if (status == 2)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(7, 5);
				cout << "   ";
				gotoxy(7, 4);
				cout << "��";
				status = 1;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(7, 5);
				cout << "   ";
				gotoxy(7, 6);
				cout << "��";
				status = 3;
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song2
				putRank(status);
				drawRanking();
				status = 1;
			}
		}
		else if (status == 3)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(7, 6);
				cout << "   ";
				gotoxy(7, 5);
				cout << "��";
				status = 2;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(7, 6);
				cout << "   ";
				gotoxy(7, 7);
				cout << "��";
				status = 4;				
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song3
				putRank(status);
				drawRanking();
				status = 1;	
			}			
		}
		else if (status == 4)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(7, 7);
				cout << "   ";
				gotoxy(7, 6);
				cout << "��";
				status = 3;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(7, 7);
				cout << "   ";
				gotoxy(7, 8);
				cout << "��";
				status = 5;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song4
				putRank(status);
				drawRanking();
				status = 1;	
			}			
		}
		else if (status == 5)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(7, 8);
				cout << "   ";
				gotoxy(7, 7);
				cout << "��";
				status = 4;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(7, 8);
				cout << "   ";
				gotoxy(7, 9);
				cout << "��";
				status = 6;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song5
				putRank(status);
				drawRanking();
				status = 1;				
			}			
		}
		else if (status == 6)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(7, 9);
				cout << "   ";
				gotoxy(7, 8);
				cout << "��";
				status = 5;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(7, 9);
				cout << "   ";
				gotoxy(7, 10);
				cout << "��";
				status = 0;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// song5
				putRank(status);
				drawRanking();
				status = 1;				
			}
		}
		else if (status == 0)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				gotoxy(7, 10);
				cout << "   ";
				gotoxy(7, 9);
				cout << "��";
				status = 6;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				gotoxy(7, 10);
				cout << "   ";
				gotoxy(7, 4);
				cout << "��";
				status = 1;			
			}
			else if (GetKeyState(VK_SPACE) < 0)
			{// back
				system("CLS");
				drawMainStatic();
				drawMainButton();
				break;
			}				
		}
		Sleep(100);
	}	
}
void keyinRank(string name, int score, int song)
{
	ifstream rankFile;
	string names[11];
	int scores[11] = {0};
	if (song == 1)
		rankFile.open("song1Rank.txt");
	else if (song == 2)
		rankFile.open("song2Rank.txt");
	else if (song == 3)
		rankFile.open("song3Rank.txt");
	else if (song == 4)
		rankFile.open("song4Rank.txt");
	else if (song == 5)
		rankFile.open("song5Rank.txt");
	else if (song == 6)
		rankFile.open("song6Rank.txt");

	int c = 0, update = 0;
	while (c < 10) 
	{
		rankFile >> names[c] >> scores[c];
		if (score > scores[c] && update == 0)//���Ƥ�쥻�]�W���� 
		{
			names[c+1] = names[c];//���Ө��ө��Ჾ�@��
			scores[c+1] = scores[c]; 
			names[c] = name;//��쥻���H����
			scores[c] = score;//�����쥻������
			update = 1;//�w�g��s�Ʀ�] 
			c++;//�h�F�@�ӤH 
		}
		c++;
	}
	rankFile.close();
	ofstream outRank;
	if (song == 1)
		outRank.open("song1Rank.txt");
	else if (song == 2)
		outRank.open("song2Rank.txt");
	else if (song == 3)
		outRank.open("song3Rank.txt");
	else if (song == 4)
		outRank.open("song4Rank.txt");
	else if (song == 5)
		outRank.open("song5Rank.txt");
	else if (song == 6)
		outRank.open("song6Rank.txt"); 
	for (int i = 0; i < 10; i++)
		outRank << names[i] << " " << scores[i] << endl;;
	outRank.close();
}

