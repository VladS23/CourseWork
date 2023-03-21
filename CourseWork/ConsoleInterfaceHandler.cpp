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
	cTools.Clear();
	cout << "Выберите опцию"<<endl;
	cout << "1. Создать новую базу данных"<<endl;
	cout << "2. Использовать существующую базу данных" << endl;
	char options;
	cin >> options;
	while (fgetc(stdin) != '\n');
	Database mainDB;
	switch (options)
	{
		case '1':
			cTools.Clear();
			cout << "База данных была создана в корне диска D"<<endl;
			Sleep(1000);
			MainPage(mainDB);
			break;
		case '2':
			char path[256];
			cout << "Введите путь до базы данных"<<endl;
			cin >> setw(256) >> path;
			while (fgetc(stdin) != '\n');
			if (mainDB.loadDb(path)) {
				cTools.Clear();
				cout << "База данных успешно загружена"<<endl;
				Sleep(1000);
				MainPage(mainDB);

			}
			else {
				cTools.Clear();
				cout << "Ошибка загрузки БД"<<endl;
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
	cout << "Для просмотра или изменения записи введите ее номер, чтобы добавить запись введите 0, для применения фильтров введите f, для сохранения базы данных введите s"<<endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << "|Студенты" << setw(111) << "|"<<endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Students);
	cout << '|' << std::left << setw(5) << "ID" << '|' << setw(70)  << "ФИО" << '|'<< "Дата рождения" << '|' << setw(27) << "Пол" << '|' << endl;
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
			cout << "Некорректный номер" << endl;
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
		cout << "Некорректный номер" << endl;
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
	cout << "Данные студента:" << endl<<endl;
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

		cout << std::left << "|" << setw(4) << "9" << "|" << "Обнаружены сессии под номерами : ";
		for (int i = 0; i < db.students[ind].getSessionsSize() - 1; i++) {
			cout << std::left << db.students[ind].getSessionByIndex(1).numSesion << ", ";
		}
		cout << std::left << setw(115 - 34 - db.students[ind].getSessionsSize() - (db.students[ind].getSessionsSize() - 1) * 2) << db.students[ind].getSessionByIndex(db.students[ind].getSessionsSize() - 1).numSesion << '|' << endl;
	}
	else {
		cout << std::left << "|" << setw(4) << "9" << "|" << setw(113) << "Сессии не найдены" << '|' << endl;
	}
	delete[] name;
	delete[] gender;
	delete[] dateOfBorn;
	delete[] faculty;
	delete[] departments;
	delete[] group;
	delete[] numGradebook;
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << "Для изменения поля или получения более подробной информации о нем введите его номер, чтобы вернуться назад 0" << endl;
	char options;
	cin >> options;
	while (fgetc(stdin) != '\n');
	if (options == '0') {
		MainPage(db);
	}
	else if (options=='9') {
		//TODO
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
	vector <char> InitVector;
	InitVector.push_back(';');
	cTools.Clear();
	cout << "Создать студента" << endl << endl;
	bool fl = false;
	cout << "Введите ФИО" << endl;
	cin.get(name, 64);
	while (fgetc(stdin) != '\n');
	name[63] = '\0';
	for (int i = 0; i < strlen(name); i++) {
		InitVector.push_back(name[i]);
	}
	InitVector.push_back(':');
	cout << "Введите дату рождения через точку" << endl;
	cin.get(dateOfBorn, 16);
	dateOfBorn[15] = '\0';
	while (fgetc(stdin) != '\n');
	regex reg (R"(^[0-9]{1,2}\.[0-9]{1,2}\.[0-9]{1,4}$)");
	fl = false;
	if (regex_match(dateOfBorn, reg)) {
		fl =true;
	}
	while (!fl) {
		cout << "Неверный формат даты" << endl;
		cout << "Введите дату рождения через точку" << endl;
		cin.get(dateOfBorn, 16);
		dateOfBorn[15] = '\0';
		while (fgetc(stdin) != '\n');
		if (regex_match(dateOfBorn, reg)) {
			fl = true;
		}
	}
	for (int i = 0; i < strlen(dateOfBorn); i++) {
		InitVector.push_back(dateOfBorn[i]);
	}
	InitVector.push_back(':');
	cout << "Введите год поступления"<<endl;
	fl = false;
	cin.get(yearOfAdmission, 8);
	yearOfAdmission[7] = '\0';
	while (fgetc(stdin) != '\n');
	regex r(R"(^[0-9]{0,4}$)");
	if (regex_match(yearOfAdmission, r)) { 
		fl = true; 
	}
	while (!fl) {
		cout << "Введите год поступления" << endl;
		cin.get(yearOfAdmission, 8);
		yearOfAdmission[7] = '\0';
		while (fgetc(stdin) != '\n');
		regex r(R"(^[0-9]{0,4}$)");
		if (regex_match(yearOfAdmission, r)) {
			fl = true;
		}
	}
	for (int i = 0; i < strlen(yearOfAdmission); i++) {
		InitVector.push_back(yearOfAdmission[i]);
	}
	InitVector.push_back(':');
	cout << "Введите факультет" << endl;
	cin.get(faculty, 64);
	faculty[63] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(faculty); i++) {
		InitVector.push_back(faculty[i]);
	}
	InitVector.push_back(':');
	cout << "Введите кафедру" << endl;
	cin.get(departments, 64);
	departments[63] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(departments); i++) {
		InitVector.push_back(departments[i]);
	}
	InitVector.push_back(':');
	cout << "Введите группу" << endl;
	cin.get(group, 16);
	group[15] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(group); i++) {
		InitVector.push_back(group[i]);
	}
	InitVector.push_back(':');
	cout << "Введите номер студенческого билета" << endl;
	cin.get(numGradebook, 16);
	numGradebook[15] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(numGradebook); i++) {
		InitVector.push_back(numGradebook[i]);
	}
	InitVector.push_back(':');
	cout << "Введите пол" << endl;
	cin.get(gender, 32);
	gender[31] = '\0';
	while (fgetc(stdin) != '\n');
	for (int i = 0; i < strlen(gender); i++) {
		InitVector.push_back(gender[i]);
	}
	InitVector.push_back(';');
	char* initChars = new char[InitVector.size()+10];
	for (int i = 0; i < InitVector.size(); i++) {
		initChars[i] = InitVector[i];
	}
	db.students.push_back(Student(initChars));
	cTools.Clear();
	cout << "Студент успешно добавлен";
	Sleep(1000);
	MainPage(db);
}

