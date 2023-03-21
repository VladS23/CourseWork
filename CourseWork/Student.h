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
	Student(char initString[10240]);
	vector<char> toCharVec();
	int getYearOfAdmission() { return yearOfAdmission; };
	char* getFaculty();
	char* getDepartments();
	char* getGroup();
	char* getNumGradebook();
	Session getSessionByIndex(int index);
	bool setYearOfAdmission(int year);
	bool setFaculty(char newVal[64]);
	bool setDepartments(char newVal[64]);
	bool setGroup(char newVal[16]);
	bool setNumGradebook(char newVal[16]);
	bool deleteSessionByNum(int num);
	bool addSessionByNum(int num);
	bool updSesResultByIndex(Result res, int sesNum, int resInd); //TODO
	bool addSesResult(Result res, int sesNum);
	bool deleteSesResultByIndex(int sesNum, int resInd); //TODO
	int getSessionsSize();
	static int tests();
};
