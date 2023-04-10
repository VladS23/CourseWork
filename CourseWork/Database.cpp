#include "Database.h"
#include "MyList.h"
#include <fstream>
#include <string>
#include <regex>
#include <set>
#include <string.h>
#include <iostream>


using namespace std;

int Database::countSes5(Student student, std::set<int> setSesNumbers)
{
	int fives = 0;
	vector <int> vecSesNum(setSesNumbers.begin(), setSesNumbers.end());
	for (int i = 0; i < student.getSessionsSize(); i++) {
		for (int j = 0; j < vecSesNum.size(); j++) {
			if (student.getSessionByIndex(i).numSesion == vecSesNum[j]) {
				for (int k=0; k < student.getSessionByIndex(i).oneRes.size(); k++) {
					if (student.getSessionByIndex(i).oneRes[k].grading == 5) {
						fives++;
					}
				}
			}
		 }
	}
	return fives;
}

Database::Database() {
	char STANDART_PATH[] = "D:\\students.txt";
	DbPath = new char [sizeof(STANDART_PATH)/sizeof(char)];
	for (int i = 0; i < sizeof(STANDART_PATH) / sizeof(char); i++) {
		DbPath[i] = STANDART_PATH[i];
	}
}
bool Database::loadDb(char* dbPath)
{
	students.clear();
	byte buf;
	std::ifstream in(dbPath, std::ios::binary);
	MyList <byte> initString;
	if (!in.is_open()) {
		return false;
	}
	if (in.is_open())
	{
		while (in >> noskipws >> buf) {
			initString.push_back(buf);
		}
	}
	char* plaintext = new char[initString.size()];
	for (int i = 0; i < initString.size(); i++) {
		plaintext[i] = initString[i];
	}
	crypt.Decrypt(plaintext, initString.size());
	int count=0;
	MyList<char> initList;
	for (int i = 0; i < strlen(plaintext); i++) {
		if (plaintext[i] == ';') {
			count++;
		}
		if (count == 1) {
			initList.push_back(plaintext[i]);
		}
		if (count == 2) {
			initList.push_back(plaintext[i]);
			char* initArr = new char[initList.size()];
			for (int j = 0; j < initList.size(); j++) {
				initArr[j] = initList[j];
			}
			count = 0;
			initList.clear();
			this->students.push_back(Student((initArr)));
		}
	}
	if (students.size() == 0) {
		cout << "Неверный пароль" << endl;
		exit(0);
	}
	bool fl = in.is_open();
	in.close();
	return fl;
}

bool Database::saveDb()
{
	std::ofstream out;
	out.open(DbPath, std::ios::out|std::ios::binary);
	MyList <char> allStud;
	if (out.is_open())
	{
		for (int i=0; i<students.size();i++){
			MyList<char> buff = students[i].toCharVec();
			for (int j = 0; j < buff.size(); j++) {
				allStud.push_back(buff[j]);
			}
		}
	}
	char* encrText = new char[allStud.size()+1];
	int y = 0;
	for (int i = 0; i < allStud.size(); i++) {
		encrText[i] = allStud[i];
		y = i;
	}
	encrText[y+1] = '\0';
	crypt.Crypt(encrText, allStud.size());

	for (int i = 0; i < allStud.size();i++) {
		out << noskipws << encrText[i];
	}

	delete[] encrText;
	bool fl = out.is_open();
	out.close();
	auto x = 9;
	return fl;
}

bool Database::addFilter(char filtersStr[64], MyList <Student>& filtred)
{
	static const regex r(R"(^[\d\,]*\d$)");
	vector <Student> temp;
	for (int i = 0; i < students.size(); i++) {
		Student t{ students[i] };
		temp.push_back(t);
	}
	if (regex_match(filtersStr, r)) {
		int i = 0;
		vector <int> sesNumbers;
		while (filtersStr[i] != '\0') {
			char sesNum[4];
			int j = 0;
			while (i<4 && filtersStr[i] != '\0' && filtersStr[i] != ',') {
				sesNum[j] = filtersStr[i];
				i++;
				j++;
			}
			if (i == 4) {
				return false;
			}
			j++;
			sesNum[j] = '\0';
			sesNumbers.push_back(atoi(sesNum));
			if (filtersStr[i] == '\0') {
				break;
			}
			i++;
			
			}
		std::set<int> setSesNumbers(sesNumbers.begin(), sesNumbers.end());
		vector <int> ses5;
		for (int i=0; i < students.size(); i++) {
			ses5.push_back(countSes5(students[i], setSesNumbers));
		}
		while (temp.empty() == false) {
			int maxInd=0;
			for (int i = 0; i < temp.size(); i++) {
				if (ses5[i] > ses5[maxInd]) {
					maxInd = i;
				}
			}
			filtred.push_back(temp[maxInd]);
			temp.erase(temp.begin() + maxInd);
			ses5.erase(ses5.begin() + maxInd);
		}
		return true;
	}
	return false;
}

