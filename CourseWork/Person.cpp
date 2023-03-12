#include "Person.h"
#include <vector>
using namespace std;

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
