#include "Student.h"
#include "Person.h"
#include "Database.h"
#include"CryptoTools.h"
#include <iostream>
#include <charconv>
#include "MyList.h"
#include "StudentParser.h"
#include "StudentStringBuilder.h"

Student::Student() {
;}
Student::Student(char initString [10240]) {
	StudentParser::parse(initString, this);
}

MyList <char> Student::toCharVec() {
	return StudentStringBuilder::toCharVec(this);
}

char* Student::getFaculty()
{
	char* res = new char [sizeof(faculty) / sizeof(char)];
	strcpy_s(res, sizeof(faculty) / sizeof(char), faculty);
	return res;
}

char* Student::getDepartments()
{
	char* res = new char[sizeof(departments) / sizeof(char)];
	strcpy_s(res, sizeof(departments) / sizeof(char), departments);
	return res;
}

char* Student::getGroup()
{
	char* res = new char[sizeof(group) / sizeof(char)];
	strcpy_s(res, sizeof(group) / sizeof(char), group);
	return res;
}

char* Student::getNumGradebook()
{
	char* res = new char[sizeof(numGradebook) / sizeof(char)];
	strcpy_s(res, sizeof(numGradebook) / sizeof(char), numGradebook);
	return res;
}

Session Student::getSessionByIndex(int index)
{
	return sessions[index];
}

bool Student::setYearOfAdmission(int year)
{
	if (year > 1900 && year < 2050) {
		yearOfAdmission = year;
		return true;
	}
	return false;
}

bool Student::setFaculty(char newVal [64] )
{
	if (checkCharArray(newVal, 64))
	{
		for (int i = 0; i < 64; i++) {
			faculty[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::setDepartments(char newVal [64])
{
	if (checkCharArray(newVal, 64))
	{
		for (int i = 0; i < 64; i++) {
			departments[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::setGroup(char newVal [16])
{
	if (checkCharArray(newVal, 16))
	{
		for (int i = 0; i < 16; i++) {
			group[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::setNumGradebook(char newVal [16])
{
	if (checkCharArray(newVal, 16))
	{
		for (int i = 0; i < 16; i++) {
			numGradebook[i] = newVal[i];
		}
		return true;
	}
	return false;
}

bool Student::deleteSessionByNum(int num)
{
	int ind = -1;
	for (int i = 0; i < sessions.size(); i++) {
		if (sessions[i].numSesion == num) {
			ind = i;
			break;
		}
	}
	if (ind != -1) {
		sessions.removeAt(ind);
		return true;
	}
	return false;
}

bool Student::addSessionByNum(int num)
{
	int ind = -1;
	for (int i = 0; i < sessions.size(); i++) {
		if (sessions[i].numSesion == num) {
			ind = i;
			break;
		}
	}
	if (!sessions.size() == 0) {
		if (ind == -1) {
			for (int i = 0; i < sessions.size() - 1; i++) {
				if (sessions[i].numSesion<num && sessions[i + 1].numSesion>num) {
					ind = i + 1;
					break;
				}
			}
			if (ind == -1) {
				if (sessions[0].numSesion > num) {
					ind = 0;
				}
				if (sessions[sessions.size() - 1].numSesion < num) {
					ind = sessions.size();
				}
			}
			Session newSes;
			newSes.numSesion = num;
			sessions.insert(newSes, ind);
			return true;
		}
	}
	else {
		Session newSes;
		newSes.numSesion = num;
		sessions.push_back(newSes);
		return true;
	}

	return false;
}

bool Student::updSesResultByIndex(Result res, int sesNum, int resInd)
{
	int sesInd = -1;
	for (int i = 0; i < sessions.size() - 1; i++) {
		if (sessions[i].numSesion==sesNum) {
			sesInd = i;
			break;
		}
	}
	if (sessions.size() == sesNum) {
		sessions[sesNum-1].oneRes[resInd] = res;
		return true;
	}
	if (sesInd != -1) {
		if (resInd < sessions[sesInd].oneRes.size()) {
			sessions[sesInd].oneRes[resInd] = res;
			return true;
		}
	}
	return false;
}

bool Student::addSesResult(Result res, int sesNum)
{
	int sesInd = -1;
	for (int i = 0; i < sessions.size() - 1; i++) {
		if (sessions[i].numSesion == sesNum) {
			sesInd = i;
			break;
		}
	}
	if (sessions.size() ==sesNum) {
		sessions[sesNum-1].oneRes.push_back(res);
		return true;
	}
	if (sesInd != -1) {
		sessions[sesInd].oneRes.push_back(res);
		return true;
	}
	return false;
}

bool Student::deleteSesResultByIndex(int sesNum, int resInd)
{
	int sesInd = -1;
	for (int i = 0; i < sessions.size() - 1; i++) {
		if (sessions[i].numSesion == sesNum) {
			sesInd = i;
			break;
		}
	}
	if (sessions.size() == sesNum) {
		sessions[sesNum-1].oneRes.removeAt(resInd);
		return true;
	}
	if (sesInd != -1) {
		if (resInd < sessions[sesInd].oneRes.size()) {
			sessions[sesInd].oneRes.removeAt(resInd);
				return true;
		}
	}
	return false;
}

int Student::getSessionsSize()
{
	return sessions.size();
}