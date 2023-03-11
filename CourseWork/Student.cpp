#include "Student.h"
#include "Person.h"
#include <vector>
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
	dateOfBorn.mounth = date[1];
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
			Sessions.push_back(curSes);
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
		Sessions[curSesIterator].oneRes.push_back(curOneRes);
		curentInitVecEl++;

	}
}
