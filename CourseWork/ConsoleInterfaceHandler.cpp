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
	cin >> setw(7) >> options;
	while (fgetc(stdin) != '\n');
	static const regex r(R"(^[0-9]{0,6}$)");
	if (regex_match(options, r)) {
		int ind = atoi(options)-1;
		if (ind >= 0 && ind < db.students.size()) {
			StudentPage(db.students[ind], db);
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

void ConsoleInterfaceHandler::StudentPage(Student stud,Database db)
{
	cTools.Clear();
	int yearOfAdmission = stud.getYearOfAdmission();
	char* name = stud.getName();
	char* gender = stud.getGender();
	char* dateOfBorn = stud.getDateOfBorn().toCharArray();
	char* faculty=stud.getFaculty();
	char* departments=stud.getDepartments();
	char* group=stud.getGroup();
	char* numGradebook=stud.getNumGradebook();
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
	if (stud.getSessionsSize() > 0) {

		cout << std::left << "|" << setw(4) << "9" << "|" << "Обнаружены сессии под номерами : ";
		for (int i = 0; i < stud.getSessionsSize() - 1; i++) {
			cout << std::left << stud.getSessionByIndex(1).numSesion << ", ";
		}
		cout << std::left << setw(115 - 34 - stud.getSessionsSize() - (stud.getSessionsSize() - 1) * 2) << stud.getSessionByIndex(stud.getSessionsSize() - 1).numSesion << '|' << endl;
	}
	else {
		cout << std::left << "|" << setw(4) << "9" << "|" << setw(113) << "Сессии не найдены" << '|' << endl;
	}
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << "Для изменения поля или получения более подробной информации о нем введите его номер" << endl;
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
	char* initChars = new char[InitVector.size()];
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
