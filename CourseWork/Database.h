#pragma once
#include <vector>
#include "Student.h"
class Database
{
private:
	 char* DbPath;
public:
	Database();
	vector <Student> students;
	bool loadDb(char* dbPath);
	bool saveDb();
	void addStudent(Student newStudent);
};

