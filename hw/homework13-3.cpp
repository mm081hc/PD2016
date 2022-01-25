#include <iostream>
#include <cctype>
#include <cstring>
#include <cmath>
using namespace std;
// status: 0: offline, 1: searching, 2: traveling
const int offline = 0;
const int searching = 1;
const int traveling = 2;
class User { 
protected:
	static int offlineCnt; 
	static int searchingCnt; 
	static int travelingCnt; 
	int id;
	int status; int x;
	int y;
	int ratingCnt;
	int* ratings;
};
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
    double score;  // score: score
public:
    bool vip;  // 1: vip, 0: usual	
    int driverPos;  // driverPos: �����q���}�C��m 
    Passenger (int, int);  // constructor
    bool search(int, int, int);  // searching
    void travel(int);  // traveling
    void close(int);  // close
    bool arrive(int, int, int, int, bool);  // arrive
    void aveCount();  // �p��ratingAve, score
    bool belowTwo();  // �ˬdscore�O�_<2 
};
int Passenger::offlineCnt = 0;
int Passenger::searchingCnt = 0;
int Passenger::travelingCnt = 0;
Passenger::Passenger (int id, int vip)
{// constructor
    Passenger::offlineCnt++;
    this->id = id;
    this->vip = vip;
    status = offline;  // offline 
    x = y = 0;
    ratingCnt = 0;
    ratingAve = 3;  // ��lrating average 
    ratings = new int [10000];
    driverPos = -1;  // ��l�q���}�Cindex = -1 
    lateCnt = 0;  // ��llate���� 
    score = 3;  // ��lscore 
}
bool Passenger::search(int id, int x, int y)
{// searching
    if (this->id == id)  // �Y�P�ǤJid�۲šA�^��true 
    {
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
bool Passenger::arrive(int id, int x, int y, int r, bool late)
{// arrive
    if (this->id == id)  // �Y�P�ǤJid�۲šA�^��true 
    {
        if (late == 1)  // �Y�X�{late, late����+1 
            lateCnt++;
        this->x = x;  // ������m 
        this->y = y;
        close(r);  // close app
        aveCount();  // �p��rating average, score 
        return true;
    }
    return false;  // ���Ŧ^��false
}
void Passenger::aveCount()
{// �p��average rating, score
    double sum = 0;
    for (int i = 0; i < ratingCnt; i++)  // �p��average rating
        sum += ratings[i];
    ratingAve = sum / ratingCnt; 
	score = ratingAve - 5 * (lateCnt / ratingCnt);  // �p��score 
}
bool Passenger::belowTwo()
{// �ˬdscore�O�_ < 2
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
    double lateCnt;  // lateCnt: late���� 
    double ratingAve;  // ratingAve: average rating
    double score;  // score: score
public:
    Driver(int);  // constructor
    Driver();  // default constructor
    bool operator>(const Driver&) const;  // �P�_priority
    bool find(int );
    bool open (int, int, int);  // open app (id, x, y)
    void travel();  // traveling
    bool close (int);  // close app (id)
    void arrive(int, int, int, bool);  // arrive (x, y, rating)
    void aveCount();  // �p��average rating, score
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
    score = -10;  // �w����(?) 
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
bool Driver::find(int id)
{
	if (this->id == id)
		return true;
	return false;
}
bool Driver::operator>(const Driver& d) const
{// �P�_priority
    if (this->score > d.score)
        return true;  // �Yscore�j�A�^��true
    else if (this->score == d.score && this->id < d.id)
        return true;  // �Yscore�ۦP�Bid���p�A�^��true 
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
void Driver::arrive(int x, int y, int r, bool late)
{
    if (late == 1)  // �Y�X�{late, late����+1 
        lateCnt++;
	this->x = x;  // ������m 
    this->y = y;
    status = searching;  // ���A��searching
    Driver::travelingCnt--;
    Driver::searchingCnt++;
    ratings[ratingCnt] = r;  // ����rating 
    ratingCnt++;
    aveCount();  // �p��score

}
void Driver::aveCount()
{// �p��average rating, score
    double sum = 0;
    for (int i = 0; i < ratingCnt; i++)
        sum += ratings[i];
    ratingAve = sum / ratingCnt;
    score = ratingAve - 5 * (lateCnt / ratingCnt);
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
    char event = 0;  // event: �ΨӧP�_��J�����p 
    int m = 0, pNum = 0, dNum = 0;  // m: Manhattan distance 
    // pNum: number of passengers // dNum: number of drivers 
    Passenger* p[100000];  // ���VPassenger���󪺫��� 
    Driver* d[100000];  // ���VDriver���󪺫���   
     
    cin >> m;
    while (cin >> event)
    {
        int id = 0;
        if (event == 'P')  // ���ȵ��U 
        {
        	int vip = 0;
            cin >> vip >> id;
            p[pNum] = new Passenger(id, vip);  // ���Ы��V���� 
            pNum++;
        }
        else if (event == 'D')  // �q�����U 
        {
            cin >> id;
            d[dNum] = new Driver(id);  // ���Ы��V���� 
            dNum++;
        }
        else if (event == 'O')  // �q�����}app 
        {
            int x = 0, y = 0;
            cin >> id >> x >> y;
            for (int i = 0; i < dNum; i++)  // ��۲�id 
                if (d[i]->open(id, x, y))
                    break;
        }
        else if (event == 'S')  // ���ȷj�M 
        {
            int x = 0, y = 0, idD = 0;
            cin >> id >> x >> y;
            for (int i = 0; i < pNum; i++)  // ��۲�id 
            {
                if (p[i]->search(id, x, y))  // ���ŦX��Jid������ 
                {
                	if(p[i]->vip == 1)
					{// vip
						if (d[0]->searchConti())
						{
							cin >> idD;
							for (int j = 0; j < dNum; j++)
							{
								if (d[j]->find(idD))
								{
									p[i]->travel(j);
									d[j]->travel();
								}							
							}
						}
						else
							p[i]->close(0);
					}
	            	else
	            	{// usual
	                    if (p[i]->belowTwo())  // �Y���ȵ���<2, close app 
	                        break;
	                    else
	                        assign(p[i], x, y, d, dNum, m, m);  // ���tdriver
	                    break;                		
					}
				}
            }      
        }
        else if (event == 'A')  // ��F�ت��a 
        {
            int x = 0, y = 0, rP = 0, rD = 0;
            char reviewD[501] = {0}, reviewP[501] = {0};
            bool lateD = 0, lateP = 0;  // lateD, lateP: �����q�����ȬO�_���, �Y���=1 
            cin >> id >> x >> y >> rD >> rP;
            cin.ignore();  // ���L�@�r��
            cin.getline(reviewD, 500);  // ��Jreview
            cin.getline(reviewP, 500);
            for (int i = 0; i < strlen(reviewD); i++)  // �Nreview�ର�p�g 
                reviewD[i] = tolower(reviewD[i]);
            for (int i = 0; i < strlen(reviewP); i++)
                reviewP[i] = tolower(reviewP[i]);
            if (strstr(reviewD, "late") != nullptr)  // �Y�X�{late, lateD = 1
                lateD = 1;
            if (strstr(reviewP, "late") != nullptr)  // �Y�X�{late, lateP = 1 
                lateP = 1;
            for (int i = 0; i < pNum; i++)  // ��۲�id
            {
                if (p[i]->arrive(id, x, y, rP, lateP))
                {
                    d[p[i]->driverPos]->arrive(x, y, rD, lateD);  // driverPos: �q���}�C��m 
                    p[i]->driverPos = -1;  // �M���q�����
                    break;
                }
            }
        }
        else if (event == 'C')  // �q������app 
        {
            cin >> id;
            for (int i = 0; i < dNum; i++)  // ��۲�id 
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
