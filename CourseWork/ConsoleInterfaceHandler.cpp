#include "ConsoleInterfaceHandler.h"
#include <iostream>
#include "Database.h"
#include <iomanip>
#include <regex>
#include "MyList.h"
using namespace std;

ConsoleInterfaceHandler::ConsoleInterfaceHandler()
{
	StartPage();
}

void ConsoleInterfaceHandler::StartPage()
{
	cTools.Clear();
	cout << "�������� �����"<<endl;
	cout << "1. ������� ����� ���� ������"<<endl;
	cout << "2. ������������ ������������ ���� ������" << endl;
	char options;
	cin >> options;
	while (fgetc(stdin) != '\n');
	Database mainDB;
	switch (options)
	{
		case '1':
			cTools.Clear();
			cout << "���� ������ ���� ������� � ����� ����� D"<<endl;
			Sleep(1000);
			MainPage(mainDB);
			break;
		case '2':
			char path[256];
			cout << "������� ���� �� ���� ������"<<endl;
			cin >> setw(256) >> path;
			while (fgetc(stdin) != '\n');
			if (mainDB.loadDb(path)) {
				cTools.Clear();
				cout << "���� ������ ������� ���������"<<endl;
				Sleep(1000);
				MainPage(mainDB);

			}
			else {
				cTools.Clear();
				cout << "������ �������� ��"<<endl;
				Sleep(1000);
				StartPage();
			}
			break;
	default:
		break;
	}
}

void ConsoleInterfaceHandler::MainPage(Database db)
{
	cTools.Clear();
	cout << "��� ��������� ��� ��������� ������ ������� �� �����, ����� �������� ������ ������� 0, ��� ���������� �������� ������� f, ��� ���������� ���� ������ ������� s"<<endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << "|��������" << setw(111) << "|"<<endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Students);
	cout << '|' << std::left << setw(5) << "ID" << '|' << setw(70)  << "���" << '|'<< "���� ��������" << '|' << setw(27) << "���" << '|' << endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Students);	
	for (int i = 0; i < db.students.size(); i++) {
		char* name = db.students[i].getName();
		char* gender = db.students[i].getGender();
		char* dateOfBorn = db.students[i].getDateOfBorn().toCharArray();
		cout << '|' <<std::left<< setw(5) << i+1 << '|' << setw(70) << name << '|' << setw(13) << dateOfBorn << '|' << setw(27) << gender << '|' << endl;
		cTools.PrintSeparator(ConsoleTools::Separators::Students);
		delete[] name;
		delete[] gender;
		delete[] dateOfBorn;
	}
	char options[7];
	cin.get(options, 7);
	while (fgetc(stdin) != '\n');
	static const regex r(R"(^[0-9]{0,6}$)");
	if (regex_match(options, r)) {
		int ind = atoi(options)-1;
		if (ind >= 0 && ind < db.students.size()) {
			StudentPage(ind, db);
		}
		else if(ind==-1) {
			CreateStudentPage(db);
		}
		else {
			cout << "������������ �����" << endl;
			Sleep(1000);
			MainPage(db);
			cTools.Clear();
		}
	}
	else if (options[0]=='f') {
		FiltredStud(db);
	}
	else if(options[0] == 's'){
		SavePage(db);
	}
	else {
		cTools.Clear();
		cout << "������������ �����" << endl;
		Sleep(1000);
		MainPage(db);
	}
}

