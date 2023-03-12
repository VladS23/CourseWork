#pragma once
#include "Structures.h"
class Person {
private:
	char name[64];
	Date dateOfBorn;
	char gender[32];
public:
	char* getName();
	Date getDateOfBorn();
	char* getGender;
	bool setName(char[64]);
	bool setDateOfBorn(Date);
	bool setGender(char[32]);
};