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
	cout << "Для просмотра или изменения записи введите ее номер, чтобы добавить запись введите 0, для применения фильтров введите 999999"<<endl;
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
	static const regex r(R"(^[1-9]{0,6}$)");
	if (regex_match(options, r)) {
		int ind = atoi(options)-1;
		if (ind >= 0 && ind < db.students.size()) {
			StudentPage(db.students[ind], db);
		}
		else if(ind==-1) {
			CreateStudentPage(db);
		}
		else if (ind == 999998) {
			FiltredStud(db);
		}
		else {
			cout << "Некорректный номер" << endl;
			Sleep(1000);
			MainPage(db);
			cTools.Clear();
		}
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
	cout << std::left <<  "|"<<setw(4)<<"9"<<"|"<<"Обнаружены сессии под номерами : ";
	for (int i = 0; i < stud.getSessionsSize() - 1; i++) {
		cout << std::left << stud.getSessionByIndex(1).numSesion << ", ";
	}
	cout << std::left << setw (115-34 - stud.getSessionsSize() - (stud.getSessionsSize()-1)*2) << stud.getSessionByIndex(stud.getSessionsSize() - 1).numSesion << '|' << endl;
	cTools.PrintSeparator(ConsoleTools::Separators::Simple);
	cout << "Для изменения поля или получения более подробной информации о нем введите его номер" << endl;
}

void ConsoleInterfaceHandler::CreateStudentPage(Database db)
{
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