void ConsoleInterfaceHandler::StudentPage(int ind ,Database db)
{
	cTools.Clear();
	int yearOfAdmission = db.students[ind].getYearOfAdmission();
	char* name = db.students[ind].getName();
	char* gender = db.students[ind].getGender();
	char* dateOfBorn = db.students[ind].getDateOfBorn().toCharArray();
	char* faculty= db.students[ind].getFaculty();
	char* departments= db.students[ind].getDepartments();
	char* group= db.students[ind].getGroup();
	char* numGradebook= db.students[ind].getNumGradebook();
	cout << "������ ��������:" << endl<<endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << '|' << std::left << setw(4)<<"1" << '|' << setw(65) << name << "|" << setw(4)<< "5" << '|' << setw(42) << faculty << '|' << endl;
	cTools.PrintSeparator(ConsoleTools::Separators::PersonalCard);
	cout << '|' << std::left << setw(4) << "2" << '|' << setw(65) << dateOfBorn << "|" << setw(4) << "6" << '|' << setw(42) << departments << '|' << endl;
	cTools.PrintSeparator(ConsoleTools::Separators::PersonalCard);
	cout << '|' << std::left << setw(4) << "3" << '|' << setw(65) << gender << "|" << setw(4) << "7" << '|' << setw(42) << group << '|' << endl;
	cTools.PrintSeparator(ConsoleTools::Separators::PersonalCard);
	cout << '|' << std::left << setw(4) << "4" << '|' << setw(65) << yearOfAdmission << "|" << setw(4) << "8" << '|' << setw(42) << numGradebook << '|' << endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	if (db.students[ind].getSessionsSize() > 0) {

		cout << std::left << "|" << setw(4) << "9" << "|" <<setw(112) << "����������� ������ " << '|'<<endl;
	}
	else {
		cout << std::left << "|" << setw(4) << "9" << "|" << setw(113) << "������ �� �������" << '|' << endl;
	}
	delete[] name;
	delete[] gender;
	delete[] dateOfBorn;
	delete[] faculty;
	delete[] departments;
	delete[] group;
	delete[] numGradebook;
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << "��� ��������� ���� ��� ��������� ����� ��������� ���������� � ��� ������� ��� �����, ����� ��������� ����� 0,"<<endl<<"����� ������� - " << endl;
	char options;
	cin >> options;
	while (fgetc(stdin) != '\n');
	if (options == '0') {
		MainPage(db);
	}
	else if (options=='9') {
		SessionsPage(db, ind);
	}
	else if (options == '-') {
		db.students.removeAt(ind);
	}
	else {
		UpdateStudPage((UpdatePage)atoi(&options), ind, db);
	}
	MainPage(db);
}

void ConsoleInterfaceHandler::CreateStudentPage(Database db)
{
	char yearOfAdmission[8];
	char faculty[64];
	char departments[64];
	char group[16];
	char numGradebook[16];
	char name[64];
	char dateOfBorn[16];
	char gender[32];
	MyList <char> InitList;
	InitList.push_back(';');
	cTools.Clear();
	cout << "������� ��������" << endl << endl;
	bool fl = false;
	cout << "������� ���" << endl;
	cin.get(name, 64);
	while (fgetc(stdin) != '\n');
	name[63] = '\0';
	for (int i = 0; i < strlen(name); i++) {
		InitList.push_back(name[i]);
	}
	InitList.push_back(':');
	cout << "������� ���� �������� ����� �����" << endl;
	cin.get(dateOfBorn, 16);
	dateOfBorn[15] = '\0';
	while (fgetc(stdin) != '\n');
	regex reg (R"(^[0-9]{1,2}\.[0-9]{1,2}\.[0-9]{1,4}$)");
	fl = false;
	if (regex_match(dateOfBorn, reg)) {
		fl =true;
	}
	while (!fl) {
		cout << "�������� ������ ����" << endl;
		cout << "������� ���� �������� ����� �����" << endl;
		cin.get(dateOfBorn, 16);
		dateOfBorn[15] = '\0';
		while (fgetc(stdin) != '\n');
		if (regex_match(dateOfBorn, reg)) {
			fl = true;
		}
	}
	for (int i = 0; i < strlen(dateOfBorn); i++) {
		InitList.push_back(dateOfBorn[i]);
	}
	InitList.push_back(':');
	cout << "������� ��� �����������"<<endl;
	fl = false;
	cin.get(yearOfAdmission, 8);
	yearOfAdmission[7] = '\0';
	while (fgetc(stdin) != '\n');
	regex r(R"(^[0-9]{0,4}$)");
	if (regex_match(yearOfAdmission, r)) { 
		fl = true; 
	}
	while (!fl) {
		cout << "������� ��� �����������" << endl;
		cin.get(yearOfAdmission, 8);
		yearOfAdmission[7] = '\0';
		while (fgetc(stdin) != '\n');
		regex r(R"(^[0-9]{0,4}$)");
		if (regex_match(yearOfAdmission, r)) {
			fl = true;
		}
	}
	for (int i = 0; i < strlen(yearOfAdmission); i++) {
		InitList.push_back(yearOfAdmission[i]);
	}
	InitList.push_back(':');
	cout << "������� ���������" << endl;
	cin.get(faculty, 64);
	faculty[63] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(faculty); i++) {
		InitList.push_back(faculty[i]);
	}
	InitList.push_back(':');
	cout << "������� �������" << endl;
	cin.get(departments, 64);
	departments[63] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(departments); i++) {
		InitList.push_back(departments[i]);
	}
	InitList.push_back(':');
	cout << "������� ������" << endl;
	cin.get(group, 16);
	group[15] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(group); i++) {
		InitList.push_back(group[i]);
	}
	InitList.push_back(':');
	cout << "������� ����� ������������� ������" << endl;
	cin.get(numGradebook, 16);
	numGradebook[15] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(numGradebook); i++) {
		InitList.push_back(numGradebook[i]);
	}
	InitList.push_back(':');
	cout << "������� ���" << endl;
	cin.get(gender, 32);
	gender[31] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(gender); i++) {
		InitList.push_back(gender[i]);
	}
	InitList.push_back(';');
	char* initChars = new char[InitList.size()+10];
	for (int i = 0; i < InitList.size(); i++) {
		initChars[i] = InitList[i];
	}
	db.students.push_back(Student(initChars));
	cTools.Clear();
	cout << "������� ������� ��������";
	Sleep(1000);
	MainPage(db);
}

