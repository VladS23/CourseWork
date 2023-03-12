#include "Student.h"
#include "Person.h"
#include <vector>
#include <iostream>
#include <charconv>
/// <summary>
/// ������ ������������� ������� �� ������ ���������� : � ����� ; 
/// ������ ������ "���:���� ��������:��� �����������:��������:���������:�������:������:����� �������:����� ������1:�������1:������1:����� ������1:�������n:������n6:����� ������k:�������m:������m;"
/// ������ �� ����� ������ ���� ������������� �� ����������� ������ ������, � ������� ��� ��������� 
/// </summary>
/// <param name="initString"></param>
Student::Student(char initString [1024]) {
	//������ ��� �������� ������ �������� �� :
	vector <dataEl> initVector;
	int i = 0;
	while (initString[i] != ';') {
		//� ������ ������ �������� ������, ������� ������� ��� � ���������
		dataEl curDataEl;
		//�������������� ������ ���� ���������
		int k = 0;
		while (k < 64 && curDataEl.chars[k] != '\0') {
			curDataEl.chars[k] = '\0';
			k++;
		}
		int j = 0;
		//��������� ������ �� : � ������� ��������
		auto x= initString[i];
		while (initString[i] != ':' && initString[i+1] != ';') {
			curDataEl.chars[j] = initString[i];
			i++;
			j++;
		}
		if(initString[i + 1] == ';') {
			curDataEl.chars[j] = initString[i];
		}
		i++;
		//��������� ������������ ������ � ������
		initVector.push_back(curDataEl);
	}
	i = 0;
	int curentInitVecEl = 0;
	//���������� ������ ������� ������� � ���
	while (i < 64) {
		name[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	int date[3];
	int curDateEl = 0;
	//��������� ������ ������� �� .
	while (initVector[curentInitVecEl].chars[i] != '\0')
	{
		char curInt[8] = {'0'};
		int k = 0;
		while (initVector[curentInitVecEl].chars[i] != '.'  && initVector[curentInitVecEl].chars[i] != '\0') {
			curInt[k] = initVector[curentInitVecEl].chars[i];
			i++;
			k++;
		}
		i++;
		//����������� ������ �� ������������ �������� � ���� � ������� � ������
		date[curDateEl] = atoi(curInt);
		curDateEl++;
	}
	//�� ��������� ������� �������������� ��������� ��� �������� ���� ��������
	dateOfBorn.day = date[0];
	dateOfBorn.month = date[1];
	dateOfBorn.year = date[2];
	i = 0;
	curentInitVecEl++;
	//������� ��������� ������� ������� � ���� �����������, ������������ ��� � ����
	yearOfAdmission = atoi(initVector[curentInitVecEl].chars);
	curentInitVecEl++;
	//�������������� �������� ��������� ��������� �������
	while (i < 64) {
		faculty[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	//�������������� ������� ��������� ��������� �������
	while (i < 64) {
		departments[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	//�������������� ������ ��������� ��������� �������
	while (i < 16) {
		group[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	//�������������� ������� ��������� ��������� �������
	while (i < 16) {
		numGradebook[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	i = 0;
	//�������������� ��� ��������� ��������� �������
	while (i < 32) {
		gender[i] = initVector[curentInitVecEl].chars[i];
		i++;
	}
	curentInitVecEl++;
	int prevSession = 0;
	int curSesIterator = -1;
	while (curentInitVecEl< initVector.size())
	{
		if (atoi(initVector[curentInitVecEl].chars) > prevSession) {
			Session curSes;
			prevSession = atoi(initVector[curentInitVecEl].chars);
			curSes.numSesion = atoi(initVector[curentInitVecEl].chars);
			sessions.push_back(curSes);
			curSesIterator++;
			curentInitVecEl++;
		}
		else {
			curentInitVecEl++;
		}
		Result curOneRes;
		int i = 0;
		while (i < 64) {
			curOneRes.subName[i] = initVector[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		curOneRes.grading = atoi(initVector[curentInitVecEl].chars);
		sessions[curSesIterator].oneRes.push_back(curOneRes);
		curentInitVecEl++;
	}
}
vector<char> Student::toCharVec() {
	vector<char> result;
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
	return result;
}
