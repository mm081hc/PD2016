#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class Course
{
private:
	int id;
	int credit;
	char* name;
public:
	void init(int, int, char*);
	int getid();
	int getCre();
	char* getName();
};
void Course::init(int a, int b, char* c)
{
	id = a;
	credit = b; 
	name = c;
//	cout << id << " " << b << " " << name << endl;
}
int Course::getid()
{// 回傳Course ID 
	return id;
}
int Course::getCre()
{// 回傳學分 
	return credit;
}
char* Course::getName()
{
	return name;
}

class CourseGrade
{
private:
	Course* ptrCourse;
	int grade;
public:
	void inti(Course* , int);
	int getGrade();
	int getCre();
};
void CourseGrade::inti(Course* a, int b)
{
	ptrCourse = a;
	grade = b;
//	cout << "hii" << " " << grade << endl;
}
int CourseGrade::getGrade()
{
	return grade;
}
int CourseGrade::getCre()
{
	return ptrCourse->getCre();
}


class Student
{
private:
	int id;
	char* name;
	CourseGrade* cg[15];  // 可能太小 
	int gradeNum = 0;
public:
	double aveGrade = 0;
	CourseGrade* getcg(int a);
	void inti(int , char*);
	void setgra(CourseGrade*);
	int getid();
	char* getName();	
};
CourseGrade* Student::getcg(int a)
{
	return cg[a];
//	cout << name << " " << aveGrade << endl;
}
void Student::inti(int a, char* b)
{
	id = a;
	name = b;
//	cout << id << " " << name << endl;
}
void Student::setgra(CourseGrade* a)
{
	cg[gradeNum] = a;
	gradeNum++;
//	cout << "公威啊" << endl; 
}
int Student::getid()
{
	return id;
}
char* Student::getName()
{
	return name;
}

int main()
{
	int n = 0, m = 0, k = 0;
	char nameCour[1010][55] = {0}, nameStu[1010][55] = {0};

	cin >> n;
	Course* course = new Course[n];	
	for (int i = 0; i < n; i++)  // 輸入課程資料 
	{
		char x = 0;
		int id = 0, cre = 0;
		cin >> x >> id >> x >> cre >> x;
		cin.getline(nameCour[i], 55, ')');
		course[i].init(id, cre, nameCour[i]);
//		cout << id << " " << nameCour[i] << "XDDD" << endl;
	}
// ingnore?	
	cin >> m;
	Student* student = new Student[m];
	for (int i = 0; i < m; i++)  // 輸入學生資料 
	{
		char x = 0;
		int id = 0;
		cin >> x >> id >> x;
		cin.getline(nameStu[i], 55, ')');
		student[i].inti(id, nameStu[i]);
//		cout << nameStu[i] << endl;
	}
	
	cin >> k;
	CourseGrade* grade = new CourseGrade[k];
	int** stuGrade = new int* [m];  // m個學生 
	for (int i = 0; i < m; i++)
		stuGrade[i] = new int [n];  // 課程數
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
				stuGrade[i][j] = -1;
		
	for (int i = 0; i < k; i++)  // 輸入成績 
	{
		int gra = 0;
		char x = 0;
		char idC[55] = {0}, idS[55] = {0};
		cin.ignore(1, '\n');
		cin.getline(idC, 55, ',');
		cin.getline(idS, 55, ',');
		cin >> gra;
		if (isdigit(idC[0]) == 0) // course id非數字 
		{
			int courPos = 0;
			for (int j = 0; j < n; j++)
			{
				if (strcmp(idC, course[j].getName()) == 0)
				{
					grade[i].inti(&course[j], gra);
					courPos = j;
					break;
				}
			}

			if (isdigit(idS[0]) == 0)  // student id非數字 
			{
				for (int j = 0; j < m; j++)
				{
					if (strcmp(idS, student[j].getName()) == 0)
					{
						student[j].setgra(&grade[i]);
						stuGrade[j][courPos] = gra;  // 紀錄成績 
						break;
					}
				}
			}
			else  // 若student id為數字
			{ 
				int idStu = 0;
				for (int j = 0; j < strlen(idS); j++)
				{
					int temp = static_cast<int>(idS[j])-48;
					for (int k = 1; k < strlen(idS)-j; k++)
						temp = temp * 10;
					idStu += temp;
				}
				for (int j = 0; j < m; j++)
				{
					if (idStu == student[j].getid())
					{						
						student[j].setgra(&grade[i]);
						stuGrade[j][courPos] = gra;						
						break;
					}
				}
			}
		}
		else  // course id為數字 
		{
			int idCou = 0, courPos = 0;;
			for (int j = 0; j < strlen(idC); j++)
			{
				int temp = static_cast<int>(idC[j])-48;
				for (int k = 1; k < strlen(idC)-j; k++)
					temp = temp * 10;
				idCou += temp;				
			}
//			cout << idCou << endl;
			for (int j = 0; j < n; j++)
			{
				if (idCou == course[j].getid())
				{
					grade[i].inti(&course[j], gra);
					courPos = j;
					break;									
				}
			}
			if (isdigit(idS[0]) == 0)  // student id非數字 
			{
				for (int j = 0; j < m; j++)
				{
					if (strcmp(idS, student[j].getName()) == 0)
					{
						student[j].setgra(&grade[i]);
						stuGrade[j][courPos] = gra;					
						break;
					}
				}
			}
			else  // 若student id為數字
			{ 
				int idStu = 0;
				for (int j = 0; j < strlen(idS); j++)
				{
					int temp = static_cast<int>(idS[j])-48;
					for (int k = 1; k < strlen(idS)-j; k++)
						temp = temp * 10;
					idStu += temp;
				}
				
				for (int j = 0; j < m; j++)
				{
					if (idStu == student[j].getid())
					{
						student[j].setgra(&grade[i]);
						stuGrade[j][courPos] = gra;
						break;
					}
				}
			}
		}
	}

	int p = 0, stuID[1010] = {0}, input = 0;
	while (cin >> input)
	{
		for (int i = 0; i < m; i++)
		{
			if (input == student[i].getid())
			{
				stuID[p] = 	i;
//				cout << i << " ";
				break;
			}
		}
		p++;
	}
//	cout << p << endl;
/*	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << stuGrade[i][j] << " ";
		}
		cout << endl;
	}
*/	
	int dominNum = 0;
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < p; j++)
		{
			bool domin = 1;  // 假設所有成績stuID[i] > stuID[j]
			for (int k = 0; k < n; k++)  // 逐項比較各科成績 
			{
				if (stuGrade[stuID[i]][k] == -1 || stuGrade[stuID[j]][k] == -1)  // 若兩者有人為-1 
					continue;
				else if (stuGrade[stuID[i]][k] <= stuGrade[stuID[j]][k])
					domin = 0;
				if (domin == 0)  // 若非dominant 
					break;
			}
//			cout << domin << " ";
			if (domin == 1)
				dominNum++;
		}
	}
	cout << dominNum;

	return 0;
}
