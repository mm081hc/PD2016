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
{// �]�w�ҵ{��� 
	id = a;
	credit = b; 
	name = c;
}
int Course::getid()
{// �^��Course ID 
	return id;
}
int Course::getCre()
{// �^�ǾǤ� 
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
{// �]�wgrade��� 
	ptrCourse = a;
	grade = b;
}
int CourseGrade::getGrade()
{// �^��grade 
	return grade;
}
int CourseGrade::getCre()
{// �^�ǾǤ� 
	return ptrCourse->getCre();
}

class Student
{
private:
	int id;
	char* name;
	CourseGrade* cg[10];
	int gradeNum = 0;  // gradeNum: �⦳�X�Ӧ��Z(�Ψӷ�cg�Ѽ�)
public:
	double aveGrade = 0;  // aveGrade: �������Z 
	void countAve();
	void inti(int , char*);
	void setgra(CourseGrade*);
	int getid();
	char* getName();
};
void Student::countAve()
{// �p��[�v���� 
	double sum = 0, num = 0;
	for (int i = 0; i < gradeNum; i++)
	{
		sum += (cg[i]->getGrade()) * (cg[i]->getCre());
		num += cg[i]->getCre();
	}
	aveGrade = sum / num;
}
void Student::inti(int a, char* b)
{// �]�w�ǥ͸�� 
	id = a;
	name = b;
}
void Student::setgra(CourseGrade* a)
{// �]�w�ǥͦ��Z��� 
	cg[gradeNum] = a;
	gradeNum++;
}
int Student::getid()
{// �^��student ID 
	return id;
}
char* Student::getName()
{// �^��student name
	return name;
}

int main()
{
	int n = 0, m = 0, k = 0;
	char nameCour[1010][55] = {0}, nameStu[1010][55] = {0};
	// nameCour: course name // nameStu: student name
	cin >> n;  // n���
	Course* course = new Course[n];  // course: Course objects
	for (int i = 0; i < n; i++)  // ��J�ҵ{��� 
	{
		char x = 0;  // x�����ݭn���Ÿ�(�r��/�A��)
		int id = 0, cre = 0;  // id: course id // cre: credit 
		cin >> x >> id >> x >> cre >> x;
		int j = 0;
		while (cin >> nameCour[i][j])  // ��J�ҵ{�W�� 
		{
			if (nameCour[i][j] == ')')  // �Y�J�� ')' �N���X 
			{
				nameCour[i][j] = 0;
				break;
			}
			j++;
		}
		course[i].init(id, cre, nameCour[i]);  // �]�w�ҵ{��� 
	}
	
	cin >> m;  // m�Ӿǥ� 
	Student* student = new Student[m];  // student: Student objects
	for (int i = 0; i < m; i++)  // ��J�ǥ͸�� 
	{
		char x = 0;  // x�����ݭn���Ÿ�(�r��/�A��)
		int id = 0;  // id: student id
		cin >> x >> id >> x;
		int j = 0;
		while (cin >> nameStu[i][j])  // ��J�ǥͦW�� 
		{
			if (nameStu[i][j] == ')')  // �Y�J�� ')' �N���X
			{
				nameStu[i][j] = 0;
				break;
			}
			j++;
		}
		student[i].inti(id, nameStu[i]);  // �]�w�ǥ͸�� 
	}
	
	cin >> k;  // k�����Z 
	CourseGrade* grade = new CourseGrade[k];  // grade: CourseGrade objects
	for (int i = 0; i < k; i++)  // ��J���Z 
	{
		int idC = 0, idS = 0, gra = 0;
		// idC: course id // idS: student // gra: grade
		char x = 0;  // x�����ݭn���Ÿ�(�r��)
		cin >> idC >> x >> idS >> x >> gra;
		for (int j = 0; j < n; j++)
		{// ��PidC�۲Ū�course 
			if (idC == course[j].getid())  // �Ycourse id�ۦP 
			{
				grade[i].inti(&course[j], gra);  // �]�w���Z��� 
				break;
			}
		}
		for (int j = 0; j < m; j++)
		{// ��PidS�۲Ū�student 
			if (idS == student[j].getid())  // �Ystudent id�ۦP 
			{
				student[j].setgra(&grade[i]);  // �]�w�ǥ͸�� 
				break;
			}
		}
	}

	Student* ptrStu[1010];  // ptrStu: ���Vstudent[]������, �ΨӤ�j�p 
	for (int i = 0; i < m; i++)
	{
		ptrStu[i] = &student[i];
		student[i].countAve();  // �p��C�Ӿǥͪ����Z���� 
	}
	 
	for (int i = 0; i < m - 1; i++)  // bubble sort 
	{
		for (int j = i; j < m; j++)
		{
			if (ptrStu[j]->aveGrade > ptrStu[i]->aveGrade) // �Y��̦��Z�����A��H���� 
			{ 
				Student* temp = ptrStu[i];
				ptrStu[i] = ptrStu[j];
				ptrStu[j] = temp;
			}
			else if (ptrStu[j]->aveGrade == ptrStu[i]->aveGrade)  // �Y��H���Z�ۦP�B��̦W�ٱƧǦb�e�A��H���� 
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
	
	for (int i = 0; i < m - 1; i++)  // ��X 
		cout << ptrStu[i]->getName() << " ";
	cout << ptrStu[m-1]->getName();

	return 0;
}
