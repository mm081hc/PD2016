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
	int driverPos;  // driverPos: 紀錄司機陣列位置 
	int lateCnt;  // lateCnt: late次數 
	Passenger (int);  // constructor
	bool search(int, int, int);  // searching
	void travel(int);  // traveling
	void close(int);  // close
	bool arrive(int, int, int, int);  // arrive
	void aveCount();  // 計算average rating
	bool belowTwo();  // 檢查average rating是否<2 
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
	ratingAve = 3;  // 初始rating average 
	ratings = new int [10000];
	driverPos = -1;  // 初始司機陣列index = -1 
	lateCnt = 0;
}
bool Passenger::search(int id, int x, int y)
{// searching
	if (this->id == id)  // 若與傳入id相符，回傳true 
	{
		driverPos = -1;  // 重置司機資料 
		this->x = x;  // 設定x, y 
		this->y = y;
		status = searching;  // searching
		Passenger::offlineCnt--;  // offline人數-1 
		Passenger::searchingCnt++;  // searching人數+1 
		return true;
	}
	return false;  // 不符回傳false
}
void Passenger::travel(int d)
{// traveling
	driverPos = d;  // 設定司機陣列index 
	status = traveling;  // traveling
	Passenger::searchingCnt--;  // searching人數-1 
	Passenger::travelingCnt++;  // traveling人數+1 
}
void Passenger::close(int r)
{// close app
	if (r == 0)  // 若為強制關閉app(原狀態為searching)
		Passenger::searchingCnt--;  // searching人數-1 
	else  // 若為抵達目的地 
	{
		ratings[ratingCnt] = r;  // 記錄評價 
		ratingCnt++;
		Passenger::travelingCnt--;  // traveling人數-1 
	}
	Passenger::offlineCnt++;  // offline人數+1 
	status = offline;  // offline
}
bool Passenger::arrive(int id, int x, int y, int r)
{// arrive
	if (this->id == id)  // 若與傳入id相符，回傳true 
	{
		this->x = x;  // 紀錄位置 
		this->y = y;
		close(r);  // close app
		aveCount();  // 計算rating average 
		return true;
	}
	return false;  // 不符回傳false
}
void Passenger::aveCount()
{// 計算average rating
	double sum = 0;
	for (int i = 0; i < ratingCnt; i++)  // 計算評價總和 
		sum += ratings[i];
	ratingAve = sum / ratingCnt;
}
bool Passenger::belowTwo()
{// 檢查rating average是否 < 2
	double score = ratingAve;
	if (ratingCnt != 0)
		score -= 5 * static_cast<double>(lateCnt) / ratingCnt;	
//	cout << "score: " << lateCnt << " " << score << endl;
	if (score < 2)  // 若 < 2，關閉app，回傳true 
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
	int lateCnt;  // late次數	
	bool operator>(const Driver&) const;  // 判斷priority
	bool open (int, int, int);  // open app (id, x, y)
	void travel();  // traveling
	bool close (int);  // close app (id)
	void arrive(int, int, int);  // arrive (x, y, rating)
	void aveCount();  // 計算average rating
	bool available(int, int, int);  // 檢查是否有司機符合條件 (x, y, m) 
	bool searchConti();  // 檢查是否有司機能分配
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
{// 判斷priority
	double scorethis = this->ratingAve;
	if (ratingCnt != 0)
		scorethis -= 5 * static_cast<double>(lateCnt) / ratingCnt;
	double score = d.ratingAve;
	if (d.ratingCnt != 0)
		score -= 5 * static_cast<double>(d.lateCnt) / d.ratingCnt;	
	if (scorethis > score)
		return true;  // 若average rating大，回傳true
	else if (scorethis == score && this->id < d.id)
		return true;  // 若average rating相同且id較小，回傳true 
	return false;
}
bool Driver::open(int id, int x, int y)
{// open app
	if (this->id == id)
	{
		this->x = x;  // 設定位置 
		this->y = y;
		status = searching;  // 狀態改為searching 
		Driver::offlineCnt--;  // offline人數-1
		Driver::searchingCnt++;  // searching人數+1 
		return true;
	}
	return false;
}
void Driver::travel()
{// traveling
	status = traveling;  // traveling
	Driver::searchingCnt--;  // searching人數-1 
	Driver::travelingCnt++;  // traveling人數+1 
}
bool Driver::close(int id)
{// close app
	if (this->id == id)  // 若id與傳入id相符，回傳true
	{
		Driver::searchingCnt--;  // seaching人數-1 
		Driver::offlineCnt++;  // offline人數+1 
		status = offline;  // offline
		return true;
	}
	return false;  // 不符回傳false 
}
void Driver::arrive(int x, int y, int r)
{
	this->x = x;  // 紀錄位置 
	this->y = y;
	status = searching;  // 狀態為searching
	Driver::travelingCnt--;
	Driver::searchingCnt++;
	ratings[ratingCnt] = r;  // 紀錄rating 
	ratingCnt++;
	aveCount();  // 計算average rating
}
void Driver::aveCount()
{// 計算average rating
	double sum = 0;
	for (int i = 0; i < ratingCnt; i++)
		sum += ratings[i];
	ratingAve = sum / ratingCnt;
}
bool Driver::available(int x, int y, int m)
{// 檢查司機是否滿足條件(searching, distance <= m) 
	if (status == searching)
		if (abs(this->x - x) + abs(this->y - y) <= m)
			return true;
	return false;
}
bool Driver::searchConti()
{// 檢查是否有司機可分配(有人狀態為searching) 
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
// 分配司機: 傳入passenger, x, y, driver, number of drivers, m, m 

int main()
{
	char input[501] = {0};  // event: 用來判斷輸入的狀況
	char delim[2] = {' '};
	int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
	// pNum: number of passengers // dNum: number of drivers 
	Passenger* p[10000];  // 指向Passenger物件的指標 
	Driver* d[10000];  // 指向Driver物件的指標   
	
	cin >> m;
	int id = -1, iPos = -1;
	cin.ignore();
	while (cin.getline(input, 500))
	{
//		cout << "input: " << input << endl;
		if (isdigit(input[2]))
		{
			if (input[0] == 'P')  // 乘客註冊 
			{	
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				p[pNum] = new Passenger(id);  // 指標指向物件 
				pNum++;
			}
			else if (input[0] == 'D')  // 司機註冊 
			{
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				d[dNum] = new Driver(id);  // 指標指向物件 
				dNum++;
			}
			else if (input[0] == 'O')  // 司機打開app 
			{
				int x = 0, y = 0;
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				start = strtok(nullptr, delim);
				x = atoi(start);
				start = strtok(nullptr, delim);
				y = atoi(start);
				for (int i = 0; i < dNum; i++)  // 找相符id 
					if (d[i]->open(id, x, y))
						break;
						
	//			cout << id << x << y << endl; 
			}
			else if (input[0] == 'S')  // 乘客搜尋 
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
				for (int i = 0; i < pNum; i++)  // 找相符id 
				{
					if (p[i]->search(id, x, y))  // 找到符合輸入id的乘客 
					{
						if (p[i]->belowTwo())  // 若乘客評價<2, close app 
							break;
						else
							assign(p[i], x, y, d, dNum, m, m);  // 分配driver
						break;	
					}	
				}

			}
			else if (input[0] == 'A')  // 抵達目的地 
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
				for (int i = 0; i < pNum; i++)  // 找相符id 
				{
					if (p[i]->arrive(id, x, y, rP))
					{
						d[p[i]->driverPos]->arrive(x, y, rD);  // driverPos: 司機陣列位置
						iPos = i;
//						cout << "iPos: " << iPos << " " << p[i]->driverPos << endl;
					//	p[i]->driverPos = -1;  // 清除司機資料
						break;
					}
				}
//				cout << id << " " << x << " "  << y << " " << rD << " " << rP << endl;
			}
			else if (input[0] == 'C' && isdigit(input[2]))  // 司機關閉app 
			{
				char* start = strtok(input, delim);
				start = strtok(nullptr, delim);
				id = atoi(start);
				for (int i = 0; i < dNum; i++)  // 找相符id 
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
	if (d[0]->searchConti())  // 若有司機未分配(searchingCnt > 0) 
	{	
		Driver* prior = new Driver();  // prior: 指向應分配的司機 
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
			delete prior;  // 刪除指標 
			assign (p, x, y, d, dNum, m + k, k);  // 將m加上m(2m, 3m...), 傳入下一次迴圈
		} 
		else // 若有找到司機，將乘客和司機的狀態改為traveling 
		{
			d[priorPos]->travel();
			p->travel(priorPos);
		}
	}
	else  // 若無司機可分配，乘客關閉app
		p->close(0);
}
