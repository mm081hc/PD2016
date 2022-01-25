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
};
void Course::init(int a, int b, char* c)
{// 設定課程資料 
	id = a;
	credit = b; 
	name = c;
}
int Course::getid()
{// 回傳Course ID 
	return id;
}
int Course::getCre()
{// 回傳學分 
	return credit;
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
{// 設定grade資料 
	ptrCourse = a;
	grade = b;
}
int CourseGrade::getGrade()
{// 回傳grade 
	return grade;
}
int CourseGrade::getCre()
{// 回傳學分 
	return ptrCourse->getCre();
}

class Student
{
private:
	int id;
	char* name;
	CourseGrade* cg[10];
	int gradeNum = 0;  // gradeNum: 算有幾個成績(用來當cg參數)
public:
	double aveGrade = 0;  // aveGrade: 平均成績 
	void countAve();
	void inti(int , char*);
	void setgra(CourseGrade*);
	int getid();
	char* getName();
};
void Student::countAve()
{// 計算加權平均 
	double sum = 0, num = 0;
	for (int i = 0; i < gradeNum; i++)
	{
		sum += (cg[i]->getGrade()) * (cg[i]->getCre());
		num += cg[i]->getCre();
	}
	aveGrade = sum / num;
}
void Student::inti(int a, char* b)
{// 設定學生資料 
	id = a;
	name = b;
}
void Student::setgra(CourseGrade* a)
{// 設定學生成績資料 
	cg[gradeNum] = a;
	gradeNum++;
}
int Student::getid()
{// 回傳student ID 
	return id;
}
char* Student::getName()
{// 回傳student name
	return name;
}

int main()
{
	int n = 0, m = 0, k = 0;
	char nameCour[1010][55] = {0}, nameStu[1010][55] = {0};
	// nameCour: course name // nameStu: student name
	cin >> n;  // n堂課
	Course* course = new Course[n];  // course: Course objects
	for (int i = 0; i < n; i++)  // 輸入課程資料 
	{
		char x = 0;  // x為不需要的符號(逗號/括號)
		int id = 0, cre = 0;  // id: course id // cre: credit 
		cin >> x >> id >> x >> cre >> x;
		int j = 0;
		while (cin >> nameCour[i][j])  // 輸入課程名稱 
		{
			if (nameCour[i][j] == ')')  // 若遇到 ')' 就跳出 
			{
				nameCour[i][j] = 0;
				break;
			}
			j++;
		}
		course[i].init(id, cre, nameCour[i]);  // 設定課程資料 
	}
	
	cin >> m;  // m個學生 
	Student* student = new Student[m];  // student: Student objects
	for (int i = 0; i < m; i++)  // 輸入學生資料 
	{
		char x = 0;  // x為不需要的符號(逗號/括號)
		int id = 0;  // id: student id
		cin >> x >> id >> x;
		int j = 0;
		while (cin >> nameStu[i][j])  // 輸入學生名稱 
		{
			if (nameStu[i][j] == ')')  // 若遇到 ')' 就跳出
			{
				nameStu[i][j] = 0;
				break;
			}
			j++;
		}
		student[i].inti(id, nameStu[i]);  // 設定學生資料 
	}
	
	cin >> k;  // k筆成績 
	CourseGrade* grade = new CourseGrade[k];  // grade: CourseGrade objects
	for (int i = 0; i < k; i++)  // 輸入成績 
	{
		int idC = 0, idS = 0, gra = 0;
		// idC: course id // idS: student // gra: grade
		char x = 0;  // x為不需要的符號(逗號)
		cin >> idC >> x >> idS >> x >> gra;
		for (int j = 0; j < n; j++)
		{// 找與idC相符的course 
			if (idC == course[j].getid())  // 若course id相同 
			{
				grade[i].inti(&course[j], gra);  // 設定成績資料 
				break;
			}
		}
		for (int j = 0; j < m; j++)
		{// 找與idS相符的student 
			if (idS == student[j].getid())  // 若student id相同 
			{
				student[j].setgra(&grade[i]);  // 設定學生資料 
				break;
			}
		}
	}

	Student* ptrStu[1010];  // ptrStu: 指向student[]的指標, 用來比大小 
	for (int i = 0; i < m; i++)
	{
		ptrStu[i] = &student[i];
		student[i].countAve();  // 計算每個學生的成績平均 
	}
	 
	for (int i = 0; i < m - 1; i++)  // bubble sort 
	{
		for (int j = i; j < m; j++)
		{
			if (ptrStu[j]->aveGrade > ptrStu[i]->aveGrade) // 若後者成績較高，兩人互換 
			{ 
				Student* temp = ptrStu[i];
				ptrStu[i] = ptrStu[j];
				ptrStu[j] = temp;
			}
			else if (ptrStu[j]->aveGrade == ptrStu[i]->aveGrade)  // 若兩人成績相同且後者名稱排序在前，兩人互換 
			{
				if (strcmp(ptrStu[i]->getName(), ptrStu[j]->getName()) > 0)
				{
					Student* temp = ptrStu[i];
					ptrStu[i] = ptrStu[j];
					ptrStu[j] = temp;						
				}
			}
		}
	}
	
	for (int i = 0; i < m - 1; i++)  // 輸出 
		cout << ptrStu[i]->getName() << " ";
	cout << ptrStu[m-1]->getName();

	return 0;
}
