#pragma once
#include <vector>
#include "MyList.h"
using namespace std;
struct Date {
	int day;
	int month;
	int year;
	char* toCharArray() {
		char* date1 = new char[16];
		char day1[4];
		char month1[4];
		char year1[8];
		MyList <char> result;
		sprintf_s(day1, "%d", day);
		sprintf_s(month1, "%d", month);
		sprintf_s(year1, "%d", year);
		int i = 0;
		while (day1[i] != '\0') {
			result.push_back(day1[i]);
			i++;
		}
		result.push_back('.');
		i = 0;
		while (month1[i] != '\0') {
			result.push_back(month1[i]);
			i++;
		}
		result.push_back('.');
		i = 0;
		while (year1[i] != '\0') {
			result.push_back(year1[i]);
			i++;
		}
		result.push_back('\0');
		for (int i = 0; i < result.size(); i++) {
			date1[i] = result[i];
		}
		return date1;
	}
};
struct Result
{
	char subName[64];
	int grading;
};
struct Session {
	int numSesion;
	MyList <Result> oneRes;
};
struct dataEl
{
	char chars [64];
};
