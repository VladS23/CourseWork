#pragma once
#include <vector>
using namespace std;
struct Date {
	int day;
	int month;
	int year;
};
struct Result
{
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
