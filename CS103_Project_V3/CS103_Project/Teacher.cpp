#include "Teacher.h"

const std::string teacherFile = "Teacher.txt";
//teacherMapPtr variable
std::shared_ptr<std::map<short, Teacher>> teacherMapPtr = std::make_shared<std::map<short, Teacher>>();

/// <summary>
/// Print Teacher's info
/// </summary>
void Teacher::displayInfo() const {
    if (teacherMapPtr->size() != 0) { 
        for (auto it = teacherMapPtr->begin(); it != teacherMapPtr->end(); it++) {
            std::cout << "First Name: " << it->second.firstName << std::endl;
            std::cout << "Last Name: " << it->second.lastName << std::endl;
            std::cout << "Date of Birth: " << it->second.dateOfBirth << std::endl;
            std::cout << "Gender: " << it->second.gender << std::endl;
            std::cout << "Role: " << it->second.role << std::endl;
        }
    }
    else
        std::cout << "Teacher's file is empty!\n";
	
}

/// <summary>
/// add teacher to Teacher.txt
/// </summary>
void Teacher::addTeacher(){
    Teacher newTeacherObj = Teacher();
    userInput(newTeacherObj);
    
    short newKey = 1;
    // Open the file in append mode
    std::ofstream outFile(teacherFile, std::ios::app);
    if (teacherMapPtr->size() != 0) { //if map is not empty
        auto it = --teacherMapPtr->end(); //fetch the last element
        newKey = it->first + 1; //fetch last element's key
    }
     
    (*teacherMapPtr)[newKey] = newTeacherObj;
    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        outFile << newKey << "-" + newTeacherObj.firstName << "-" << newTeacherObj.lastName << "-" << newTeacherObj.dateOfBirth << "-" <<
                newTeacherObj.gender << "-" << newTeacherObj.role << std::endl;

        // Close the file
        outFile.close();
        std::cout << newTeacherObj.firstName << " " << newTeacherObj.lastName << " has been added successfully!\n";
    }
}

/// <summary>
/// fetch user input for teacher object
/// </summary>
/// <param name="_teacherObj"></param>
void Teacher::userInput(Teacher& _teacherObj) {
    std::string _firstName, _lastName, _dateOfBirth, _gender, _role;

    // Function to validate first and last names (letters only)
    auto isNameValid = [](const std::string& name) {
        return std::regex_match(name, std::regex("^[A-Za-z]+$"));
        };

    while (true) {
        // Prompt user for first name input and validate
        std::cout << "Enter First Name (letters only): ";
        std::getline(std::cin, _firstName);
        if (!isNameValid(_firstName))
            std::cout << "Invalid First Name. It should contain letters only." << std::endl;
        else
            break;
    }

    while (true) {
        // Prompt user for last name input and validate
        std::cout << "Enter Last Name (letters only): ";
        std::getline(std::cin, _lastName);
        if (!isNameValid(_lastName))
            std::cout << "Invalid Last Name. It should contain letters only." << std::endl;
        else
            break;
    }

    // Function to validate date of birth (01/12/1991 format)
    auto isDateOfBirthValid = [](const std::string& dob) {
        return std::regex_match(dob, std::regex("^\\d{2}/\\d{2}/\\d{4}$"));
        };

    while (true) {
        std::cout << "Enter Date of Birth (dd/mm/yyyy): ";
        std::getline(std::cin, _dateOfBirth);
        if (!isDateOfBirthValid(_dateOfBirth))
            std::cout << "Invalid Date of Birth. Use the format dd/mm/yyyy." << std::endl;
        else
            break;
    }

    // Function to validate gender (m/M, f/F, o/O)
    auto isGenderValid = [](const std::string& gender) {
        return std::regex_match(gender, std::regex("^[mMfFoO]$"));
        };

    while (true) {
        std::cout << "Enter Gender (M=Male|F=Female|O=Others): ";
        std::getline(std::cin, _gender);
        if (!isGenderValid(_gender))
            std::cout << "Invalid Gender. Use 'm'/'M' for male, 'f'/'F' for female, 'o'/'O' for others." << std::endl;
        else
            break;
    }

    std::cout << "Enter Role: ";
    //std::cin.ignore();  // Clear the newline character from the previous input
    std::getline(std::cin, _role);

    _teacherObj.firstName = _firstName;
    _teacherObj.lastName = _lastName;
    _teacherObj.dateOfBirth = _dateOfBirth;
    _teacherObj.gender = _gender;
    _teacherObj.role = _role;
}

