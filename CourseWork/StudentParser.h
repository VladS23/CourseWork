#pragma once
#include "Student.h"
class StudentParser:private Student
{
public:
	static void parse(char initString[10240], Student* s);
};

