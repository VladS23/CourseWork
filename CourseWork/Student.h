#pragma once
#include "Structures.h"
#include "Person.h"
class Student : public Person{
	int yearOfAdmission;
	char faculty[64];
	char departments[64];
	char group[16];
	char numGradebook[16];
	vector<Session> Sesions;
public:
	Student(char [1024]);
};
