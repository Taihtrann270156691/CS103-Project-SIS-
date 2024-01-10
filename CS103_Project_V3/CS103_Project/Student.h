#pragma once
#include "SystemFunction.h"
class Student
{
public:
    // Constructor to initialize the Teacher object
    Student(const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& gender, const std::string& role)
        : firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), gender(gender) {}
    Student() = default;

    // Member function to display teacher information
    void displayInfo() const;

    // Member function to add teacher information to Teacher.txt
    void addStudent();

    // Member function to fetch input from user for teacher object
    void userInput(Student& _studentObj);

    // Member function to read teacher information from Teacher.txt
    void readStudentFile();

    // Member function to split raw data into readable data
    void splitLine(const std::string& line);

    //Member function to edite teacher information
    void editStudent();

    // Member function to update teacher.txt
    void updateStudentFile(const std::map<short, Student>::iterator& _userIt);

    // Member function to delete selected element of Teacher
    void deleteStudent();

public:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string gender;
};

