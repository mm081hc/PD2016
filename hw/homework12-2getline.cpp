#include <iostream>
#include <cctype>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
// status: 0: offline, 1: searching, 2: traveling
const int offline = 0;
const int searching = 1;
const int traveling = 2;

class Passenger
{
private:
	static int offlineCnt;
	static int searchingCnt;
	static int travelingCnt;
	int id;
	int status;
	int x;
	int y;
	int ratingCnt;
	int* ratings;
	double ratingAve;  // ratingAve: average rating
public:
	int driverPos;  // driverPos: �����q���}�C��m 
	int lateCnt;  // lateCnt: late���� 
	Passenger (int);  // constructor
	bool search(int, int, int);  // searching
	void travel(int);  // traveling
	void close(int);  // close
	bool arrive(int, int, int, int);  // arrive
	void aveCount();  // �p��average rating
	bool belowTwo();  // �ˬdaverage rating�O�_<2 
};
int Passenger::offlineCnt = 0;
int Passenger::searchingCnt = 0;
int Passenger::travelingCnt = 0;
Passenger::Passenger (int id)
{// constructor
	Passenger::offlineCnt++;
	this->id = id;
	status = offline;  // offline 
	x = y = 0;
	ratingCnt = 0;
	ratingAve = 3;  // ��lrating average 
	ratings = new int [10000];
	driverPos = -1;  // ��l�q���}�Cindex = -1 
	lateCnt = 0;
}
bool Passenger::search(int id, int x, int y)
{// searching
	if (this->id == id)  // �Y�P�ǤJid�۲šA�^��true 
	{
		driverPos = -1;  // ���m�q����� 
		this->x = x;  // �]�wx, y 
		this->y = y;
		status = searching;  // searching
		Passenger::offlineCnt--;  // offline�H��-1 
		Passenger::searchingCnt++;  // searching�H��+1 
		return true;
	}
	return false;  // ���Ŧ^��false
}
void Passenger::travel(int d)
{// traveling
	driverPos = d;  // �]�w�q���}�Cindex 
	status = traveling;  // traveling
	Passenger::searchingCnt--;  // searching�H��-1 
	Passenger::travelingCnt++;  // traveling�H��+1 
}
void Passenger::close(int r)
{// close app
	if (r == 0)  // �Y���j������app(�쪬�A��searching)
		Passenger::searchingCnt--;  // searching�H��-1 
	else  // �Y����F�ت��a 
	{
		ratings[ratingCnt] = r;  // �O������ 
		ratingCnt++;
		Passenger::travelingCnt--;  // traveling�H��-1 
	}
	Passenger::offlineCnt++;  // offline�H��+1 
	status = offline;  // offline
}
bool Passenger::arrive(int id, int x, int y, int r)
{// arrive
	if (this->id == id)  // �Y�P�ǤJid�۲šA�^��true 
	{
		this->x = x;  // ������m 
		this->y = y;
		close(r);  // close app
		aveCount();  // �p��rating average 
		return true;
	}
	return false;  // ���Ŧ^��false
}
void Passenger::aveCount()
{// �p��average rating
	double sum = 0;
	for (int i = 0; i < ratingCnt; i++)  // �p������`�M 
		sum += ratings[i];
	ratingAve = sum / ratingCnt;
}
bool Passenger::belowTwo()
{// �ˬdrating average�O�_ < 2
	double score = ratingAve;
	if (ratingCnt != 0)
		score -= 5 * static_cast<double>(lateCnt) / ratingCnt;	
//	cout << "score: " << lateCnt << " " << score << endl;
	if (score < 2)  // �Y < 2�A����app�A�^��true 
	{
		close(0);
		return true;
	}
	return false;
}

