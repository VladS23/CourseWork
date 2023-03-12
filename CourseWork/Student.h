#pragma once
#include "Structures.h"
#include "Person.h"
class Student : public Person {
private:
	int yearOfAdmission;
	char faculty[64];
	char departments[64];
	char group[16];
	char numGradebook[16];
	vector<Session> sessions;
public:
	Student(char[10240]);
	vector<char> toCharVec();
	int getYearOfAdmission() { return yearOfAdmission; };
	char* getFaculty();
	char* getDepartments();
	char* getGroup();
	char* getNumGradebook();
	Session getSessionByIndex(int);
	bool setYearOfAdmission(int);
	bool setFaculty(char[64]);
	bool setDepartments(char[64]);
	bool setGroup(char[64]);
	bool setNumGradebook(char[16]);
	bool deleteSessionByIndex(int);
	bool addSession();
	bool updSesResultByIndex(Result, int);
	bool addSesResultByIndex(Result, int);
	bool deleteSesResultByIndex(int);
};
