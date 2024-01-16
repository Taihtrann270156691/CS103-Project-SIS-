#pragma once
#include "SystemFunction.h"

class ClassRoom {
public:
	std::string className;
    std::string roomNumber;

public:
	ClassRoom() = default;
    ClassRoom(const std::string& className, const std::string& roomNumber)
        : className(className), roomNumber(roomNumber){}
    // Member function to display ClassRoom information
    void displayInfo() const;

    // Member function to add ClassRoom information to ClassRoom.txt
    void addClass();

    // Member function to fetch input from user for ClassRoom object
    void userInput(ClassRoom& _classObj);

    // Member function to read ClassRoom information from ClassRoom.txt
    void readClassFile();

    // Member function to split raw data into readable data
    void splitLine(const std::string& line);

    //Member function to edite ClassRoom information
    void editClass();

    // Member function to update ClassRoom.txt
    void updateClassFile();

    // Member function to delete selected element of ClassRoom
    void deleteClass();

};

