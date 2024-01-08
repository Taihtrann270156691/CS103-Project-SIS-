#pragma once
#include "SystemFunction.h"
class Teacher {
public:
    // Constructor to initialize the Teacher object
    Teacher(const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& gender, const std::string& role)
        : firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), gender(gender), role(role) {}
    Teacher() = default;

    // Member function to display teacher information
    void displayInfo() const;

    // Member function to add teacher information to Teacher.txt
    void addTeacher();

    // Member function to fetch input from user for teacher object
    void userInput(Teacher& _teacherObj);

    // Member function to read teacher information from Teacher.txt
    void readTeacherFile();

    // Member function to split raw data into readable data
    void splitLine(const std::string& line);

    //Member function to edite teacher information
    void editTeacher();

    // Member function to update teacher.txt
    void updateTeacherFile(const std::map<short, Teacher>::iterator& _userIt);

    // Member function to delete selected element of Teacher
    void deleteTeacher();

public:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string gender;
    std::string role;
    //Science, Math, Social Study etc...
};

