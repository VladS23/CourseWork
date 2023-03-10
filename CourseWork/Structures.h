#pragma once
#include <vector>
using namespace std;
struct Date {
	int day;
	int mounth;
	int year;
};
struct Result
{
	int numSesion;
	char subName[64];
	int grading;
};
struct Session {
	int numSesion;
	vector <Result> oneRes;
};
struct dataEl
{
	char chars [64];
};
