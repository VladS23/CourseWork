#include "Database.h"
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>

using namespace std;

int Database::countSes5(Student student, std::set<int> setSesNumbers)
{
	int fives = 0;
	int j = 0;
	vector <int> vecSesNum(setSesNumbers.begin(), setSesNumbers.end());
	for (int i = 0; i < vecSesNum.size(); i++) {
		if (j < student.getSessionsSize() &&  vecSesNum[i] < student.getSessionByIndex(j).numSesion) {
		}
		else if (j < student.getSessionsSize() &&  vecSesNum[i] > student.getSessionByIndex(j).numSesion) {
			j++;
			i--;
		}
		else if (j < student.getSessionsSize() &&  vecSesNum[i] == student.getSessionByIndex(j).numSesion) {
			for (int k = 0; k < student.getSessionByIndex(j).oneRes.size(); k++) {
				if (student.getSessionByIndex(j).oneRes[k].grading == 5) {
					fives++;
				}
			}
			j++;
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
	std::string line;
	std::ifstream in(dbPath);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			char* chars = new char[line.length()];
			const char* lc = line.c_str();
			for (int i = 0; i < line.length(); i++) {
				chars[i] = lc[i];
			}
			students.push_back(Student(chars));
		}
	}
	bool fl = in.is_open();
	in.close();
	return fl;
}

bool Database::saveDb()
{
	std::ofstream out;
	out.open(DbPath, std::ios_base::out);
	if (out.is_open())
	{
		for (int i=0; i<students.size();i++){
			vector<char> buff = students[i].toCharVec();
			char* buffer = new char[buff.size()+1];
			int j=0;
			while (buff[j]!=';') {
				buffer[j] = buff[j];
				j++;
			}
			buffer[j] = ';';
			buffer[j+1] = '\0';
			out << buffer<<endl;
			delete[] buffer;
		}
	}
	bool fl = out.is_open();
	out.close();
	return fl;
}

bool Database::addFilter(char filtersStr[64], vector <Student>& filtred)
{
	static const regex r(R"(^[\d\,]*\d$)");
	vector <Student> temp(students.begin(), students.end());
	if (regex_match(filtersStr, r)) {
		int i = 0;
		vector <int> sesNumbers;
		while (filtersStr[i] != '\0') {
			char sesNum[4];
			int j = 0;
			while (filtersStr[i] != '\0' && filtersStr[i] != ',') {
				sesNum[j] = filtersStr[i];
				i++;
				j++;
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
		auto debudStop = 8;
		return true;
	}
	return false;
}