class Driver
{
private:
	static int offlineCnt;
	static int searchingCnt;
	static int travelingCnt;
	int id;
	int status;
	int x;
	int y;
	int ratingCnt;
	int* ratings;
	double ratingAve;  // ratingAve: average rating
public:
	Driver(int);  // constructor
	Driver();  // default constructor
	int lateCnt;  // late����	
	bool operator>(const Driver&) const;  // �P�_priority
	bool open (int, int, int);  // open app (id, x, y)
	void travel();  // traveling
	bool close (int);  // close app (id)
	void arrive(int, int, int);  // arrive (x, y, rating)
	void aveCount();  // �p��average rating
	bool available(int, int, int);  // �ˬd�O�_���q���ŦX���� (x, y, m) 
	bool searchConti();  // �ˬd�O�_���q������t
	void print(int&);  // print id
};
int Driver::offlineCnt = 0;
int Driver::searchingCnt = 0;
int Driver::travelingCnt = 0;
Driver::Driver()
{// default constructor
	id = 100000;
	ratingAve = 0;
}
Driver::Driver (int id)
{// constructor
	Driver::offlineCnt++;
	this->id = id;
	status = offline;
	x = y = 0;
	ratingCnt = 0;
	ratingAve = 3;
	ratings = new int [10000];
	lateCnt = 0;
}
bool Driver::operator>(const Driver& d) const
{// �P�_priority
	double scorethis = this->ratingAve;
	if (ratingCnt != 0)
		scorethis -= 5 * static_cast<double>(lateCnt) / ratingCnt;
	double score = d.ratingAve;
	if (d.ratingCnt != 0)
		score -= 5 * static_cast<double>(d.lateCnt) / d.ratingCnt;	
	if (scorethis > score)
		return true;  // �Yaverage rating�j�A�^��true
	else if (scorethis == score && this->id < d.id)
		return true;  // �Yaverage rating�ۦP�Bid���p�A�^��true 
	return false;
}
bool Driver::open(int id, int x, int y)
{// open app
	if (this->id == id)
	{
		this->x = x;  // �]�w��m 
		this->y = y;
		status = searching;  // ���A�אּsearching 
		Driver::offlineCnt--;  // offline�H��-1
		Driver::searchingCnt++;  // searching�H��+1 
		return true;
	}
	return false;
}
void Driver::travel()
{// traveling
	status = traveling;  // traveling
	Driver::searchingCnt--;  // searching�H��-1 
	Driver::travelingCnt++;  // traveling�H��+1 
}
bool Driver::close(int id)
{// close app
	if (this->id == id)  // �Yid�P�ǤJid�۲šA�^��true
	{
		Driver::searchingCnt--;  // seaching�H��-1 
		Driver::offlineCnt++;  // offline�H��+1 
		status = offline;  // offline
		return true;
	}
	return false;  // ���Ŧ^��false 
}
void Driver::arrive(int x, int y, int r)
{
	this->x = x;  // ������m 
	this->y = y;
	status = searching;  // ���A��searching
	Driver::travelingCnt--;
	Driver::searchingCnt++;
	ratings[ratingCnt] = r;  // ����rating 
	ratingCnt++;
	aveCount();  // �p��average rating
}
void Driver::aveCount()
{// �p��average rating
	double sum = 0;
	for (int i = 0; i < ratingCnt; i++)
		sum += ratings[i];
	ratingAve = sum / ratingCnt;
}
bool Driver::available(int x, int y, int m)
{// �ˬd�q���O�_��������(searching, distance <= m) 
	if (status == searching)
		if (abs(this->x - x) + abs(this->y - y) <= m)
			return true;
	return false;
}
bool Driver::searchConti()
{// �ˬd�O�_���q���i���t(���H���A��searching) 
	if (searchingCnt > 0)
		return true;
	return false;
}
void Driver::print(int& num)
{// cout id
//	cout << id << " " << status << endl;
	if (status == searching)	
	{
		if (num == searchingCnt - 1)
			cout << id;
		else
			cout << id << " ";
		num++;
	}	
}

void assign(Passenger*, int, int, Driver* [], int, int, int);
// ���t�q��: �ǤJpassenger, x, y, driver, number of drivers, m, m 

