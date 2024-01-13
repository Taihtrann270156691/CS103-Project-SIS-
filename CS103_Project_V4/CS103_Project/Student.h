#pragma once
#include "SystemFunction.h"
class Student {
public:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string gender;

public:
    // Constructor to initialize the Student object
    Student(const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& gender, const std::string& role)
        : firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), gender(gender) {}
    Student() = default;

    // Member function to display student information
    void displayInfo() const;

    // Member function to add student information to student.txt
    void addStudent();

    // Member function to fetch input from user for student object
    void userInput(Student& _studentObj);

    // Member function to read student information from student.txt
    void readStudentFile();

    // Member function to split raw data into readable data
    void splitLine(const std::string& line);

    //Member function to edite student information
    void editStudent();

    // Member function to update student.txt
    void updateStudentFile(const std::map<short, Student>::iterator& _studentIt);

    // Member function to delete selected element of student
    void deleteStudent();

};

