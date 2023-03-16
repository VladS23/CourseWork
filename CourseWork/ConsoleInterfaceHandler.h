#pragma once
#include "Database.h"
class ConsoleInterfaceHandler
{
public:
	ConsoleInterfaceHandler();
private:
	void StartPage();
	void MainPage(Database db);
	void Clear();
	void StudentPage(Student stud, Database db);
};

