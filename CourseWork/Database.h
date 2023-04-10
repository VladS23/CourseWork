#pragma once
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
	MyList <Student> students;
	bool loadDb(char* dbPath);
	bool saveDb();
	bool addFilter(char filtersStr[64], MyList <Student> &filtred );
};

