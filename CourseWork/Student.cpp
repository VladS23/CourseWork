#include "Student.h"
#include "Person.h"
#include "Database.h"
#include"CryptoTools.h"
#include <vector>
#include <iostream>
#include <charconv>

/// <summary>
/// Строка инициализации состоит из данных разделеных : в конце и начале ; 
/// формат строки ";ФИО:Дата рождения:Год поступления:Институт:факультет:Кафедра:Группа:Номер Зачетки:Номер сессии1:предмет1:оценка1:Номер сессии1:предметn:оценкаn6:Номер сессииk:предметm:оценкаm;"
/// оценки за сесию должны быть отсортированы по возрастанию номера сессии, к которой они относятся 
/// </summary>
/// <param name="initString"></param>
Student::Student(char initString [10240]) {
	//вектор для хранения данных разбитых по :
	vector <dataEl> initVector;
	int i = 0;
	if (initString[i] == ';') {
		i++;
		while (initString[i] != ';') {
			//в вектор нельзя добавить массив, поэтому обернем его в структуру
			dataEl curDataEl;
			//инициализируем массив нуль символами
			int k = 0;
			while (k < 64 && curDataEl.chars[k] != '\0') {
				curDataEl.chars[k] = '\0';
				k++;
			}
			int j = 0;
			//разбиваем строку по : в масиивы символов
			while (initString[i] != ':' && initString[i + 1] != ';') {
				curDataEl.chars[j] = initString[i];
				i++;
				j++;
			}
			if (initString[i + 1] == ';') {
				curDataEl.chars[j] = initString[i];
			}
			i++;
			//добавляем получившийся массив в вектор
			initVector.push_back(curDataEl);
		}
		i = 0;
		int curentInitVecEl = 0;
		//записываем первый элемент вектора в фио
		while (i < 64) {
			name[i] = initVector[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		int date[3];
		int curDateEl = 0;
		//разбиваем второй элемент по .
		while (initVector[curentInitVecEl].chars[i] != '\0')
		{
			char curInt[8] = { '0' };
			int k = 0;
			while (initVector[curentInitVecEl].chars[i] != '.' && initVector[curentInitVecEl].chars[i] != '\0') {
				curInt[k] = initVector[curentInitVecEl].chars[i];
				i++;
				k++;
			}
			i++;
			//преобразуем каждый из получившихся массивов к инту и добавим в массив
			date[curDateEl] = atoi(curInt);
			curDateEl++;
		}
		//на основании массива инициализируем структуру для хранения даты рождения
		dateOfBorn.day = date[0];
		dateOfBorn.month = date[1];
		dateOfBorn.year = date[2];
		i = 0;
		curentInitVecEl++;
		//запишем следующий элемент вектора в дату поступления, преобразовав его к инту
		yearOfAdmission = atoi(initVector[curentInitVecEl].chars);
		curentInitVecEl++;
		//инициализируем институт следующим элементом вектора
		while (i < 64) {
			faculty[i] = initVector[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		//инициализируем кафедру следующим элементом вектора
		while (i < 64) {
			departments[i] = initVector[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		//инициализируем группу следующим элементом вектора
		while (i < 16) {
			group[i] = initVector[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		//инициализируем зачетку следующим элементом вектора
		while (i < 16) {
			numGradebook[i] = initVector[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		//инициализируем пол следующим элементом вектора
		while (i < 32) {
			gender[i] = initVector[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		int prevSession = 0;
		int curSesIterator = -1;
		while (curentInitVecEl < initVector.size())
		{
			if (atoi(initVector[curentInitVecEl].chars) > prevSession) {
				Session curSes;
				prevSession = atoi(initVector[curentInitVecEl].chars);
				curSes.numSesion = atoi(initVector[curentInitVecEl].chars);
				sessions.push_back(curSes);
				curSesIterator++;
				curentInitVecEl++;
			}
			else {
				curentInitVecEl++;
			}
			Result curOneRes;
			int i = 0;
			while (i < 64) {
				curOneRes.subName[i] = initVector[curentInitVecEl].chars[i];
				i++;
			}
			curentInitVecEl++;
			curOneRes.grading = atoi(initVector[curentInitVecEl].chars);
			sessions[curSesIterator].oneRes.push_back(curOneRes);
			curentInitVecEl++;
		}
	}
}
vector<char> Student::toCharVec() {
	vector<char> result;
	result.push_back(';');
	int i = 0;
	while (name[i] != '\0') {
		result.push_back(name[i]);
		i++;
	}
	result.push_back(':');
	char date[16];
	char day[4];
	char month[4];
	char year[8];
	sprintf_s(day, "%d", dateOfBorn.day);
	sprintf_s(month, "%d", dateOfBorn.month);
	sprintf_s(year, "%d", dateOfBorn.year);
	i = 0;
	while (day[i] != '\0') {
		result.push_back(day[i]);
		i++;
	}
	result.push_back('.');
	i = 0;
	while (month[i] != '\0') {
		result.push_back(month[i]);
		i++;
	}
	result.push_back('.');
	i = 0;
	while (year[i] != '\0') {
		result.push_back(year[i]);
		i++;
	}
	result.push_back(':');
	sprintf_s(year, "%d", yearOfAdmission);
	i = 0;
	while (year[i] != '\0') {
		result.push_back(year[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (faculty[i] != '\0') {
		result.push_back(faculty[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (departments[i] != '\0') {
		result.push_back(departments[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (group[i] != '\0') {
		result.push_back(group[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (numGradebook[i] != '\0') {
		result.push_back(numGradebook[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (gender[i] != '\0') {
		result.push_back(gender[i]);
		i++;
	}
	result.push_back(':');
	for (int i = 0; i < sessions.size(); i++) {
		for (int j=0; j < sessions[i].oneRes.size(); j++) {
			char sesnum[4];
			sprintf_s(sesnum, "%d", sessions[i].numSesion);
			int k = 0;
			while (sesnum[k]!='\0')
			{
				result.push_back(sesnum[k]);
				k++;
			}
			result.push_back(':');
			k = 0;
			while (sessions[i].oneRes[j].subName[k] != '\0')
			{
				result.push_back(sessions[i].oneRes[j].subName[k]);
				k++;
			}
			result.push_back(':');
			char grad[4];
			sprintf_s(grad, "%d", sessions[i].oneRes[j].grading);
			k = 0;
			while (grad[k] != '\0')
			{
				result.push_back(grad[k]);
				k++;
			}
			result.push_back(':');
		}
	}
	result[result.size() - 1] = ';';
	result.push_back('\n');
	return result;
}

char* Student::getFaculty()
{
	char* res = new char [sizeof(faculty)];
	for (int i = 0; i < sizeof(faculty) / sizeof(char); i++) {
		*(res + i) = faculty[i];
	}
	return res;
}
char* Student::getDepartments()
{
	char* res = new char[sizeof(departments)];
	for (int i = 0; i < sizeof(departments) / sizeof(char); i++) {
		*(res + i) = departments[i];
	}
	return res;
}

char* Student::getGroup()
{
	char* res = new char[sizeof(group)];
	for (int i = 0; i < sizeof(group) / sizeof(char); i++) {
		*(res + i) = group[i];
	}
	return res;
}

char* Student::getNumGradebook()
{
	char* res = new char[sizeof(numGradebook)];
	for (int i = 0; i < sizeof(numGradebook) / sizeof(char); i++) {
		*(res + i) = numGradebook[i];
	}
	return res;
}

Session Student::getSessionByIndex(int index)
{
	return sessions[index];
}

bool Student::setYearOfAdmission(int year)
{
	if (year > 1900 && year < 2050) {
		yearOfAdmission = year;
		return true;
	}
	return false;
}

bool Student::setFaculty(char newVal [64] )
{
	if (checkCharArray(newVal, 64))
	{
		for (int i = 0; i < 64; i++) {
			faculty[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::setDepartments(char newVal [64])
{
	if (checkCharArray(newVal, 64))
	{
		for (int i = 0; i < 64; i++) {
			departments[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::setGroup(char newVal [64])
{
	if (checkCharArray(newVal, 64))
	{
		for (int i = 0; i < 64; i++) {
			group[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::setNumGradebook(char newVal [16])
{
	if (checkCharArray(newVal, 16))
	{
		for (int i = 0; i < 16; i++) {
			numGradebook[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::deleteSessionByNum(int num)
{
	vector <Session>::iterator Iter;
	int ind = -1;
	for (int i = 0; i < sessions.size(); i++) {
		if (sessions[i].numSesion == num) {
			ind = i;
			break;
		}
	}
	if (ind != -1) {
		Iter = sessions.begin()+ind;
		sessions.erase(Iter);
		return true;
	}
	return false;
}

bool Student::addSessionByNum(int num)
{
	int ind = -1;
	for (int i = 0; i < sessions.size(); i++) {
		if (sessions[i].numSesion == num) {
			ind = i;
			break;
		}
	}
	if (ind == -1) {
		for (int i = 0; i < sessions.size()-1; i++) {
			if (sessions[i].numSesion<num && sessions[i + 1].numSesion>num) {
				ind = i + 1;
				break;
			}
		}
		if (ind == -1) {
			if (sessions[0].numSesion > num) {
				ind = 0;
			}
			if (sessions[sessions.size() - 1].numSesion < num) {
				ind = sessions.size();
			}
		}
		Session newSes;
		newSes.numSesion = num;
		sessions.insert(sessions.begin() + ind, newSes);
		return true;
	}
	return false;
}

bool Student::updSesResultByIndex(Result res, int sesNum, int resInd)
{
	int sesInd = -1;
	for (int i = 0; i < sessions.size() - 1; i++) {
		if (sessions[i].numSesion==sesNum) {
			sesInd = i;
			break;
		}
	}
	if (sesInd != -1) {
		if (resInd < sessions[sesInd].oneRes.size()) {
			sessions[sesInd].oneRes[resInd] = res;
			return true;
		}
	}
	return false;
}

bool Student::addSesResult(Result res, int sesNum)
{
	int sesInd = -1;
	for (int i = 0; i < sessions.size() - 1; i++) {
		if (sessions[i].numSesion == sesNum) {
			sesInd = i;
			break;
		}
	}
	if (sesInd != -1) {
		sessions[sesInd].oneRes.push_back(res);
		return true;
	}
	return false;
}

bool Student::deleteSesResultByIndex(int sesNum, int resInd)
{
	int sesInd = -1;
	for (int i = 0; i < sessions.size() - 1; i++) {
		if (sessions[i].numSesion == sesNum) {
			sesInd = i;
			break;
		}
	}
	if (sesInd != -1) {
		if (resInd < sessions[sesInd].oneRes.size()) {
			sessions[sesInd].oneRes.erase(sessions[sesInd].oneRes.begin() + resInd);
				return true;
		}
	}
	return false;
}
int Student::getSessionsSize()
{
	return sessions.size();
}
/// <summary>
/// test all methods of programm
/// </summary>
/// <returns></returns>
int Student::tests()
{
	char c1[1024] = ";Петров Петр Петрович:1.12.2003:2021:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:calculation:4:1:phys:3:2:programming:5:3:SecurityOS:4:4:SecurityDB:5;";
	Student s1(c1);
	int y = 5 + 9;
	vector <char> v1 = s1.toCharVec();
	char* c2 = (char*)malloc(sizeof(char) * v1.size());
	for (int i = 0; i < v1.size(); i++) {
		*(c2 + i) = v1[i];
	}
	*(c2 + v1.size()) = '\0';
	Student s2(c2);
	vector <char> v2 = s2.toCharVec();
	char* c3 = (char*)malloc(sizeof(char) * v2.size());
	for (int i = 0; i < v2.size(); i++) {
		*(c3 + i) = v2[i];
	}
	int i1 = s1.getYearOfAdmission();
	char* cc1 = s1.getFaculty();
	char* cc2 = s1.getDepartments();
	char* cc3 = s1.getGroup();
	char* cc4 = s1.getNumGradebook();
	char* cc5 = s1.getName();
	char* cc6 = s1.getGender();
	Date d1 = s1.getDateOfBorn();
	vector <bool> boleanTest;
	boleanTest.push_back(s1.setYearOfAdmission(1232)==false);
	boleanTest.push_back(s1.setYearOfAdmission(2018)==true);
	char ccc1[64] = "ИИТ";
	char ccc2[64] = ":ИИТ;";
	boleanTest.push_back(s1.setFaculty(ccc1)==true);
	boleanTest.push_back(s1.setFaculty(ccc2)==false);
	boleanTest.push_back(s1.deleteSessionByNum(5)==false);
	boleanTest.push_back(s1.deleteSessionByNum(4)==true);
	boleanTest.push_back(s1.deleteSessionByNum(2)==true);
	boleanTest.push_back(s1.deleteSessionByNum(2)==false);
	boleanTest.push_back(s1.deleteSessionByNum(1)==true);
	boleanTest.push_back(s1.addSessionByNum(1)==true);
	boleanTest.push_back(s1.addSessionByNum(2)==true);
	boleanTest.push_back(s1.addSessionByNum(2)==false);
	boleanTest.push_back(s1.addSessionByNum(10)==true);
	boleanTest.push_back(s1.addSessionByNum(4)==true);
	boleanTest.push_back(s1.addSessionByNum(6)==true);
	boleanTest.push_back(s1.addSessionByNum(5)==true);
	boleanTest.push_back(s1.updSesResultByIndex(Result{ "test1", 5 }, 3, 0)==true);
	boleanTest.push_back(s1.updSesResultByIndex(Result{ "test1", 5 }, 1, 10)==false);
	boleanTest.push_back(s1.updSesResultByIndex(Result{ "test1", 5 }, 777, 1)==false);
	boleanTest.push_back(s1.addSesResult(Result{ "test0", 5 }, 5)==true);
	s1.addSesResult(Result{ "test1", 5 }, 5);
	s1.addSesResult(Result{ "test2", 5 }, 5);
	s1.addSesResult(Result{ "test3", 5 }, 5);
	boleanTest.push_back(s1.addSesResult(Result{ "test1", 5 }, 777)==false);
	boleanTest.push_back(s1.deleteSesResultByIndex(5, 2)==true);
	boleanTest.push_back(s1.deleteSesResultByIndex(5, 777)==false);
	boleanTest.push_back(s1.setDateOfBorn(Date{ 12, 12, 2004 })==true);
	boleanTest.push_back(s1.setDateOfBorn(Date{ 777, 777, 777 })==false);
	char dbt1[1024] = ";Петров Петр Петрович:1.12.2003:2021:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:calculation:4:1:phys:3:2:programming:5:3:SecurityOS:4:4:SecurityDB:5;";
	char dbt2[1024] = ";Иванов Иван Иванович:1.12.2003:2021:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:calculation:4:1:phys:3:2:programming:5:3:SecurityOS:4:4:SecurityDB:5;";
	//Database db1;
	//db1.students.push_back(dbt1);
	//db1.students.push_back(Student(dbt2));
	//boleanTest.push_back(db1.saveDb()==true);
	//char ccc3[64] = "D:\\students1.txt";
	//boleanTest.push_back(db1.loadDb(ccc3)==true);
	//char t1[] = "1,1,3,4,5,2.";
	//vector <Student> svec1;
	//boleanTest.push_back(db1.addFilter(t1, svec1) == false);
	char indt1[1024] = ";Петров Петр Петрович:1.12.2003:2342:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:test:5:1:test:5:2:test:5;";
	char indt2[1024] = ";Васильев Василий Василиевич:1.12.2003:3232:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:test:5:2:test:5:2:test:5:2:test:5:2:test:5;";
	char indt3[1024] = ";Тимофеев Тимофей Тимофеевич:1.12.2003:1411:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:test:5:1:test:5:1:test:5:3:test:5:3:test:5:3:test:5:3:test:5:3:test:5:3:test:5:3:test:5:3:test:5:3:test:5;";
	char indt4[1024] = ";Чаплин Чарли Чарлеевич:1.12.2003:4122:ИКБ:КБ-1:БАСО-01-21:Б0404:male:2:test:5:2:test:5:2:test:5:2:test:5:2:test:5:2:test:5;";
	Database db2;
	vector <Student> svec2;
	db2.students.push_back(Student(indt1));
	db2.students.push_back(Student(indt2));
	db2.students.push_back(Student(indt3));
	db2.students.push_back(Student(indt4));
	char fl1[16]="1";
	db2.addFilter(fl1, svec2);
	boleanTest.push_back(svec2[0].getYearOfAdmission() == 1411 && svec2[1].getYearOfAdmission() == 2342 && svec2[2].getYearOfAdmission() == 3232 && svec2[3].getYearOfAdmission() == 4122);
	svec2.clear();
	char fl2[16] = "1,2";
	db2.addFilter(fl2, svec2);
	boleanTest.push_back(svec2[0].getYearOfAdmission() == 4122 && svec2[1].getYearOfAdmission() == 3232 && svec2[2].getYearOfAdmission() == 2342 && svec2[3].getYearOfAdmission() == 1411);
	svec2.clear();
	char fl3[16] = "1,2,3";
	db2.addFilter(fl3, svec2);
	boleanTest.push_back(svec2[0].getYearOfAdmission() == 1411 && svec2[1].getYearOfAdmission() == 4122 && svec2[2].getYearOfAdmission() == 3232 && svec2[3].getYearOfAdmission() == 2342);
	svec2.clear();
	char fl4[16] = "3";
	db2.addFilter(fl4, svec2);
	boleanTest.push_back(svec2[0].getYearOfAdmission() == 1411);
	svec2.clear();
	char fl5[16] = "777";
	db2.addFilter(fl4, svec2);
	svec2.clear();
	db2.saveDb();
	char pathdb2[] = "D:\\students.txt";
	db2.loadDb(pathdb2);
	char chch[] = "УРАУРА";
	auto vcdb1 = db2.students[1].toCharVec();
	for (int i = 0; i < vcdb1.size(); i++) {
		std::cout << vcdb1[i];
	}
	std::cout << endl;
	db2.students[2].setName(chch);
	auto vcdb2 = db2.students[2].toCharVec();
	for (int i = 0; i < vcdb2.size(); i++) {
		//std::cout << vcdb2[i];
	}
	std::cout << endl;
	for (int i = 0; i < boleanTest.size(); i++) {
		if (boleanTest[i]) {
			cout << "TEST " << i + 1 << " PASSED" << endl;
		}
		else {
			cout << "!!!TEST " << i + 1 << " FAILED!!!" << endl;
		}
	}
	return 0;
}
