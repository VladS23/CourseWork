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
	char* res = (char*)malloc(sizeof(name));
	for (int i = 0; i < sizeof(name) / sizeof(char); i++) {
		*(res + i) = name[i];
	}
	return res;
}

char* Person::getGender()
{
	char* res = (char*)malloc(sizeof(gender));
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

bool Person::setGender(char newVal [32])
{
	if (checkCharArray(newVal, 64))
	{
		for (int i = 0; i < 64; i++) {
			gender[i] = newVal[i];
		}
		return true;
	}
	return false;
}