void ConsoleInterfaceHandler::FiltredStud(Database db)
{
	bool fl = false;
	char filter[64];
	MyList <Student> filtred;
	cTools.Clear();
	cout << "������� ������ ������, �� ������� ���������� ����������� ����� �������, ��� ��������" << endl;
	cin >>setw(64) >> filter;
	while (fgetc(stdin) != '\n');
	fl = db.addFilter(filter, filtred);
	while(!fl) {
		cTools.Clear();
		cout << "�������� ������ ������"<<endl;
		cout << "������� ������ ������, �� ������� ���������� ����������� ����� �������, ��� ��������" << endl;
		cin >> setw(64) >> filter;
		while (fgetc(stdin) != '\n');
		fl = db.addFilter(filter, filtred);
	}
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << '|' << std::left << setw(5) << "ID" << '|' << setw(70) << "���" << '|' << "���� ��������" << '|' << setw(27) << "���" << '|' << endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Students);
	for (int i = 0; i < filtred.size(); i++) {
		char* name = filtred[i].getName();
		char* gender = filtred[i].getGender();
		char* dateOfBorn = filtred[i].getDateOfBorn().toCharArray();
		cout << '|' << std::left << setw(5) << i + 1 << '|' << setw(70) << name << '|' << setw(13) << dateOfBorn << '|' << setw(27) << gender << '|' << endl;
		cTools.PrintSeparator(ConsoleTools::Separators::Students);
		delete[] name;
		delete[] gender;
		delete[] dateOfBorn;
	}
	cout << "������� 0 ����� ��������� � ������� ����" << endl;
	char c;
	cin >> c;
	while (fgetc(stdin) != '\n');
	while (c != '0') {
		cin >> c;
		while (fgetc(stdin) != '\n');
	}
	MainPage(db);
}

void ConsoleInterfaceHandler::SavePage(Database db)
{
	cTools.Clear();
	if (db.saveDb()) {
		cout << "���� ������ ��������� �� ������ D:/students.txt";
		Sleep(1000);
		MainPage(db);
	}
	else {
		cout << "������ ���������� ���� ������";
		Sleep(1000);
		MainPage(db);
	}
}

