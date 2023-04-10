#include "Student.h"
#include "Person.h"
#include "Database.h"
#include"CryptoTools.h"
#include <iostream>
#include <charconv>
#include "MyList.h"
#include "StudentParser.h"

Student::Student() {
;}
Student::Student(char initString [10240]) {
	StudentParser::parse(initString, this);
}

MyList <char> Student::toCharVec() {
	MyList<char> result;
	result.push_back(';');
	int i = 0;
	while (name[i] != '\0') {
		result.push_back(name[i]);
		i++;
	}
	result.push_back(':');
	char date[16];
	char day[4];
	char month[4];
	char year[8];
	sprintf_s(day, "%d", dateOfBorn.day);
	sprintf_s(month, "%d", dateOfBorn.month);
	sprintf_s(year, "%d", dateOfBorn.year);
	i = 0;
	while (day[i] != '\0') {
		result.push_back(day[i]);
		i++;
	}
	result.push_back('.');
	i = 0;
	while (month[i] != '\0') {
		result.push_back(month[i]);
		i++;
	}
	result.push_back('.');
	i = 0;
	while (year[i] != '\0') {
		result.push_back(year[i]);
		i++;
	}
	result.push_back(':');
	sprintf_s(year, "%d", yearOfAdmission);
	i = 0;
	while (year[i] != '\0') {
		result.push_back(year[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (faculty[i] != '\0') {
		result.push_back(faculty[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (departments[i] != '\0') {
		result.push_back(departments[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (group[i] != '\0') {
		result.push_back(group[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (numGradebook[i] != '\0') {
		result.push_back(numGradebook[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (gender[i] != '\0') {
		result.push_back(gender[i]);
		i++;
	}
	result.push_back(':');
	for (int i = 0; i < sessions.size(); i++) {
		for (int j=0; j < sessions[i].oneRes.size(); j++) {
			char sesnum[4];
			sprintf_s(sesnum, "%d", sessions[i].numSesion);
			int k = 0;
			while (sesnum[k]!='\0')
			{
				result.push_back(sesnum[k]);
				k++;
			}
			result.push_back(':');
			k = 0;
			while (sessions[i].oneRes[j].subName[k] != '\0')
			{
				result.push_back(sessions[i].oneRes[j].subName[k]);
				k++;
			}
			result.push_back(':');
			char grad[4];
			sprintf_s(grad, "%d", sessions[i].oneRes[j].grading);
			k = 0;
			while (grad[k] != '\0')
			{
				result.push_back(grad[k]);
				k++;
			}
			result.push_back(':');
		}
	}
	result[result.size() - 1] = ';';
	result.push_back('\n');
	return result;
}

char* Student::getFaculty()
{
	char* res = new char [sizeof(faculty)];
	for (int i = 0; i < sizeof(faculty) / sizeof(char); i++) {
		*(res + i) = faculty[i];
	}
	return res;
}

char* Student::getDepartments()
{
	char* res = new char[sizeof(departments)];
	for (int i = 0; i < sizeof(departments) / sizeof(char); i++) {
		*(res + i) = departments[i];
	}
	return res;
}

char* Student::getGroup()
{
	char* res = new char[sizeof(group)];
	for (int i = 0; i < sizeof(group) / sizeof(char); i++) {
		*(res + i) = group[i];
	}
	return res;
}

char* Student::getNumGradebook()
{
	char* res = new char[sizeof(numGradebook)];
	for (int i = 0; i < sizeof(numGradebook) / sizeof(char); i++) {
		*(res + i) = numGradebook[i];
	}
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