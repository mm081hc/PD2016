#include <iostream>
#include <cctype>
#include <cstring>
#include <cmath>
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
    int lateCnt;  // lateCnt: late次數
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    int driverPos;  // driverPos: 紀錄司機陣列位置 
    Passenger (int);  // constructor
    bool search(int, int, int);  // searching
    void travel(int);  // traveling
    void close(int);  // close
    bool arrive(int, int, int, int, bool);  // arrive
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
    score = 3;
}
bool Passenger::search(int id, int x, int y)
{// searching
    if (this->id == id)  // 若與傳入id相符，回傳true 
    {
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
bool Passenger::arrive(int id, int x, int y, int r, bool late)
{// arrive
    if (this->id == id)  // 若與傳入id相符，回傳true 
    {
        if (late == 1)
            lateCnt++;
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
	score = ratingAve - 5 * static_cast<double>(lateCnt) / ratingCnt;
}
bool Passenger::belowTwo()
{// 檢查rating average是否 < 2
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
    int lateCnt;  // late次數 
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    Driver(int);  // constructor
    Driver();  // default constructor
    bool operator>(const Driver&) const;  // 判斷priority
    bool open (int, int, int);  // open app (id, x, y)
    void travel();  // traveling
    bool close (int);  // close app (id)
    void arrive(int, int, int, bool);  // arrive (x, y, rating)
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
    score = -10;
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
    score = 3;
}
bool Driver::operator>(const Driver& d) const
{// 判斷priority
    if (this->score > d.score)
        return true;  // 若average rating大，回傳true
    else if (this->score == d.score && this->id < d.id)
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
void Driver::arrive(int x, int y, int r, bool late)
{
    if (late == 1)
        lateCnt++;
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
    score = ratingAve - 5 * static_cast<double>(lateCnt) / ratingCnt;
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
    char event = 0;  // event: 用來判斷輸入的狀況
    const char delim[7] = {' ', ',', '.', '!', '?', ';'};
    int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
    // pNum: number of passengers // dNum: number of drivers 
    Passenger* p[10000];  // 指向Passenger物件的指標 
    Driver* d[10000];  // 指向Driver物件的指標   
     
    cin >> m;
    while (cin >> event)
    {
        int id = 0;
        if (event == 'P')  // 乘客註冊 
        {
            cin >> id;
            p[pNum] = new Passenger(id);  // 指標指向物件 
            pNum++;
        }
        else if (event == 'D')  // 司機註冊 
        {
            cin >> id;
            d[dNum] = new Driver(id);  // 指標指向物件 
            dNum++;
        }
        else if (event == 'O')  // 司機打開app 
        {
            int x = 0, y = 0;
            cin >> id >> x >> y;
            for (int i = 0; i < dNum; i++)  // 找相符id 
                if (d[i]->open(id, x, y))
                    break;
        }
        else if (event == 'S')  // 乘客搜尋 
        {
            int x = 0, y = 0;
            cin >> id >> x >> y;
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
        else if (event == 'A')  // 抵達目的地 
        {
            int x = 0, y = 0, rP = 0, rD = 0;
            char reviewD[501] = {0}, reviewP[501] = {0};
            bool lateD = 0, lateP = 0;  // lateD, lateP: 紀錄司機乘客是否遲到(1) 
            cin >> id >> x >> y >> rD >> rP;
            cin.ignore();  // 跳過一字元 
            cin.getline(reviewD, 500);  // 輸入review       
            cin.getline(reviewP, 500);
            for (int i = 0; i < strlen(reviewD); i++)
                reviewD[i] = tolower(reviewD[i]);
            for (int i = 0; i < strlen(reviewP); i++)
                reviewP[i] = tolower(reviewP[i]);
            char * startD = strtok(reviewD, delim);
            while (startD != nullptr)
            {
            	if (strcmp(startD, "late") == 0)
            	{
            		lateD = 1;
            		break;
				}
            	startD = strtok(nullptr, delim); 	
			}
            char * startP = strtok(reviewP, delim);
            while (startP != nullptr)
            {
            	if (strcmp(startP, "late") == 0)
            	{
            		lateP = 1;
            		break;
				}
            	startP = strtok(nullptr, delim);
			}
            for (int i = 0; i < pNum; i++)  // 找相符id 
            {
                if (p[i]->arrive(id, x, y, rP, lateP))
                {
                    d[p[i]->driverPos]->arrive(x, y, rD, lateD);  // driverPos: 司機陣列位置 
                    p[i]->driverPos = -1;  // 清除司機資料
                    break;
                }
            }
        }
        else if (event == 'C')  // 司機關閉app 
        {
            cin >> id;
            for (int i = 0; i < dNum; i++)  // 找相符id 
                if (d[i]->close(id))
                    break;
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
