#include "Student.h"
#include "Person.h"
#include <vector>
//Данные разделены :, заканчивается ;
Student::Student(char initString [1024]) {
	vector <dataEl> initVector;
	int i = 0;
	while (initString[i] != ';') {
		dataEl curDataEl;
		int k = 0;
		while (k < 64 && curDataEl.chars[k] != '\0') {
			curDataEl.chars[k] = '\0';
			k++;
		}
		int j = 0;
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
		initVector.push_back(curDataEl);
	}
	i = 0;
	int curentInitVecEl = 0;
	while (i < 64) {
		name[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	int date[3];
	int curDateEl = 0;
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
		date[curDateEl] = atoi(curInt);
		curDateEl++;
	}
	dateOfBorn.day = date[0];
	dateOfBorn.mounth = date[1];
	dateOfBorn.year = date[2];
	i = 0;
	curentInitVecEl++;
	yearOfAdmission = atoi(initVector[curentInitVecEl].chars);
	curentInitVecEl++;
	while (i < 64) {
		faculty[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	while (i < 64) {
		departments[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	while (i < 16) {
		group[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	while (i < 16) {
		numGradebook[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	while (i < 32) {
		gender[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	auto h = 0 + 9;
}
