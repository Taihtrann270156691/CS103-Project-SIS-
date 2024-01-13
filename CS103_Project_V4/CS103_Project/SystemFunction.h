#pragma once
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <regex>
#include <memory>
#include <string>
#include <iostream>
#include "School.h"
#include "UserLogin.h"
#include "Teacher.h"
#include "Student.h"
#include "Parent.h"

void schoolMenu();
short mainMenu(bool& _admin);
short schoolChoice();
void manageSchoolFiles();
void printSystemWelcome();
void teacherMenu(bool _admin);
void studentMenu(bool _admin);
void parentMenu(bool _admin);