/// <summary>
/// read Teacher.txt and fetch data to map container
/// </summary>
void Teacher::readTeacherFile() {
    std::ifstream fileExist(teacherFile);

    if (fileExist.is_open()) { //file exist
        std::string line;
        while (std::getline(fileExist, line)) { // Read each line
            if(!line.empty())
                splitLine(line);
        }
        fileExist.close(); // Close the file
        //if (!(teacherMapPtr->size() > 0)) {} //if Teacher.txt file is empty
            //addAdmin();
    }
    else { //create Teacher.txt file 
        //addAdmin();
    }
}

/// <summary>
/// split raw data into a readable chunk of data and fetch them into teacher's map container
/// </summary>
/// <param name="line"></param>
void Teacher::splitLine(const std::string& line) {
    std::istringstream str(line);
    std::string token;
    std::shared_ptr<std::string[]> myArray(new std::string[6], [](std::string* ptr) { delete[] ptr; });
    /*Array Reference : userArray[0] store keyvalue, schoolArray[1]-[5] store Teacher Variable*/

    Teacher teacherObj = Teacher();

    int i = 0;
    while (std::getline(str, token, '-')) {
        myArray[i] = token;
        i++;
    }

    short key = std::stoi(myArray[0]);
    teacherObj.firstName = myArray[1];
    teacherObj.lastName = myArray[2];
    teacherObj.dateOfBirth = myArray[3];
    teacherObj.gender = myArray[4];
    teacherObj.role = myArray[5];
    
    (*teacherMapPtr)[key] = teacherObj;
}

/// <summary>
/// edit teacher's informations
/// </summary>
void Teacher::editTeacher() {
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select teacher you want to edit." << std::endl;
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
    auto it = teacherMapPtr->find(finalKey);
    if (it != teacherMapPtr->end())
    {
        Teacher newTeacherObj = Teacher();
        userInput(newTeacherObj);

        short newKey = 1;
        // Open the file in append mode
        std::ofstream outFile(teacherFile, std::ios::app);
        if (teacherMapPtr->size() != 0) { //if map is not empty
            auto it = --teacherMapPtr->end(); //fetch the last element
            newKey = it->first + 1; //fetch last element's key
        }

        (*teacherMapPtr)[newKey] = newTeacherObj;
        if (!outFile) {
            std::cerr << "Error opening the file!" << std::endl;
        }
        else {
            // Add data to the end of the file
            outFile << newKey << "-" + newTeacherObj.firstName << "-" << newTeacherObj.lastName << "-" << newTeacherObj.dateOfBirth << "-" <<
                newTeacherObj.gender << "-" << newTeacherObj.role << std::endl;

            // Close the file
            outFile.close();
            std::cout << newTeacherObj.firstName << " " << newTeacherObj.lastName << " has been added successfully!\n";
        }
    }
    else
        std::cout << "Error cannot find school element with provided key." << std::endl;
}

/// <summary>
/// update Teacher.txt
/// </summary>
/// <param name="_userIt"></param>
void Teacher::updateTeacherFile(const std::map<short, Teacher>::iterator& _teacherIt) {
    // Open the file in append mode
    std::ofstream outFile(teacherFile, std::ios::app);

    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        outFile << _teacherIt->first << "-" + _teacherIt->second.firstName << "-" << _teacherIt->second.lastName << "-" << 
            _teacherIt->second.dateOfBirth << "-" << _teacherIt->second.gender << "-" << _teacherIt->second.role << std::endl;

        // Close the file
        outFile.close();
    }
}

/// <summary>
/// To delete teacher by selected element of its map container
/// </summary>
void Teacher::deleteTeacher() {
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select teacher you want to delete." << std::endl;
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
    auto it = teacherMapPtr->find(finalKey);
    if (it != teacherMapPtr->end())
    {
        //delete element with provided key
        teacherMapPtr->erase(finalKey);

        // Open the file in truncation mode
        std::ofstream file(teacherFile, std::ios::trunc);

        // Check if the file is open
        if (file.is_open()) {
            // Close the file
            file.close();
            for (auto it = teacherMapPtr->begin(); it != teacherMapPtr->end(); it++)
                updateTeacherFile(it);

            std::cout << "Selected teacher deleted successfully." << std::endl;
        }
        else
            std::cout << "Error opening the file." << std::endl;
    }
    else
        std::cout << "Error cannot find element with provided key." << std::endl;
}

