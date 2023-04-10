#pragma once
#include "Student.h"
class StudentStringBuilder: private Student
{
public:
	static 	MyList<char> toCharVec(Student* s);
};

