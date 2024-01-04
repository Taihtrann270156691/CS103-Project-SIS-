#pragma once
#include "School.h"

void fileReading(std::shared_ptr<std::map<short, School>> _schoolPtr);
void splitLine(std::shared_ptr<std::map<short, School>> _schoolPtr, const std::string& line);
void addSchool(const std::map<short, School>::iterator& it);
void createNewFile(const std::map<short, School>::iterator& _school);
void updateFile(const std::map<short, School>::iterator& _school);