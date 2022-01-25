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
    double lateCnt;  // lateCnt: late次數
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    int driverPos;  // driverPos: 紀錄司機陣列位置 
    Passenger (int);  // constructor
    void search(int, int);  // searching
    void travel(int);  // traveling
    void close();  // close
    void arrive(int, int, int, bool);  // arrive
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
void Passenger::search(int x, int y)
{// searching
    this->x = x;  // 設定x, y 
    this->y = y;
    status = searching;  // searching
    Passenger::offlineCnt--;  // offline人數-1 
    Passenger::searchingCnt++;  // searching人數+1 
}
void Passenger::travel(int d)
{// traveling
    driverPos = d;  // 設定司機陣列index 
    status = traveling;  // traveling
    Passenger::searchingCnt--;  // searching人數-1 
    Passenger::travelingCnt++;  // traveling人數+1 
}
void Passenger::close()
{// 強制關閉 app
    Passenger::searchingCnt--;  // searching人數-1 
    Passenger::offlineCnt++;  // offline人數+1 
    status = offline;  // offline
}
void Passenger::arrive(int x, int y, int r, bool late)
{// arrive
    if (late == 1)
        lateCnt++;
    this->x = x;  // 紀錄位置 
    this->y = y;
    ratings[ratingCnt] = r;  // 記錄評價 
    ratingCnt++;
    Passenger::travelingCnt--;  // close 
    Passenger::offlineCnt++;
    status = offline;  // offline
    double sum = 0;  // 計算rating average
    for (int i = 0; i < ratingCnt; i++)  // 計算評價總和 
        sum += ratings[i];
    ratingAve = sum / ratingCnt;
	score = ratingAve - 5 * (lateCnt / ratingCnt);  // 計算score    
}
bool Passenger::belowTwo()
{// 檢查rating average是否 < 2
//    cout << "score: " << score << endl;
    if (score < 2)  // 若 < 2，關閉app，回傳true 
    {
        close();
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
    double lateCnt;  // late次數 
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    Driver(int);  // constructor
    Driver();  // default constructor
    bool operator>(const Driver&) const;  // 判斷priority
    void open (int, int);  // open app (id, x, y)
    void travel();  // traveling
    void close ();  // close app (id)
    void arrive(int, int, int, bool);  // arrive (x, y, rating)
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
    score = 0;
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
void Driver::open(int x, int y)
{// open app
    this->x = x;  // 設定位置 
    this->y = y;
    status = searching;  // 狀態改為searching 
    Driver::offlineCnt--;  // offline人數-1
    Driver::searchingCnt++;  // searching人數+1 
}
void Driver::travel()
{// traveling
    status = traveling;  // traveling
    Driver::searchingCnt--;  // searching人數-1 
    Driver::travelingCnt++;  // traveling人數+1 
}
void Driver::close()
{// close app
    Driver::searchingCnt--;  // seaching人數-1 
    Driver::offlineCnt++;  // offline人數+1 
    status = offline;  // offline
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
    double sum = 0;  // 計算average rating 
    for (int i = 0; i < ratingCnt; i++)
        sum += ratings[i];
    ratingAve = sum / ratingCnt;
    score = ratingAve - 5 * (lateCnt / ratingCnt);  // 計算score 
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
//	cout << "id: " << id << " " << "status: " << status << endl;
    if (status == searching)    
    {
        if (num == searchingCnt - 1)
            cout << id;
        else
            cout << id << " ";
        num++;
    }   
}
 
//void assign(Passenger*, int, int, Driver* [], int, int, int);
// 分配司機: 傳入passenger, x, y, driver, number of drivers, m, m 
 
int main()
{
    char event = 0;  // event: 用來判斷輸入的狀況 
    int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
    // pNum: number of passengers // dNum: number of drivers 
    Passenger* ptr[10000];  // 指向Passenger物件的指標 
    Driver* dptr[10000];  // 指向Driver物件的指標   
    Passenger* p[100000];
    Driver* d[100000];
    
    cin >> m;
    while (cin >> event)
    {
        int id = 0;
        if (event == 'P')  // 乘客註冊 
        {// ok
            cin >> id;
            p[id] = new Passenger(id);  // 指標指向物件 
            ptr[pNum] = p[id];
			pNum++;
        }
        else if (event == 'D')  // 司機註冊 
        {// ok
            cin >> id;
            d[id] = new Driver(id);  // 指標指向物件
            dptr[dNum] = d[id];
            dNum++;
        }
        else if (event == 'O')  // 司機打開app 
        {// ok
            int x = 0, y = 0;
            cin >> id >> x >> y;
            d[id]->open(x, y);
        }
        else if (event == 'S')  // 乘客搜尋 
        {
        	const int k = m;
            int x = 0, y = 0;
            cin >> id >> x >> y;
            p[id]->search(x, y);
            if (!p[id]->belowTwo())  // 若乘客評價<2, close app
            {
				if (dptr[0]->searchConti())  // 若有司機未分配(searchingCnt > 0) 
			    {
			        Driver* prior = new Driver();  // prior: 指向應分配的司機 
			        int priorPos = -1;  // 儲存應分配的司機位置   
			        while (true)
			        {
			            for (int i = 0; i < dNum; i++)
			            {
			                if (dptr[i]->available(x, y, m))  // 若司機狀態為searching, 且距離<=m 
			                {
			                    if (*dptr[i] > *prior)  // 若d[i]有較高的priority 
			                    {
			                        prior = dptr[i];  // 替換指標 
			                        priorPos = i;  // 記下i值 
			                    }
			                }
			            }
			            if (priorPos != -1) // 若有找到司機，將乘客和司機的狀態改為traveling 
			            {
			                dptr[priorPos]->travel();
			                p[id]->travel(priorPos);
							break;
			            }
			            m += k;
			        }
			    }
			    else  // 若無司機可分配，乘客關閉app
			        p[id]->close();			
			
			}
        }
        else if (event == 'A')  // 抵達目的地 
        {// ok
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
            if (strstr(reviewD, "late") != nullptr)
                lateD = 1;
            if (strstr(reviewP, "late") != nullptr)
                lateP = 1;
            p[id]->arrive(x, y, rP, lateP);
            dptr[p[id]->driverPos]->arrive(x, y, rD, lateD);  // driverPos: 司機陣列位置 
            p[id]->driverPos = -1;  // 清除司機資料
        }
//          cout << "XD" << endl;
        else if (event == 'C')  // 司機關閉app 
        {// ok
            cin >> id;
            d[id]->close();
        }
    }
     
    int printNum = 0;
    for (int i = 0; i < dNum; i++)  // cout
        dptr[i]->print(printNum);
    return 0;
}
