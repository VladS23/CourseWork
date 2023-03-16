#pragma once
class ConsoleTools
{
public:
	ConsoleTools();
	enum Separators{Simple, Students, PersonalCard};
	void Clear();
	void PrintSeparator(Separators type);
};