int main()
{
	char input[501] = {0};  // event: �ΨӧP�_��J�����p
	char delim[2] = {' '};
	int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
	// pNum: number of passengers // dNum: number of drivers 
	Passenger* p[10000];  // ���VPassenger���󪺫��� 
	Driver* d[10000];  // ���VDriver���󪺫���   
	
	cin >> m;
	int id = -1, iPos = -1;
	cin.ignore();
	while (cin.getline(input, 500))
	{
//		cout << "input: " << input << endl;
		if (isdigit(input[2]))
		{
			if (input[0] == 'P')  // ���ȵ��U 
			{	
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				p[pNum] = new Passenger(id);  // ���Ы��V���� 
				pNum++;
			}
			else if (input[0] == 'D')  // �q�����U 
			{
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				d[dNum] = new Driver(id);  // ���Ы��V���� 
				dNum++;
			}
			else if (input[0] == 'O')  // �q�����}app 
			{
				int x = 0, y = 0;
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				start = strtok(nullptr, delim);
				x = atoi(start);
				start = strtok(nullptr, delim);
				y = atoi(start);
				for (int i = 0; i < dNum; i++)  // ��۲�id 
					if (d[i]->open(id, x, y))
						break;
						
	//			cout << id << x << y << endl; 
			}
			else if (input[0] == 'S')  // ���ȷj�M 
			{
				int x = 0, y = 0;
	//			cin >> id >> x >> y;
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				start = strtok(nullptr, delim);
				x = atoi(start);
				start = strtok(nullptr, delim);
				y = atoi(start);			
				for (int i = 0; i < pNum; i++)  // ��۲�id 
				{
					if (p[i]->search(id, x, y))  // ���ŦX��Jid������ 
					{
						if (p[i]->belowTwo())  // �Y���ȵ���<2, close app 
							break;
						else
							assign(p[i], x, y, d, dNum, m, m);  // ���tdriver
						break;	
					}	
				}

			}
			else if (input[0] == 'A')  // ��F�ت��a 
			{
				int x = 0, y = 0, rP = 0, rD = 0;
//				char reviewD[501] = {0}, reviewP[501] = {0};
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				start = strtok(nullptr, delim);
				x = atoi(start);
				start = strtok(nullptr, delim);
				y = atoi(start);
				start = strtok(nullptr, delim);
				rD = atoi(start);
				start = strtok(nullptr, delim);
				rP = atoi(start);
				for (int i = 0; i < pNum; i++)  // ��۲�id 
				{
					if (p[i]->arrive(id, x, y, rP))
					{
						d[p[i]->driverPos]->arrive(x, y, rD);  // driverPos: �q���}�C��m
						iPos = i;
//						cout << "iPos: " << iPos << " " << p[i]->driverPos << endl;
					//	p[i]->driverPos = -1;  // �M���q�����
						break;
					}
				}
//				cout << id << " " << x << " "  << y << " " << rD << " " << rP << endl;
			}
			else if (input[0] == 'C' && isdigit(input[2]))  // �q������app 
			{
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				for (int i = 0; i < dNum; i++)  // ��۲�id 
					if (d[i]->close(id))
						break;
			}
//			cout << "id: " << id << endl;
		}
		else
		{
			char input2[501] = {0};			
			cin.getline(input2, 500);
			for (int i = 0; i < strlen(input); i++)
				input[i] = tolower(input[i]);
			for (int i = 0; i < strlen(input2); i++)
				input2[i] = tolower(input2[i]);
//			cout << input << endl << input2 << endl;
			if (strstr(input2, "late") != NULL)
				p[iPos]->lateCnt++;
			if (strstr(input, "late") != NULL)
				d[p[iPos]->driverPos]->lateCnt++;
			
//			cout << iPos << p[iPos]->driverPos << endl;
		}
	}
	
	int printNum = 0;
	for (int i = 0; i < dNum; i++)  // cout
		d[i]->print(printNum);
	return 0;
}

void assign(Passenger* p, int x, int y, Driver* d[], int dNum, int m, int k)
{
	if (d[0]->searchConti())  // �Y���q�������t(searchingCnt > 0) 
	{	
		Driver* prior = new Driver();  // prior: ���V�����t���q�� 
		int priorPos = -1;  // �x�s�����t���q����m 
		for (int i = 0; i < dNum; i++)
		{
			if (d[i]->available(x, y, m))  // �Y�q�����A��searching, �B�Z��<=m 
			{
				if (*d[i] > *prior)  // �Yd[i]��������priority 
				{
					prior = d[i];  // �������� 
					priorPos = i;  // �O�Ui�� 
				}
			}
		}	
		if (priorPos == -1)  // �S���۲Ū��q��, ������searching���q�� 
		{	
			delete prior;  // �R������ 
			assign (p, x, y, d, dNum, m + k, k);  // �Nm�[�Wm(2m, 3m...), �ǤJ�U�@���j��
		} 
		else // �Y�����q���A�N���ȩM�q�������A�אּtraveling 
		{
			d[priorPos]->travel();
			p->travel(priorPos);
		}
	}
	else  // �Y�L�q���i���t�A��������app
		p->close(0);
}