void ConsoleInterfaceHandler::UpdateStudPage(UpdatePage options, int ind, Database db)
{
	char* name;
	Date dateOfBornd;
	char* dateOfBornc;
	char* faculty;
	char* departments;
	char* group;
	char* numGrade;
	char* gender;
	char yearOfAdmission[8]="0";
	bool fl = false;
	regex reg(R"(^[0-9]{1,2}\.[0-9]{1,2}\.[0-9]{1,4}$)");
	regex r(R"(^[0-9]{0,4}$)");
	int date[3];
	int curDateEl = 0;
	int i = 0;
	int j = 0;
	cTools.Clear();
	switch (options)
	{
	case ConsoleInterfaceHandler::Name:
		name = db.students[ind].getName();
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << '|' << setw(118) << name << '|'<<endl;
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout <<"������� ����� ���, ��� ������ ������� 0"<<endl;
		cin.get(name, 64);
		while (fgetc(stdin) != '\n');
		if (name[0] != '0') {
			name[63] = '\0';
			bool b = db.students[ind].setName(name);
		}
		delete[] name;
		MainPage(db);
		break;
	case ConsoleInterfaceHandler::DateOfBorn:
		dateOfBornd = db.students[ind].getDateOfBorn();
		cTools.PrintSeparator(ConsoleTools::Simple);
		dateOfBornc = dateOfBornd.toCharArray();
		cout << '|' << setw(118) << dateOfBornc << '|';
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << "������� ���� �������� ����� �����" << endl;
		cin.get(dateOfBornc, 16);
		dateOfBornc[15] = '\0';
		while (fgetc(stdin) != '\n');
		if (regex_match(dateOfBornc, reg)) {
			fl = true;
		}
		while (!fl) {
			cout << "�������� ������ ����" << endl;
			cout << "������� ���� �������� ����� �����" << endl;
			cin.get(dateOfBornc, 16);
			dateOfBornc[15] = '\0';
			while (fgetc(stdin) != '\n');
			if (regex_match(dateOfBornc, reg)) {
				fl = true;
			}
		}
		i = 0;
		while (dateOfBornc[i] != '\0')
		{
			char curInt[8]={'0'};
			j = 0;
			while (dateOfBornc[i] != '.' && dateOfBornc[i] != '\0') {
				curInt[j] = dateOfBornc[i];
				i++;
				j++;
			}
			i++;
			date[curDateEl] = atoi(curInt);
			curDateEl++;
			if (dateOfBornc[i - 1] == '\0') {
				break;
			}
		}
		dateOfBornd.day = date[0];
		dateOfBornd.month = date[1];
		dateOfBornd.year = date[2];
		db.students[ind].setDateOfBorn(dateOfBornd);
		delete[] dateOfBornc;
		MainPage(db);
		break;
	case ConsoleInterfaceHandler::Gender:
		gender = db.students[ind].getGender();
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << '|' << setw(118) << gender << '|'<<endl;
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << "������� ���" << endl;
		cin.get(gender, 32);
		gender[31] = '\0';
		while (fgetc(stdin) != '\n');
		db.students[ind].setGender(gender);
		delete[] gender;
		MainPage(db);
		break;
	case ConsoleInterfaceHandler::YearOfAdmissions:
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << '|' << setw(118) << db.students[i].getYearOfAdmission() << '|';
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << "������� ��� �����������" << endl;
		fl = false;
		cin.get(yearOfAdmission, 8);
		yearOfAdmission[7] = '\0';
		while (fgetc(stdin) != '\n');
		if (regex_match(yearOfAdmission, r)) {
			fl = true;
		}
		while (!fl) {
			cout << "������� ��� �����������" << endl;
			cin.get(yearOfAdmission, 8);
			yearOfAdmission[7] = '\0';
			while (fgetc(stdin) != '\n');
			if (regex_match(yearOfAdmission, r)) {
				fl = true;
			}
			delete[] yearOfAdmission;
		}
		db.students[i].setYearOfAdmission(atoi(yearOfAdmission));
		MainPage(db);
		break;
	case ConsoleInterfaceHandler::Faculty:
		faculty = db.students[ind].getFaculty();
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << '|' << setw(118) << faculty << '|' << endl;
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << "������� ���������" << endl;
		cin.get(faculty, 64);
		faculty[63] = '\0';
		while (fgetc(stdin) != '\n');
		db.students[ind].setFaculty(faculty);
		delete[] faculty;
		MainPage(db);
		break;
	case ConsoleInterfaceHandler::Departsment:
		departments = db.students[ind].getDepartments();
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << '|' << setw(118) << departments << '|' << endl;
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << "������� �������" << endl;
		cin.get(departments, 64);
		departments[63] = '\0';
		while (fgetc(stdin) != '\n');
		db.students[ind].setDepartments(departments);
		delete[] departments;
		MainPage(db);
		break;
	case ConsoleInterfaceHandler::Group:
		group = db.students[ind].getGroup();
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << '|' << setw(118) << group << '|' << endl;
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << "������� ������" << endl;
		cin.get(group, 16);
		group[15] = '\0';
		while (fgetc(stdin) != '\n');
		db.students[ind].setGroup(group);
		delete[] group;
		MainPage(db);
		break;
	case ConsoleInterfaceHandler::numOfGradebook:
		numGrade = db.students[ind].getNumGradebook();
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << '|' << setw(118) << numGrade << '|'<<endl;
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << "������� ����� �������" << endl;
		cin.get(numGrade, 16);
		numGrade[15] = '\0';
		while (fgetc(stdin) != '\n');
		db.students[ind].setNumGradebook(numGrade);
		delete[] numGrade;
		MainPage(db);
		break;
	default:
		MainPage(db);
		break;
	}
}

