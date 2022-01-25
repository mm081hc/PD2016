#include <iostream>
#include <cmath>
using namespace std;

class Passenger
{
private:
	static int offlineCnt;
	static int searchingCnt;
	static int travelingCnt;
	int id;
	int status;  // 0: offline, 1: searching, 2: traveling
	int x;
	int y;
	int ratingCnt;
	int* ratings;
	double ratingAve;  // ratingAve: average rating
public:
	int driverPos;
	Passenger (int);
	bool search(int, int, int);
	void travel(int);  // traveling
	void close(int);  // close
	bool arrive(int, int, int, int);
	void aveCount();	
	bool belowTwo();
};
int Passenger::offlineCnt = 0;
int Passenger::searchingCnt = 0;
int Passenger::travelingCnt = 0;
Passenger::Passenger (int id)
{// constructor
	Passenger::offlineCnt++;
	this->id = id;
	status = 0;  // offline 
	x = y = 0;
	ratingCnt = 0;
	ratingAve = 3;  // ��lrating average 
	ratings = new int [10000];
	driverPos = -1;  // �����q���}�Cindex�A��l�Ȭ�-1 
}
bool Passenger::search(int id, int x, int y)
{
	if (this->id == id)  // �Y�P�ǤJid�۲šA�^��true 
	{
		this->x = x;  // �]�wx, y 
		this->y = y;
		status = 1;  // searching
		Passenger::offlineCnt--;  // offline�H��-1 
		Passenger::searchingCnt++;  // searching�H��+1 
		return true;
	}
	return false;  // ���Ŧ^��false
}
void Passenger::travel(int d)
{
	driverPos = d;  // �]�w�q���}�Cindex 
	status = 2;  // traveling
	Passenger::searchingCnt--;  // searching�H��-1 
	Passenger::travelingCnt++;  // traveling�H��+1 
}
void Passenger::close(int r)
{
	if (r == 0)  // �Y���j������(���A��searching)
		Passenger::searchingCnt--;  // searching�H��-1 
	else  // �Y����F�ت��a 
	{
		ratings[ratingCnt] = r;  // �O������ 
		ratingCnt++;
		Passenger::travelingCnt--;  // traveling�H��-1 
	}
	Passenger::offlineCnt++;  // offline�H��+1 
	status = 0;  // offline
}
bool Passenger::arrive(int id, int x, int y, int r)
{
	if (this->id == id)  // �Y�P�ǤJid�۲šA�^��true 
	{
		this->x = x;  // ������m 
		this->y = y;
		close(r);  // close
		aveCount();  // �p��rating average 
		return true;
	}
	return false;  // ���Ŧ^��false
}
void Passenger::aveCount()  // �p��rating average
{
	double sum = 0;
	for (int i = 0; i < ratingCnt; i++)  // �p������`�M 
		sum += ratings[i];
	ratingAve = sum / ratingCnt;
}
bool Passenger::belowTwo()
{
	if (ratingAve < 2)  // �Yrating average < 2�A����app�A�^��true 
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
	int status;  // 0: offline, 1: searching, 2: traveling
	int x;
	int y;
	int ratingCnt;
	int* ratings;
	double ratingAve;
	int revenue;
public:
	Driver(int);  // id
	Driver();
	bool operator>(const Driver&) const;
	bool open (int, int, int);  // id, x, y
	void travel(int, int);
	bool close (int);  // id
	void arrive(int, int, int, int, int, int);  // x, y, rating
	void aveCount();
	bool available(int, int, int);  // x, y, m
	bool searchConti();
	void print();  // print revenue
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
	status = 0;
	x = y = 0;
	ratingCnt = 0;
	ratingAve = 3;
	ratings = new int [10000];
	revenue = 0;
}
bool Driver::operator>(const Driver& d) const
{
	if (this->ratingAve > d.ratingAve)
		return true;
	else if (this->ratingAve == d.ratingAve && this->id < d.id)
		return true;
	return false;
}
bool Driver::open(int id, int x, int y)
{
	if (this->id == id)
	{
		this->id = id;
		this->x = x;
		this->y = y;
		status = 1;
		Driver::offlineCnt--;
		Driver::searchingCnt++;
		return true;
	}
	return false;
}
void Driver::travel(int x, int y)
{
	this->x = x;  // ��F���Ȧ�m 
	this->y = y;
	status = 2;
	Driver::searchingCnt--;
	Driver::travelingCnt++;
}
bool Driver::close(int id)
{
	if (this->id == id)  // �Yid�P�ǤJid�۲šA�^��true
	{
		Driver::searchingCnt--;
		Driver::offlineCnt++;
		status = 0;
		return true;
	}
	return false;  // ���Ŧ^��false 
}
void Driver::arrive(int x, int y, int r, int A, int a, int b)
{
	int distance = abs(this->x - x) + abs(this->y - y);  // �p��g�L�Z�� 
	if (distance <= A)  // �p��revenue 
		revenue += a;
	else
		revenue += a + b * (distance-A);
	this->x = x;  // ������m 
	this->y = y;
	status = 1;  // �ରsearching
	Driver::travelingCnt--;
	Driver::searchingCnt++;
	ratings[ratingCnt] = r;  // ����rating 
	ratingCnt++;
	aveCount();
}
void Driver::aveCount()
{
	double sum = 0;
	for (int i = 0; i < ratingCnt; i++)
		sum += ratings[i];
	ratingAve = sum / ratingCnt;
}
bool Driver::available(int x, int y, int m)
{
	if (status == 1)
		if (abs(this->x - x) + abs(this->y - y) <= m)
			return true;
	return false;
}
bool Driver::searchConti()
{
	if (searchingCnt > 0)
		return true;
	return false;
}
void Driver::print()  // cout revenue
{
	cout << revenue;
}

