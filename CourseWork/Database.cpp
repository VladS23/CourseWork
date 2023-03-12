#include "Database.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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
	std::ifstream in(dbPath); // окрываем файл для чтения
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

void Database::addStudent(Student newStudent)
{
	students.push_back(newStudent);
}
