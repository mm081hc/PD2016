#include <iostream>
#include <cstring>
#include <cctype>
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
    double lateCnt;  // lateCnt: lateΩ计
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    int driverPos;  // driverPos: 魁诀皚竚 
    Passenger (int);  // constructor
    void search(int, int);  // searching
    void travel(int);  // traveling
    void close();  // close
    void arrive(int, int, int, bool);  // arrive
    bool belowTwo();  // 浪琩average rating琌<2 
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
    ratingAve = 3;  // ﹍rating average 
    ratings = new int [10000];
    driverPos = -1;  // ﹍诀皚index = -1 
    lateCnt = 0;
    score = 3;
}
void Passenger::search(int x, int y)
{// searching
    this->x = x;  // 砞﹚x, y 
    this->y = y;
    status = searching;  // searching
    Passenger::offlineCnt--;  // offline计-1 
    Passenger::searchingCnt++;  // searching计+1 
}
void Passenger::travel(int d)
{// traveling
    driverPos = d;  // 砞﹚诀皚index 
    status = traveling;  // traveling
    Passenger::searchingCnt--;  // searching计-1 
    Passenger::travelingCnt++;  // traveling计+1 
}
void Passenger::close()
{// 眏闽超 app
    Passenger::searchingCnt--;  // searching计-1 
    Passenger::offlineCnt++;  // offline计+1 
    status = offline;  // offline
}
void Passenger::arrive(int x, int y, int r, bool late)
{// arrive
    if (late == 1)
        lateCnt++;
    this->x = x;  // 魁竚 
    this->y = y;
    ratings[ratingCnt] = r;  // 癘魁蝶基 
    ratingCnt++;
    Passenger::travelingCnt--;  // close 
    Passenger::offlineCnt++;
    status = offline;  // offline
    double sum = 0;  // 璸衡rating average
    for (int i = 0; i < ratingCnt; i++)  // 璸衡蝶基羆㎝ 
        sum += ratings[i];
    ratingAve = sum / ratingCnt;
	score = ratingAve - 5 * (lateCnt / ratingCnt);  // 璸衡score    
}
bool Passenger::belowTwo()
{// 浪琩rating average琌 < 2
//    cout << "score: " << score << endl;
    if (score < 2)  // 璝 < 2闽超app肚true 
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
    double lateCnt;  // lateΩ计 
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    Driver(int);  // constructor
    Driver();  // default constructor
    bool operator>(const Driver&) const;  // 耞priority
    void open (int, int);  // open app (id, x, y)
    void travel();  // traveling
    void close ();  // close app (id)
    void arrive(int, int, int, bool);  // arrive (x, y, rating)
    bool available(int, int, int);  // 浪琩琌Τ诀才兵ン (x, y, m) 
    bool searchConti();  // 浪琩琌Τ诀だ皌
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
{// 耞priority
    if (this->score > d.score)
        return true;  // 璝average rating肚true
    else if (this->score == d.score && this->id < d.id)
        return true;  // 璝average ratingid耕肚true 
    return false;
}
void Driver::open(int x, int y)
{// open app
    this->x = x;  // 砞﹚竚 
    this->y = y;
    status = searching;  // 篈эsearching 
    Driver::offlineCnt--;  // offline计-1
    Driver::searchingCnt++;  // searching计+1 
}
void Driver::travel()
{// traveling
    status = traveling;  // traveling
    Driver::searchingCnt--;  // searching计-1 
    Driver::travelingCnt++;  // traveling计+1 
}
void Driver::close()
{// close app
    Driver::searchingCnt--;  // seaching计-1 
    Driver::offlineCnt++;  // offline计+1 
    status = offline;  // offline
}
void Driver::arrive(int x, int y, int r, bool late)
{
    if (late == 1)
        lateCnt++;
	this->x = x;  // 魁竚 
    this->y = y;
    status = searching;  // 篈searching
    Driver::travelingCnt--;
    Driver::searchingCnt++;
    ratings[ratingCnt] = r;  // 魁rating 
    ratingCnt++;
    double sum = 0;  // 璸衡average rating 
    for (int i = 0; i < ratingCnt; i++)
        sum += ratings[i];
    ratingAve = sum / ratingCnt;
	score = ratingAve - 5 * (lateCnt / ratingCnt);  // 璸衡score 
}
bool Driver::available(int x, int y, int m)
{// 浪琩诀琌骸ì兵ン(searching, distance <= m) 
    if (status == searching)
        if (abs(this->x - x) + abs(this->y - y) <= m)
            return true;
    return false;
}
bool Driver::searchConti()
{// 浪琩琌Τ诀だ皌(Τ篈searching) 
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
// だ皌诀: 肚passenger, x, y, driver, number of drivers, m, m 
 
int main()
{
    char event = 0;  // event: ノㄓ耞块猵 
    int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
    // pNum: number of passengers // dNum: number of drivers 
    Passenger* ptr[10000];  // Passengerン夹 
    Driver* dptr[10000];  // Driverン夹   
    Passenger* p[100000];
    Driver* d[100000];
    
    cin >> m;
    const int k = m;    
    while (cin >> event)
    {
        int id = 0;
        if (event == 'P')  // 爹 
        {// ok
            cin >> id;
            p[id] = new Passenger(id);  // 夹ン 
            ptr[pNum] = p[id];
			pNum++;
        }
        else if (event == 'D')  // 诀爹 
        {// ok
            cin >> id;
            d[id] = new Driver(id);  // 夹ン
            dptr[dNum] = d[id];
            dNum++;
        }
        else if (event == 'O')  // 诀ゴ秨app 
        {// ok
            int x = 0, y = 0;
            cin >> id >> x >> y;
            d[id]->open(x, y);
        }
        else if (event == 'S')  // 穓碝 
        {
        	m = k;
            int x = 0, y = 0;
            cin >> id >> x >> y;
            p[id]->search(x, y);
            if (!p[id]->belowTwo())  // 璝蝶基<2, close app
            {
				if (dptr[0]->searchConti())  // 璝Τ诀ゼだ皌(searchingCnt > 0) 
			    {
			        Driver* prior = new Driver();  // prior: 莱だ皌诀 
			        int priorPos = -1;  // 纗莱だ皌诀竚   
			        while (true)
			        {
			            for (int i = 0; i < dNum; i++)
			            {
			                if (dptr[i]->available(x, y, m))  // 璝诀篈searching, 禯瞒<=m 
			                {
			                    if (*dptr[i] > *prior)  // 璝d[i]Τ耕蔼priority 
			                    {
			                        prior = dptr[i];  // 蠢传夹 
			                        priorPos = i;  // 癘i 
			                    }
			                }
			            }
			            if (priorPos != -1) // 璝Τт诀盢㎝诀篈эtraveling 
			            {
			                dptr[priorPos]->travel();
			                p[id]->travel(priorPos);
							break;
			            }
			            m += k;
//			            cout << "m: " << m;
			        }
			    }
			    else  // 璝礚诀だ皌闽超app
			        p[id]->close();			
			
			}
        }
        else if (event == 'A')  // ╄笷ヘ 
        {// ok
            int x = 0, y = 0, rP = 0, rD = 0;
            char reviewD[500] = {0}, reviewP[500] = {0};
            bool lateD = 0, lateP = 0;  // lateD, lateP: 魁诀琌筐(1)
            char* ptrD = nullptr, * ptrP = nullptr;
            cin >> id >> x >> y >> rD >> rP;
			cin.ignore();  // 铬筁じ 
            cin.getline(reviewD, 500);  // 块review       
            cin.getline(reviewP, 500);
            for (int i = 0; i < strlen(reviewD); i++)
                reviewD[i] = tolower(reviewD[i]);
            for (int i = 0; i < strlen(reviewP); i++)
                reviewP[i] = tolower(reviewP[i]);
            ptrD = strstr(reviewD, "late");                
            ptrP = strstr(reviewP, "late");
			if (ptrD != nullptr)
                lateD = 1;
            if (ptrP != nullptr)
                lateP = 1;
            p[id]->arrive(x, y, rP, lateP);
            dptr[p[id]->driverPos]->arrive(x, y, rD, lateD);  // driverPos: 诀皚竚 
            p[id]->driverPos = -1;  // 睲埃诀戈
        }
//          cout << "XD" << endl;
        else if (event == 'C')  // 诀闽超app 
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