void ConsoleInterfaceHandler::FiltredStud(Database db)
{
	bool fl = false;
	char filter[64];
	vector <Student> filtred;
	cTools.Clear();
	cout << "Введите номера сессии, по которым необходимо фильтровать через запятую, без пробелов" << endl;
	cin >>setw(64) >> filter;
	while (fgetc(stdin) != '\n');
	fl = db.addFilter(filter, filtred);
	while(!fl) {
		cTools.Clear();
		cout << "Неверные номера сессий"<<endl;
		cout << "Введите номера сессии, по которым необходимо фильтровать через запятую, без пробелов" << endl;
		cin >> setw(64) >> filter;
		while (fgetc(stdin) != '\n');
		fl = db.addFilter(filter, filtred);
	}
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << '|' << std::left << setw(5) << "ID" << '|' << setw(70) << "ФИО" << '|' << "Дата рождения" << '|' << setw(27) << "Пол" << '|' << endl;
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
	cout << "Нажмите 0 чтобы вернуться в главное меню" << endl;
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
		cout << "База данных сохранена по адресу D:/students.txt";
		Sleep(1000);
		MainPage(db);
	}
	else {
		cout << "Ошибка сохранения базы данных";
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
		cout <<"Введите новое имя, для выхода введите 0"<<endl;
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
		cout << "Введите дату рождения через точку" << endl;
		cin.get(dateOfBornc, 16);
		dateOfBornc[15] = '\0';
		while (fgetc(stdin) != '\n');
		if (regex_match(dateOfBornc, reg)) {
			fl = true;
		}
		while (!fl) {
			cout << "Неверный формат даты" << endl;
			cout << "Введите дату рождения через точку" << endl;
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
		cout << "Введите пол" << endl;
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
		cout << "Введите год поступления" << endl;
		fl = false;
		cin.get(yearOfAdmission, 8);
		yearOfAdmission[7] = '\0';
		while (fgetc(stdin) != '\n');
		if (regex_match(yearOfAdmission, r)) {
			fl = true;
		}
		while (!fl) {
			cout << "Введите год поступления" << endl;
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
		cout << '|' << setw(118) << faculty << '|';
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << endl << endl << "Введите факультет" << endl;
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
		cout << '|' << setw(118) << departments << '|';
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << endl << endl << "Введите кафедру" << endl;
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
		cout << '|' << setw(118) << group << '|';
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << endl << endl << "Введите группу" << endl;
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
		cout << '|' << setw(118) << numGrade << '|';
		cTools.PrintSeparator(ConsoleTools::Simple);
		cout << endl << endl << "Введите номер зачетки" << endl;
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
