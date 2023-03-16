#pragma once
#include <vector>
#include "Student.h"
#include <set>
#include "CryptoTools.h"
class Database
{
private:
	 char* DbPath;
	 int countSes5(Student student, std::set<int> setSesNumbers);
	 CryptoTools crypt;
public:
	Database();
	vector <Student> students;
	bool loadDb(char* dbPath);
	bool saveDb();
	bool addFilter(char filtersStr[64], vector <Student> &filtred );
};