void assign(Passenger*, int, int, Driver* d[], int dNum, int m, int k);
// �ǤJpassenger, x, y, driver, number of drivers, m, k = 1 

int main()
{
	char event = 0;  // event: �ΨӧP�_��J�����p 
	int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
	// pNum: number of passengers // dNum: number of drivers
	int A = 0, a = 0, b = 0;
	Passenger* p[10000];  // ���VPassenger���󪺫��� 
	Driver* d[10000];  // ���VDriver���󪺫���
	cin >> A >> a >> b;
	cin >> m;
	while (cin >> event)
	{
		int id = 0;
		if (event == 'P')  // ���ȵ��U 
		{
			cin >> id;
			p[pNum] = new Passenger(id);
			pNum++;
		}
		else if (event == 'D')  // �q�����U 
		{
			cin >> id;
			d[dNum] = new Driver(id);
			dNum++;
		}
		else if (event == 'O')  // �q�����}app 
		{
			int x = 0, y = 0;
			cin >> id >> x >> y;
			for (int i = 0; i < dNum; i++)
			{
				if (d[i]->open(id, x, y))
					break;
			}
		}
		else if (event == 'S')  // ���ȷj�M 
		{
			int x = 0, y = 0;
			cin >> id >> x >> y;
			for (int i = 0; i < pNum; i++)
			{
				if (p[i]->search(id, x, y))  // ���ŦX��Jid������ 
				{
					if (p[i]->belowTwo())  // �Y���ȵ���<2 
						break;
					else
						assign(p[i], x, y, d, dNum, m, m);  // ���tdriver
					break;	
				}	
			}	
		}
		else if (event == 'A')  // ��F�ت��a 
		{
			int x = 0, y = 0, rP = 0, rD = 0;
			cin >> id >> x >> y >> rD >> rP;
			for (int i = 0; i < pNum; i++)
			{
				if (p[i]->arrive(id, x, y, rP))
				{
					d[p[i]->driverPos]->arrive(x, y, rD, A, a, b);
					p[i]->driverPos = -1;  // �M���q�����
					break;
				}
			}
		}
		else if (event == 'C')  // �q������app 
		{
			cin >> id;
			for (int i = 0; i < dNum; i++)  // ��Pid�۲Ū�driver 
			{
				if (d[i]->close(id))
					break;
			}
		}
	}
	
	d[0]->print();
	for (int i = 1; i < dNum; i++)
	{
		cout << " ";
		d[i]->print();
	}
	return 0;
}

void assign(Passenger* p, int x, int y, Driver* d[], int dNum, int m, int k)
{
	if (d[0]->searchConti())
	{	
		Driver* prior = new Driver();
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
			delete prior;
			assign (p, x, y, d, dNum, m + k, k);  // �Nm*2, �ǤJ�U�@���j��
		} 
		else // �Y�����q���A�N���ȩM�q�������A�אּtraveling 
		{
			d[priorPos]->travel(x, y);
			p->travel(priorPos);
		}
	}
	else  // �Y�L�q���i���t�A��������app
		p->close(0);
}
