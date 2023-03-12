#pragma once
#include "Structures.h"
class Person {
protected:
	char name[64];
	Date dateOfBorn;
	char gender[32];
	bool checkCharArray(char*, int);
public:
	char* getName();
	Date getDateOfBorn() { return dateOfBorn; };
	char* getGender();
	bool setName(char newVal[64]);
	bool setDateOfBorn(Date date);
	bool setGender(char newVal[32]);
};