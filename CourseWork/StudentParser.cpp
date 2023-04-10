#include "StudentParser.h"


void StudentParser::parse(char initString[10240], Student* s)
{
	StudentParser* s1=(StudentParser*)s;
	MyList <dataEl> initList;
	int i = 0;
	if (initString[i] == ';') {
		i++;
		while (initString[i] != ';') {
			dataEl curDataEl;
			int k = 0;
			while (k < 64 && curDataEl.chars[k] != '\0') {
				curDataEl.chars[k] = '\0';
				k++;
			}
			int j = 0;
			while (initString[i] != ':' && initString[i + 1] != ';') {
				curDataEl.chars[j] = initString[i];
				i++;
				j++;
			}
			if (initString[i + 1] == ';') {
				curDataEl.chars[j] = initString[i];
			}
			i++;
			initList.push_back(curDataEl);
		}
		i = 0;
		int curentInitVecEl = 0;
		while (i < 64) {
			s1->name[i] = initList[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		int date[3];
		int curDateEl = 0;
		while (initList[curentInitVecEl].chars[i] != '\0')
		{
			char curInt[8] = { '0' };
			int k = 0;
			while (initList[curentInitVecEl].chars[i] != '.' && initList[curentInitVecEl].chars[i] != '\0') {
				curInt[k] = initList[curentInitVecEl].chars[i];
				i++;
				k++;
			}
			i++;
			date[curDateEl] = atoi(curInt);
			curDateEl++;
		}
		s1->dateOfBorn.day = date[0];
		s1->dateOfBorn.month = date[1];
		s1->dateOfBorn.year = date[2];
		i = 0;
		curentInitVecEl++;
		s1->yearOfAdmission = atoi(initList[curentInitVecEl].chars);
		curentInitVecEl++;
		while (i < 64) {
			s1->faculty[i] = initList[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		while (i < 64) {
			s1->departments[i] = initList[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		while (i < 16) {
			s1->group[i] = initList[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		while (i < 16) {
			s1->numGradebook[i] = initList[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		i = 0;
		while (i < 32) {
			s1->gender[i] = initList[curentInitVecEl].chars[i];
			i++;
		}
		curentInitVecEl++;
		int prevSession = 0;
		int curSesIterator = -1;
		while (curentInitVecEl < initList.size())
		{
			if (atoi(initList[curentInitVecEl].chars) > prevSession) {
				Session curSes;
				prevSession = atoi(initList[curentInitVecEl].chars);
				curSes.numSesion = atoi(initList[curentInitVecEl].chars);
				s1->sessions.push_back(curSes);
				curSesIterator++;
				curentInitVecEl++;
			}
			else {
				curentInitVecEl++;
			}
			Result curOneRes;
			int i = 0;
			while (i < 64) {
				curOneRes.subName[i] = initList[curentInitVecEl].chars[i];
				i++;
			}
			curentInitVecEl++;
			curOneRes.grading = atoi(initList[curentInitVecEl].chars);
			s1->sessions[curSesIterator].oneRes.push_back(curOneRes);
			curentInitVecEl++;
		}
	}
}