void ConsoleInterfaceHandler::SessionsPage(Database db, int ind)
{
	cTools.Clear();
	int options;
	char prevoptions[8];
	cout << "������� ������ ������, ����� ����������� ��� �������� �� ����������," << endl << "0 ����� �������� �����, - ����� ������� ���� �� ������������, q ����� �����" << endl;
	cout << "������" << endl;
	cTools.PrintSeparator(cTools.Simple);
	for (int i = 0; i < db.students[ind].getSessionsSize(); i++) {
		cout << '|' << setw(3) << i+1 << "������ � " << setw(106) << db.students[ind].getSessionByIndex(i).numSesion << "|" << endl;
		cTools.PrintSeparator(cTools.Simple);
	}
	cin.get(prevoptions, 8);
	prevoptions[7] = '\0';
	while (fgetc(stdin) != '\n');
	regex r(R"(^[0-9]{0,2}$)");
	bool fl = false;
	if (regex_match(prevoptions, r)) {
		fl = true;
	}
	else if ((prevoptions[0] == '-' and prevoptions[1] == '\0') || (prevoptions[0] == 'q' and prevoptions[1] == '\0')) {
		fl = true;
	}
	while (not fl) {
		cout << "�������� ������ ������" << endl;
		cin.get(prevoptions, 8);
		prevoptions[7] = '\0';
		while (fgetc(stdin) != '\n');
		regex r(R"(^[0-9]{0,2}$)");
		fl = false;
		if (regex_match(prevoptions, r)) {
			fl = true;
		}
		else if ((prevoptions[0] == '-' and prevoptions[1] == '\0') || (prevoptions[0] == 'q' and prevoptions[1] == '\0')) {
			fl = true;
		}
	}
	if (!((prevoptions[0] == '-' and prevoptions[1] == '\0') || (prevoptions[0] == 'q' and prevoptions[1] == '\0')))
	{
		options = atoi(prevoptions);
		if (options == 0) {
			AddSessionPage(db, ind);
		}
		else {
			SessionPage(db, ind, options-1);
		}
	}
	else if ((prevoptions[0] == '-' and prevoptions[1] == '\0')) {
		DeleteSessionPage(db, ind);
	}
	else {
		StudentPage(ind, db);
	}
}

void ConsoleInterfaceHandler::AddSessionPage(Database db, int ind)
{
	cTools.Clear();
	cout << "������� ����� ������ ��� ����������" << endl;
	char prevoptions [8];
	int options;
	cin.get(prevoptions, 8);
	prevoptions[7] = '\0';
	while (fgetc(stdin) != '\n');
	regex r(R"(^[0-9]{0,2}$)");
	bool fl = false;
	if (regex_match(prevoptions, r)) {
		fl = true;
	}
	while (not fl) {
		cout << "�������� ������ ������" << endl;
		cin.get(prevoptions, 8);
		prevoptions[7] = '\0';
		while (fgetc(stdin) != '\n');
		regex r(R"(^[0-9]{0,2}$)");
		fl = false;
		if (regex_match(prevoptions, r)) {
			fl = true;
		}
	}
	options = atoi(prevoptions);
	bool success = db.students[ind].addSessionByNum(options);
	cTools.Clear();
	if (success) {
		cout << "������ �������� �������" << endl;
	}
	else {
		cout << "������ ��� ����������" << endl;
	}
	Sleep(1000);
	SessionsPage(db, ind);
}

