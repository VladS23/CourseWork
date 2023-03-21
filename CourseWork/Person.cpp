#include "Person.h"
#include <vector>
using namespace std;

bool Person::checkCharArray(char* newVal, int len)
{
	for (int i = 0; i < len; i++) {
		if (*(newVal+i) == '\n' || *(newVal + i) == ';' || *(newVal + i) == ':') {
			return false;
		}
	}
	return true;
}

char* Person::getName()
{
	char* res = new char[sizeof(name)];
	for (int i = 0; i < sizeof(name) / sizeof(char); i++) {
		*(res + i) = name[i];
	}
	return res;
}

char* Person::getGender()
{
	char* res = new char[sizeof(gender)];
	for (int i = 0; i < sizeof(gender) / sizeof(char); i++) {
		*(res + i) = gender[i];
	}
	return res;
}

bool Person::setName(char newVal [64])
{
	if (checkCharArray(newVal, 64))
	{
		for (int i = 0; i < 64; i++) {
			name[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Person::setDateOfBorn(Date date)
{
	if (date.day <= 31 && date.day > 0) {
		if (date.month <= 12 && date.month > 0) {
			if (date.year <= 2050 && date.year > 1900) {
				dateOfBorn = date;
				return true;
			}
		}
	}
	return false;
}

bool Person::setGender(char newVal [32])
{
	if (checkCharArray(newVal, 32))
	{
		for (int i = 0; i < 32; i++) {
			gender[i] = newVal[i];
		}
		return true;
	}
	return false;
}
