#include "Student.h"
#include "Person.h"
#include <vector>
#include <iostream>
#include <charconv>
/// <summary>
/// Строка инициализации состоит из данных разделеных : в конце ; 
/// формат строки "ФИО:Дата рождения:Год поступления:Институт:факультет:Кафедра:Группа:Номер Зачетки:Номер сессии1:предмет1:оценка1:Номер сессии1:предметn:оценкаn6:Номер сессииk:предметm:оценкаm;"
/// оценки за сесию должны быть отсортированы по возрастанию номера сессии, к которой они относятся 
/// </summary>
/// <param name="initString"></param>
Student::Student(char initString [1024]) {
	//вектор для хранения данных разбитых по :
	vector <dataEl> initVector;
	int i = 0;
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
		auto x= initString[i];
		while (initString[i] != ':' && initString[i+1] != ';') {
			curDataEl.chars[j] = initString[i];
			i++;
			j++;
		}
		if(initString[i + 1] == ';') {
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
		char curInt[8] = {'0'};
		int k = 0;
		while (initVector[curentInitVecEl].chars[i] != '.'  && initVector[curentInitVecEl].chars[i] != '\0') {
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
	while (curentInitVecEl< initVector.size())
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
vector<char> Student::toCharVec() {
	vector<char> result;
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
	return result;
}

char* Student::getFaculty()
{
	char* res = (char*)malloc(sizeof(faculty));
	for (int i = 0; i < sizeof(faculty) / sizeof(char); i++) {
		*(res + i) = faculty[i];
	}
	return res;
}
char* Student::getDepartments()
{
	char* res = (char*)malloc(sizeof(departments));
	for (int i = 0; i < sizeof(departments) / sizeof(char); i++) {
		*(res + i) = departments[i];
	}
	return res;
}

char* Student::getGroup()
{
	char* res = (char*)malloc(sizeof(group));
	for (int i = 0; i < sizeof(group) / sizeof(char); i++) {
		*(res + i) = group[i];
	}
	return res;
}

char* Student::getNumGradebook()
{
	char* res = (char*)malloc(sizeof(numGradebook));
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
