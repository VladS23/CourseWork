#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Student.h"
using namespace std;

int main() {
    char c1[1024] = "Петров Петр Петрович:1.12.2003:2021:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:calculation:4:1:phys:3:2:programming:5;";
    Student s1(c1);
    int y = 5 + 9;
    vector <char> v1 = s1.toCharVec();
    char* c2 = (char*)malloc(sizeof(char) * v1.size());
    for (int i = 0; i < v1.size(); i++){
        *(c2 + i) = v1[i];
}
    *(c2 + v1.size()) = '\0';
    Student s2(c2);
    vector <char> v2 = s2.toCharVec();
    char* c3 = (char*)malloc(sizeof(char) * v2.size());
    for (int i = 0; i < v2.size(); i++) {
        *(c3 + i) = v2[i];
    }
    int i1 = s1.getYearOfAdmission();
    char* cc1 = s1.getFaculty();
    char* cc2 = s1.getDepartments();
    char* cc3 = s1.getGroup();
    char* cc4 = s1.getNumGradebook();
    char* cc5 = s1.getName();
    char* cc6 = s1.getGender();
    Date d1 = s1.getDateOfBorn();
    int x = 5 + 9;
    return 0;
}