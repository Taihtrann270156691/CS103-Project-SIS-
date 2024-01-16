#pragma once
#include "SystemFunction.h"
const std::string parentFile = "Parent.txt";
class Parent {

public:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string gender;

public:
    Parent() = default;

    Parent(const std::string& firstName, const std::string& lastName, const std::string& dateOfBirth, const std::string& gender)
        : firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), gender(gender){}

    // Member function to display Parent information
    void displayInfo() const;

    // Member function to add Parent information to Parent.txt
    void addParent();

    // Member function to fetch input from user for Parent object
    void userInput(Parent& _studentObj);

    // Member function to read Parent information from Parent.txt
    void readParentFile();

    // Member function to split raw data into readable data
    void splitLine(const std::string& line);

    //Member function to edite Parent information
    void editParent();

    // Member function to update Parent.txt
    void updateParentFile(const std::map<short, Parent>::iterator& _parentIt);

    // Member function to delete selected element of Parent
    void deleteParent();
};