void ConsoleInterfaceHandler::SessionPage(Database db, int ind, int sesInd)
{
	cTools.Clear();
	if (sesInd < db.students[ind].getSessionsSize()) {
		cout << "����� �������� ��� ������� ��������� ������� ��� �����, ����� �������� ����� ��������� ������� 0, ����� ����� q" << endl;
		cout << "���������� ���������:" << endl;
		cTools.PrintSeparator(cTools.Simple);
		cout << '|' << setw(3) << "�" << '|' << setw(75) << "�������� ��������" << "|" << setw(38) << "������" << "|" << endl;
		cTools.PrintSeparator(cTools.Simple);
		for (int i = 0; i < db.students[ind].getSessionByIndex(sesInd).oneRes.size(); i++) {
			cout << '|' << setw(3) << i + 1 << '|' << setw(75) << db.students[ind].getSessionByIndex(sesInd).oneRes[i].subName << "|" << setw(38) << db.students[ind].getSessionByIndex(sesInd).oneRes[i].grading << "|" << endl;
			cTools.PrintSeparator(cTools.Simple);
		}
		char prevoptions[8];
		int options;
		cin.get(prevoptions, 8);
		prevoptions[7] = '\0';
		while (fgetc(stdin) != '\n');
		regex r(R"(^[0-9]{0,2}$)");
		bool fl = false;
		if (regex_match(prevoptions, r)) {
			fl = true;
		}
		else if (prevoptions[0] == 'q' and prevoptions[1] == '\0') {
			fl = true;
		}
		while (not fl) {
			cout << "�������� ������ ������" << endl;
			cin.get(prevoptions, 8);
			prevoptions[7] = '\0';
			while (fgetc(stdin) != '\n');
			regex r(R"(^[0-9]{0,2}$)");
			fl = false;
			if (regex_match(prevoptions, r)) {
				fl = true;
			}
			else if (prevoptions[0] == 'q' and prevoptions[1] == '\0') {
				fl = true;
			}
		}
		if (!(prevoptions[0] == 'q' and prevoptions[1] == '\0'))
		{
			options = atoi(prevoptions);
			if (options == 0) {
				AddSesRes(db, ind, sesInd);
			}
			else {
				UpdateOrDeleteRes(db, ind, sesInd, options - 1);
			}
		}
		else {
			SessionsPage(db, ind);
		}
	}
	else {
		cout << "������, ���������� ������ � ������ �������" << endl;
		Sleep(500);
	}
	SessionsPage(db, ind);
}

void ConsoleInterfaceHandler::DeleteSessionPage(Database db, int ind)
{
	cTools.Clear();
	cout << "������� ����� ������ ��� ��������" << endl;
	char prevoptions[8];
	int options;
	cin.get(prevoptions, 8);
	prevoptions[7] = '\0';
	while (fgetc(stdin) != '\n');
	regex r(R"(^[0-9]{0,2}$)");
	bool fl = false;
	if (regex_match(prevoptions, r)) {
		fl = true;
	}
	while (not fl) {
		cout << "�������� ������ ������" << endl;
		cin.get(prevoptions, 8);
		prevoptions[7] = '\0';
		while (fgetc(stdin) != '\n');
		regex r(R"(^[0-9]{0,2}$)");
		fl = false;
		if (regex_match(prevoptions, r)) {
			fl = true;
		}
	}
	options = atoi(prevoptions);
	bool success = db.students[ind].deleteSessionByNum(options);
	cTools.Clear();
	if (success) {
		cout << "������ �������� �������" << endl;
	}
	else {
		cout << "������ �� ����������" << endl;
	}
	Sleep(1000);
	SessionsPage(db, ind);
}

void ConsoleInterfaceHandler::AddSesRes(Database db, int ind, int sesInd)
{
	cTools.Clear();
	char subName [64];
	int grad;
	cout << "������� �������� ��������"<<endl;
	cin.get(subName, 64);
	subName[63] = '\0';
	while (fgetc(stdin) != '\n');
	cout << "������� ������"<<endl;
	cin >> grad;
	while (fgetc(stdin) != '\n');
	Result res;
	for (int i = 0; i < 64; i++) {
		res.subName[i] = subName[i];
	}
	res.grading = grad;
	db.students[ind].addSesResult(res, db.students[ind].getSessionByIndex(sesInd).numSesion);
	cTools.Clear();
	cout << "��������� ������� ��������" << endl;
	Sleep(500);
	SessionPage(db, ind, sesInd);
}

void ConsoleInterfaceHandler::UpdateOrDeleteRes(Database db, int ind, int sesInd, int resInd)
{
	cTools.Clear();
	if (resInd < db.students[ind].getSessionByIndex(sesInd).oneRes.size()) {
		cout << "������� ����� ������ ��� �������� " << db.students[ind].getSessionByIndex(sesInd).oneRes[resInd].subName << ". ������� ������: " << db.students[ind].getSessionByIndex(sesInd).oneRes[resInd].grading << endl;
		cout << "��� �������� ������ ������� -1"<<endl;
		int options;
		cin >> options;
		while (fgetc(stdin) != '\n');
		if (options == -1) {
			db.students[ind].deleteSesResultByIndex(db.students[ind].getSessionByIndex(sesInd).numSesion, resInd);
		}
		else {
			Result res = db.students[ind].getSessionByIndex(sesInd).oneRes[resInd];
			res.grading = options;
			db.students[ind].updSesResultByIndex(res, db.students[ind].getSessionByIndex(sesInd).numSesion, resInd);
		}
	}
	else {
		cout << "������, ���������� ��������� � ������ �������" << endl;
		Sleep(500);
	}
	SessionPage(db, ind, sesInd);
}


