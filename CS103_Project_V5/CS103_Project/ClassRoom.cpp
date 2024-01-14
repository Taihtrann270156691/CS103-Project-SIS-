#include "ClassRoom.h"
std::shared_ptr<std::map<short, ClassRoom>> classMapPtr = std::make_shared<std::map<short, ClassRoom>>();
const std::string classFile = "ClassRoom.txt";

/// <summary>
/// print list of class room to console
/// </summary>
void ClassRoom::displayInfo() const {
    if (classMapPtr->size() != 0) {
        for (auto it = classMapPtr->begin(); it != classMapPtr->end(); it++) {
            std::cout << "Key Element: " << it->first << std::endl;
            std::cout << "Class Room Name: " << it->second.className << std::endl;
            std::cout << "Class Room Number: " << it->second.roomNumber << std::endl << std::endl;
        }
    }
    else
        std::cout << "ClassRoom's file is empty!\n";
}

/// <summary>
/// add class room's information to ClassRoom.txt
/// </summary>
void ClassRoom::addClass(){
    ClassRoom newClassObj = ClassRoom();
    userInput(newClassObj);

    short newKey = 1;
    // Open the file in append mode
    std::ofstream outFile(classFile, std::ios::app);
    if (classMapPtr->size() != 0) { //if map is not empty
        auto it = --classMapPtr->end(); //fetch the last element
        newKey = it->first + 1; //fetch last element's key
    }

    (*classMapPtr)[newKey] = newClassObj;
    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        outFile << newKey << "-" + newClassObj.className << "-" << newClassObj.roomNumber << std::endl;

        // Close the file
        outFile.close();
        std::cout << "Class room: " << newClassObj.className << ", number: " << newClassObj.roomNumber << " has been added successfully!\n";
    }
}

/// <summary>
/// fetch input from user
/// </summary>
/// <param name="_classObj"></param>
void ClassRoom::userInput(ClassRoom& _classObj){
    std::string _className, _roomNumber;

    // Function to validate first and last names (letters only)
    auto isNameValid = [](const std::string& name) {
        return std::regex_match(name, std::regex("^[A-Z][a-zA-Z]*\\s[A-Z][a-zA-Z]*$"));
        };

    while (true) {
        // Prompt user for first name input and validate
        std::cout << "Enter Class Room Name (letters only): ";
        std::getline(std::cin, _className);
        if (!isNameValid(_className))
            std::cout << "Invalid input. It should contain letters only." << std::endl;
        else
            break;
    }

    // Function to validate date of birth (01/12/1991 format)
    auto isDateOfBirthValid = [](const std::string& dob) {
        return std::regex_match(dob, std::regex("^[0-9]+([a-zA-Z])$"));
        };

    while (true) {
        std::cout << "Enter Room Number (Digits +/- an Alphabet): ";
        std::getline(std::cin, _roomNumber);
        if (!isDateOfBirthValid(_roomNumber))
            std::cout << "Invalid Input." << std::endl;
        else
            break;
    }
    _classObj.className = _className;
    _classObj.roomNumber = _roomNumber;
}

/// <summary>
/// read ClassRoom.txt and fetch data to map container
/// </summary>
void ClassRoom::readClassFile(){
    std::ifstream fileExist(classFile);

    if (fileExist.is_open()) { //file exist
        std::string line;
        while (std::getline(fileExist, line)) { // Read each line
            if (!line.empty())
                splitLine(line);
        }
        fileExist.close(); // Close the file
    }
}

/// <summary>
/// split raw data into a readable chunk of data and fetch them into ClassRoom's map container
/// </summary>
/// <param name="line"></param>
void ClassRoom::splitLine(const std::string& line){
    std::istringstream str(line);
    std::string token;
    std::shared_ptr<std::string[]> myArray(new std::string[3], [](std::string* ptr) { delete[] ptr; });
    /*Array Reference : userArray[0] store keyvalue, schoolArray[1]-[2] store ClassRoom Variables*/

    int i = 0;
    while (std::getline(str, token, '-')) {
        myArray[i] = token;
        i++;
    }

    short key = std::stoi(myArray[0]);
    ClassRoom classObj(myArray[1], myArray[2]);

    (*classMapPtr)[key] = classObj;
}

/// <summary>
/// edit class room's information
/// </summary>
void ClassRoom::editClass(){
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select Class Room you want to edit." << std::endl;
    std::cout << "Key value must be positive integer.";

    do {
        std::cout << "Please enter key: ";
        std::getline(std::cin, key);
        //lambda function to check for positive number
        auto valid = [=]()->bool {std::regex pattern("^[1-9]\\d*$"); //regular expression for positive number
        return std::regex_match(key, pattern); };
        validKey = valid();
        if (!validKey)
            std::cout << "Invalid input! Please enter a valid key element!" << std::endl;
    } while (!validKey); //keep looping to get a valid input

    short finalKey = std::stoi(key); //finally a valid key
    if (classMapPtr->find(finalKey) != classMapPtr->end()) {
        ClassRoom newClassObj = ClassRoom();
        userInput(newClassObj);
        classMapPtr->find(finalKey)->second.className = newClassObj.className;
        classMapPtr->find(finalKey)->second.roomNumber = newClassObj.roomNumber;

        // Open the file in truncation mode
        std::ofstream file(classFile, std::ios::trunc);

        // Check if the file is open
        if (file.is_open()) {
            // Close the file
            file.close();

            //re-write edited element back to file
            
            updateClassFile();

            std::cout << "Class Data updated successfully." << std::endl;
        }
        else
            std::cout << "Error opening ClassRoom.txt." << std::endl;
    }
    else
        std::cout << "Error cannot find school element with provided key." << std::endl;
}

/// <summary>
/// update ClassFile.txt
/// </summary>
void ClassRoom::updateClassFile(){
    // Open the file in append mode
    std::ofstream outFile(parentFile, std::ios::app);

    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        for (auto it = classMapPtr->begin(); it != classMapPtr->end(); it++)
            outFile << it->first << "-" + it->second.className << "-" << it->second.roomNumber  << std::endl;

        // Close the file
        outFile.close();
    }
}

/// <summary>
/// To delete class by selected element of its map container
/// </summary>
void ClassRoom::deleteClass(){
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select class you want to delete." << std::endl;
    std::cout << "Key value must be positive integer.";
    do {
        std::cout << "Please enter key: ";
        std::getline(std::cin, key);
        //lambda function to check for positive number
        auto valid = [=]()->bool {std::regex pattern("^[1-9]\\d*$"); //regular expression for positive number
        return std::regex_match(key, pattern); };
        validKey = valid();
        if (!validKey)
            std::cout << "Invalid input! Please enter a valid key!" << std::endl;
    } while (!validKey); //keep looping to get a valid input

    short finalKey = std::stoi(key); //finally a valid key

    //check if element exist with provided key
    if (classMapPtr->find(finalKey) != classMapPtr->end())
    {
        //delete element with provided key
        classMapPtr->erase(finalKey);

        // Open the file in truncation mode
        std::ofstream file(parentFile, std::ios::trunc);

        // Check if the file is open
        if (file.is_open()) {
            // Close the file
            file.close();
            
            updateClassFile();

            std::cout << "Selected class deleted successfully." << std::endl;
        }
        else
            std::cout << "Error opening the file." << std::endl;
    }
    else
        std::cout << "Error cannot find element with provided key." << std::endl;
}
 