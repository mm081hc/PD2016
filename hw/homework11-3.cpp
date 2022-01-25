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
	ratingAve = 3;  // 初始rating average 
	ratings = new int [10000];
	driverPos = -1;  // 紀錄司機陣列index，初始值為-1 
}
bool Passenger::search(int id, int x, int y)
{
	if (this->id == id)  // 若與傳入id相符，回傳true 
	{
		this->x = x;  // 設定x, y 
		this->y = y;
		status = 1;  // searching
		Passenger::offlineCnt--;  // offline人數-1 
		Passenger::searchingCnt++;  // searching人數+1 
		return true;
	}
	return false;  // 不符回傳false
}
void Passenger::travel(int d)
{
	driverPos = d;  // 設定司機陣列index 
	status = 2;  // traveling
	Passenger::searchingCnt--;  // searching人數-1 
	Passenger::travelingCnt++;  // traveling人數+1 
}
void Passenger::close(int r)
{
	if (r == 0)  // 若為強制關閉(狀態為searching)
		Passenger::searchingCnt--;  // searching人數-1 
	else  // 若為抵達目的地 
	{
		ratings[ratingCnt] = r;  // 記錄評價 
		ratingCnt++;
		Passenger::travelingCnt--;  // traveling人數-1 
	}
	Passenger::offlineCnt++;  // offline人數+1 
	status = 0;  // offline
}
bool Passenger::arrive(int id, int x, int y, int r)
{
	if (this->id == id)  // 若與傳入id相符，回傳true 
	{
		this->x = x;  // 紀錄位置 
		this->y = y;
		close(r);  // close
		aveCount();  // 計算rating average 
		return true;
	}
	return false;  // 不符回傳false
}
void Passenger::aveCount()  // 計算rating average
{
	double sum = 0;
	for (int i = 0; i < ratingCnt; i++)  // 計算評價總和 
		sum += ratings[i];
	ratingAve = sum / ratingCnt;
}
bool Passenger::belowTwo()
{
	if (ratingAve < 2)  // 若rating average < 2，關閉app，回傳true 
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
	this->x = x;  // 到達乘客位置 
	this->y = y;
	status = 2;
	Driver::searchingCnt--;
	Driver::travelingCnt++;
}
bool Driver::close(int id)
{
	if (this->id == id)  // 若id與傳入id相符，回傳true
	{
		Driver::searchingCnt--;
		Driver::offlineCnt++;
		status = 0;
		return true;
	}
	return false;  // 不符回傳false 
}
void Driver::arrive(int x, int y, int r, int A, int a, int b)
{
	int distance = abs(this->x - x) + abs(this->y - y);  // 計算經過距離 
	if (distance <= A)  // 計算revenue 
		revenue += a;
	else
		revenue += a + b * (distance-A);
	this->x = x;  // 紀錄位置 
	this->y = y;
	status = 1;  // 轉為searching
	Driver::travelingCnt--;
	Driver::searchingCnt++;
	ratings[ratingCnt] = r;  // 紀錄rating 
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
// 傳入passenger, x, y, driver, number of drivers, m, k = 1 

int main()
{
	char event = 0;  // event: 用來判斷輸入的狀況 
	int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
	// pNum: number of passengers // dNum: number of drivers
	int A = 0, a = 0, b = 0;
	Passenger* p[10000];  // 指向Passenger物件的指標 
	Driver* d[10000];  // 指向Driver物件的指標
	cin >> A >> a >> b;
	cin >> m;
	while (cin >> event)
	{
		int id = 0;
		if (event == 'P')  // 乘客註冊 
		{
			cin >> id;
			p[pNum] = new Passenger(id);
			pNum++;
		}
		else if (event == 'D')  // 司機註冊 
		{
			cin >> id;
			d[dNum] = new Driver(id);
			dNum++;
		}
		else if (event == 'O')  // 司機打開app 
		{
			int x = 0, y = 0;
			cin >> id >> x >> y;
			for (int i = 0; i < dNum; i++)
			{
				if (d[i]->open(id, x, y))
					break;
			}
		}
		else if (event == 'S')  // 乘客搜尋 
		{
			int x = 0, y = 0;
			cin >> id >> x >> y;
			for (int i = 0; i < pNum; i++)
			{
				if (p[i]->search(id, x, y))  // 找到符合輸入id的乘客 
				{
					if (p[i]->belowTwo())  // 若乘客評價<2 
						break;
					else
						assign(p[i], x, y, d, dNum, m, m);  // 分配driver
					break;	
				}	
			}	
		}
		else if (event == 'A')  // 抵達目的地 
		{
			int x = 0, y = 0, rP = 0, rD = 0;
			cin >> id >> x >> y >> rD >> rP;
			for (int i = 0; i < pNum; i++)
			{
				if (p[i]->arrive(id, x, y, rP))
				{
					d[p[i]->driverPos]->arrive(x, y, rD, A, a, b);
					p[i]->driverPos = -1;  // 清除司機資料
					break;
				}
			}
		}
		else if (event == 'C')  // 司機關閉app 
		{
			cin >> id;
			for (int i = 0; i < dNum; i++)  // 找與id相符的driver 
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
		int priorPos = -1;  // 儲存應分配的司機位置 
		for (int i = 0; i < dNum; i++)
		{
			if (d[i]->available(x, y, m))  // 若司機狀態為searching, 且距離<=m 
			{
				if (*d[i] > *prior)  // 若d[i]有較高的priority 
				{
					prior = d[i];  // 替換指標 
					priorPos = i;  // 記下i值 
				}
			}
		}	
		if (priorPos == -1)  // 沒找到相符的司機, 但仍有searching的司機 
		{	
			delete prior;
			assign (p, x, y, d, dNum, m + k, k);  // 將m*2, 傳入下一次迴圈
		} 
		else // 若有找到司機，將乘客和司機的狀態改為traveling 
		{
			d[priorPos]->travel(x, y);
			p->travel(priorPos);
		}
	}
	else  // 若無司機可分配，乘客關閉app
		p->close(0);
}
