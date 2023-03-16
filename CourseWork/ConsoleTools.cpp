#include "ConsoleTools.h"
#include <iostream>
using namespace std;

ConsoleTools::ConsoleTools()
{
}

void ConsoleTools::Clear()
{
	cout << "\x1B[2J\x1B[H";
}

void ConsoleTools::PrintSeparator(Separators type)
{
	switch (type)
	{
	case ConsoleTools::Simple:
		cout << "|----------------------------------------------------------------------------------------------------------------------|" << endl;
		break;
	case ConsoleTools::Students:
		cout << "|-----|----------------------------------------------------------------------|-------------|---------------------------|" << endl;
		break;
	case ConsoleTools::PersonalCard:
		cout << "|----|-----------------------------------------------------------------|----|------------------------------------------|" << endl;
		break;
	default:
		break;
	}
}
