#pragma once
#include "Database.h"
#include "ConsoleTools.h"
class ConsoleInterfaceHandler
{
public:
	ConsoleInterfaceHandler();
private:
	ConsoleTools cTools;
	enum UpdatePage { Name=1, DateOfBorn, Gender, YearOfAdmissions, Faculty, Departsment, Group, numOfGradebook };
	void StartPage();
	void MainPage(Database db);
	void StudentPage(int ind, Database db);
	void CreateStudentPage(Database db);
	void FiltredStud(Database db);
	void SavePage(Database db);
	void UpdateStudPage(UpdatePage options, int ind, Database db);
	void SessionsPage(Database db, int ind);
	void AddSessionPage(Database db, int ind);
	void SessionPage(Database db, int ind, int sesInd);
	void DeleteSessionPage(Database db, int ind);
	void AddSesRes(Database db, int ind, int sesInd);
	void UpdateOrDeleteRes(Database db, int ind, int sesInd, int resInd);
};

