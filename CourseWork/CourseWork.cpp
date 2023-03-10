#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Student.h"
using namespace std;

int main() {
    char c1[1024] = "Петров Петр Петрович:1.12.2003:2021:ИКБ:КБ-1:БАСО-01-21:Б0404:male:1:calculation:4:1:phys:3:2:programming:5;";
    Student s1(c1);
    int x = 5 + 9;
    return 0;
}