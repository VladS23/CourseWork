#pragma once
#include "Database.h"
#include "ConsoleTools.h"
class ConsoleInterfaceHandler
{
public:
	ConsoleInterfaceHandler();
private:
	ConsoleTools cTools;
	void StartPage();
	void MainPage(Database db);
	void StudentPage(Student stud, Database db);
	void CreateStudentPage(Database db);
	void FiltredStud(Database db);
};

