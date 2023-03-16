#include "ConsoleInterfaceHandler.h"
#include <iostream>
#include "Database.h"
#include <iomanip>
#include <regex>
using namespace std;

ConsoleInterfaceHandler::ConsoleInterfaceHandler()
{
	StartPage();
}

void ConsoleInterfaceHandler::StartPage()
{
	Clear();
	cout << "�������� �����"<<endl;
	cout << "1. ������� ����� ���� ������"<<endl;
	cout << "2. ������������ ������������ ���� ������" << endl;
	char options;
	cin >> options;
	Database mainDB;
	switch (options)
	{
		case '1':
			cout << "���� ������ ���� ������� � ����� ����� D"<<endl;
			MainPage(mainDB);
			break;
		case '2':
			char path[256];
			cout << "������� ���� �� ���� ������"<<endl;
			cin >> path;
			if (mainDB.loadDb(path)) {
				cout << "���� ������ ������� ���������"<<endl;
				MainPage(mainDB);

			}
			else {
				cout << "������ �������� ��"<<endl;
				StartPage();
			}
			break;
	default:
		break;
	}
}

void ConsoleInterfaceHandler::MainPage(Database db)
{
	Clear();
	cout << "��� ��������� ��� ��������� ������ ������� �� �����, ����� �������� ������ ������� 0"<<endl;
	cout << "|----------------------------------------------------------------------------------------------------------------------|"<<endl;
	cout << "|��������" << setw(111) << "|"<<endl;
	cout << "|-----|----------------------------------------------------------------------|-------------|---------------------------|" << endl;
	cout << '|' << std::left << setw(5) << "ID" << '|' << setw(70)  << "���" << '|'<< "���� ��������" << '|' << setw(27) << "���" << '|' << endl;
	cout << "|-----|----------------------------------------------------------------------|-------------|---------------------------|" << endl;
	for (int i = 0; i < db.students.size(); i++) {
		cout << '|' <<std::left<< setw(5) << i+1 << '|' << setw(70) << db.students[i].getName() << '|' << setw(13) << db.students[i].getDateOfBorn().toCharArray() << '|' << setw(27) << db.students[i].getGender() << '|' << endl;
		cout << "|-----|----------------------------------------------------------------------|-------------|---------------------------|" << endl;
	}
	char options[6];
	cin >> options;
	static const regex r(R"(^[1-9]{0,6}$)");
	if (regex_match(options, r)) {
		int ind = atoi(options)-1;
		if (ind >= 0 && ind < db.students.size()) {
			StudentPage(db.students[ind], db);
		}
		else {
			cout << "������������ �����" << endl;
			MainPage(db);
		}
	}
	else {
		cout << "������������ �����" << endl;
		MainPage(db);
	}
}
void ConsoleInterfaceHandler::Clear()
{
	std::cout << "\x1B[2J\x1B[H";
}

void ConsoleInterfaceHandler::StudentPage(Student stud,Database db)
{
}
