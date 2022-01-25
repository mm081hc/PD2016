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
    double lateCnt;  // lateCnt: late����
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    int driverPos;  // driverPos: �����q���}�C��m 
    Passenger (int);  // constructor
    void search(int, int);  // searching
    void travel(int);  // traveling
    void close();  // close
    void arrive(int, int, int, bool);  // arrive
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
    score = 3;
}
void Passenger::search(int x, int y)
{// searching
    this->x = x;  // �]�wx, y 
    this->y = y;
    status = searching;  // searching
    Passenger::offlineCnt--;  // offline�H��-1 
    Passenger::searchingCnt++;  // searching�H��+1 
}
void Passenger::travel(int d)
{// traveling
    driverPos = d;  // �]�w�q���}�Cindex 
    status = traveling;  // traveling
    Passenger::searchingCnt--;  // searching�H��-1 
    Passenger::travelingCnt++;  // traveling�H��+1 
}
void Passenger::close()
{// �j������ app
    Passenger::searchingCnt--;  // searching�H��-1 
    Passenger::offlineCnt++;  // offline�H��+1 
    status = offline;  // offline
}
void Passenger::arrive(int x, int y, int r, bool late)
{// arrive
    if (late == 1)
        lateCnt++;
    this->x = x;  // ������m 
    this->y = y;
    ratings[ratingCnt] = r;  // �O������ 
    ratingCnt++;
    Passenger::travelingCnt--;  // close 
    Passenger::offlineCnt++;
    status = offline;  // offline
    double sum = 0;  // �p��rating average
    for (int i = 0; i < ratingCnt; i++)  // �p������`�M 
        sum += ratings[i];
    ratingAve = sum / ratingCnt;
	score = ratingAve - 5 * (lateCnt / ratingCnt);  // �p��score    
}
bool Passenger::belowTwo()
{// �ˬdrating average�O�_ < 2
//    cout << "score: " << score << endl;
    if (score < 2)  // �Y < 2�A����app�A�^��true 
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
    double lateCnt;  // late���� 
    double ratingAve;  // ratingAve: average rating
    double score;
public:
    Driver(int);  // constructor
    Driver();  // default constructor
    bool operator>(const Driver&) const;  // �P�_priority
    void open (int, int);  // open app (id, x, y)
    void travel();  // traveling
    void close ();  // close app (id)
    void arrive(int, int, int, bool);  // arrive (x, y, rating)
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
{// �P�_priority
    if (this->score > d.score)
        return true;  // �Yaverage rating�j�A�^��true
    else if (this->score == d.score && this->id < d.id)
        return true;  // �Yaverage rating�ۦP�Bid���p�A�^��true 
    return false;
}
void Driver::open(int x, int y)
{// open app
    this->x = x;  // �]�w��m 
    this->y = y;
    status = searching;  // ���A�אּsearching 
    Driver::offlineCnt--;  // offline�H��-1
    Driver::searchingCnt++;  // searching�H��+1 
}
void Driver::travel()
{// traveling
    status = traveling;  // traveling
    Driver::searchingCnt--;  // searching�H��-1 
    Driver::travelingCnt++;  // traveling�H��+1 
}
void Driver::close()
{// close app
    Driver::searchingCnt--;  // seaching�H��-1 
    Driver::offlineCnt++;  // offline�H��+1 
    status = offline;  // offline
}
void Driver::arrive(int x, int y, int r, bool late)
{
    if (late == 1)
        lateCnt++;
	this->x = x;  // ������m 
    this->y = y;
    status = searching;  // ���A��searching
    Driver::travelingCnt--;
    Driver::searchingCnt++;
    ratings[ratingCnt] = r;  // ����rating 
    ratingCnt++;
    double sum = 0;  // �p��average rating 
    for (int i = 0; i < ratingCnt; i++)
        sum += ratings[i];
    ratingAve = sum / ratingCnt;
    score = ratingAve - 5 * (lateCnt / ratingCnt);  // �p��score 
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
// ���t�q��: �ǤJpassenger, x, y, driver, number of drivers, m, m 
 
int main()
{
    char event = 0;  // event: �ΨӧP�_��J�����p 
    int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
    // pNum: number of passengers // dNum: number of drivers 
    Passenger* ptr[10000];  // ���VPassenger���󪺫��� 
    Driver* dptr[10000];  // ���VDriver���󪺫���   
    Passenger* p[100000];
    Driver* d[100000];
    
    cin >> m;
    while (cin >> event)
    {
        int id = 0;
        if (event == 'P')  // ���ȵ��U 
        {// ok
            cin >> id;
            p[id] = new Passenger(id);  // ���Ы��V���� 
            ptr[pNum] = p[id];
			pNum++;
        }
        else if (event == 'D')  // �q�����U 
        {// ok
            cin >> id;
            d[id] = new Driver(id);  // ���Ы��V����
            dptr[dNum] = d[id];
            dNum++;
        }
        else if (event == 'O')  // �q�����}app 
        {// ok
            int x = 0, y = 0;
            cin >> id >> x >> y;
            d[id]->open(x, y);
        }
        else if (event == 'S')  // ���ȷj�M 
        {
        	const int k = m;
            int x = 0, y = 0;
            cin >> id >> x >> y;
            p[id]->search(x, y);
            if (!p[id]->belowTwo())  // �Y���ȵ���<2, close app
            {
				if (dptr[0]->searchConti())  // �Y���q�������t(searchingCnt > 0) 
			    {
			        Driver* prior = new Driver();  // prior: ���V�����t���q�� 
			        int priorPos = -1;  // �x�s�����t���q����m   
			        while (true)
			        {
			            for (int i = 0; i < dNum; i++)
			            {
			                if (dptr[i]->available(x, y, m))  // �Y�q�����A��searching, �B�Z��<=m 
			                {
			                    if (*dptr[i] > *prior)  // �Yd[i]��������priority 
			                    {
			                        prior = dptr[i];  // �������� 
			                        priorPos = i;  // �O�Ui�� 
			                    }
			                }
			            }
			            if (priorPos != -1) // �Y�����q���A�N���ȩM�q�������A�אּtraveling 
			            {
			                dptr[priorPos]->travel();
			                p[id]->travel(priorPos);
							break;
			            }
			            m += k;
			        }
			    }
			    else  // �Y�L�q���i���t�A��������app
			        p[id]->close();			
			
			}
        }
        else if (event == 'A')  // ��F�ت��a 
        {// ok
            int x = 0, y = 0, rP = 0, rD = 0;
            char reviewD[501] = {0}, reviewP[501] = {0};
            bool lateD = 0, lateP = 0;  // lateD, lateP: �����q�����ȬO�_���(1) 
            cin >> id >> x >> y >> rD >> rP;
            cin.ignore();  // ���L�@�r�� 
            cin.getline(reviewD, 500);  // ��Jreview       
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
            dptr[p[id]->driverPos]->arrive(x, y, rD, lateD);  // driverPos: �q���}�C��m 
            p[id]->driverPos = -1;  // �M���q�����
        }
//          cout << "XD" << endl;
        else if (event == 'C')  // �q������app 
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
