#include "StudentStringBuilder.h"

MyList<char> StudentStringBuilder::toCharVec(Student* s)
{
	StudentStringBuilder* s1 = (StudentStringBuilder*)s;
	MyList<char> result;
	result.push_back(';');
	int i = 0;
	while (s1->name[i] != '\0') {
		result.push_back(s1->name[i]);
		i++;
	}
	result.push_back(':');
	char date[16];
	char day[4];
	char month[4];
	char year[8];
	sprintf_s(day, "%d", s1->dateOfBorn.day);
	sprintf_s(month, "%d", s1->dateOfBorn.month);
	sprintf_s(year, "%d", s1->dateOfBorn.year);
	i = 0;
	while (day[i] != '\0') {
		result.push_back(day[i]);
		i++;
	}
	result.push_back('.');
	i = 0;
	while (month[i] != '\0') {
		result.push_back(month[i]);
		i++;
	}
	result.push_back('.');
	i = 0;
	while (year[i] != '\0') {
		result.push_back(year[i]);
		i++;
	}
	result.push_back(':');
	sprintf_s(year, "%d", s1->yearOfAdmission);
	i = 0;
	while (year[i] != '\0') {
		result.push_back(year[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (s1->faculty[i] != '\0') {
		result.push_back(s1->faculty[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (s1->departments[i] != '\0') {
		result.push_back(s1->departments[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (s1->group[i] != '\0') {
		result.push_back(s1->group[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (s1->numGradebook[i] != '\0') {
		result.push_back(s1->numGradebook[i]);
		i++;
	}
	result.push_back(':');
	i = 0;
	while (s1->gender[i] != '\0') {
		result.push_back(s1->gender[i]);
		i++;
	}
	result.push_back(':');
	for (int i = 0; i < s1->sessions.size(); i++) {
		for (int j = 0; j < s1->sessions[i].oneRes.size(); j++) {
			char sesnum[4];
			sprintf_s(sesnum, "%d", s1->sessions[i].numSesion);
			int k = 0;
			while (sesnum[k] != '\0')
			{
				result.push_back(sesnum[k]);
				k++;
			}
			result.push_back(':');
			k = 0;
			while (s1->sessions[i].oneRes[j].subName[k] != '\0')
			{
				result.push_back(s1->sessions[i].oneRes[j].subName[k]);
				k++;
			}
			result.push_back(':');
			char grad[4];
			sprintf_s(grad, "%d", s1->sessions[i].oneRes[j].grading);
			k = 0;
			while (grad[k] != '\0')
			{
				result.push_back(grad[k]);
				k++;
			}
			result.push_back(':');
		}
	}
	result[result.size() - 1] = ';';
	result.push_back('\n');
	return result;
}
