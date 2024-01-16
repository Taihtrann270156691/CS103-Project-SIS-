#include "Student.h"
const std::string studentFile = "Student.txt";
//studentMapPtr variable
std::shared_ptr<std::map<short, Student>> studentMapPtr = std::make_shared<std::map<short, Student>>();

/// <summary>
/// Print student's info
/// </summary>
void Student::displayInfo() const {
    if (studentMapPtr->size() != 0) {
        for (auto it = studentMapPtr->begin(); it != studentMapPtr->end(); it++) {
            std::cout << "Key Element: " << it->first << std::endl;
            std::cout << "First Name: " << it->second.firstName << std::endl;
            std::cout << "Last Name: " << it->second.lastName << std::endl;
            std::cout << "Date of Birth: " << it->second.dateOfBirth << std::endl;
            std::cout << "Gender: " << it->second.gender << std::endl;
            std::cout << "Course: " << it->second.course << std::endl << std::endl;
        }
    }
    else
        std::cout << "Student's file is empty!\n";
}

/// <summary>
/// add student to student.txt
/// </summary>
void Student::addStudent() {
    Student newStudentObj = Student();
    userInput(newStudentObj);

    short newKey = 1;
    // Open the file in append mode
    std::ofstream outFile(studentFile, std::ios::app);
    if (studentMapPtr->size() != 0) { //if map is not empty
        auto it = --studentMapPtr->end(); //fetch the last element
        newKey = it->first + 1; //fetch last element's key
    }

    (*studentMapPtr)[newKey] = newStudentObj;
    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        outFile << newKey << "-" + newStudentObj.firstName << "-" << newStudentObj.lastName << "-" << newStudentObj.dateOfBirth << "-" <<
            newStudentObj.gender << "-" << newStudentObj.course << std::endl;

        // Close the file
        outFile.close();
        std::cout << "Student: " <<  newStudentObj.firstName << " " << newStudentObj.lastName << " has been added successfully!\n";
    }
}

/// <summary>
/// fetch user input for sudent object
/// </summary>
/// <param name="_studentObj"></param>
void Student::userInput(Student& _studentObj) {
    std::string _firstName, _lastName, _dateOfBirth, _gender, _course;

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

    auto isCourseValid = [](const std::string& name) {
        return std::regex_match(name, std::regex("^[A-Z][a-zA-Z]*\\s[A-Z][a-zA-Z]*$"));
        };

    while (true) {
        std::cout << "What course does the student enrol in?" << std::endl;
        std::cout << "Please Enter (letters only): ";
        std::getline(std::cin, _course);
        if (!isCourseValid(_course))
            std::cout << "Invalid Course Name. It should contain letters only." << std::endl;
        else
            break;
    }

    _studentObj.firstName = _firstName;
    _studentObj.lastName = _lastName;
    _studentObj.dateOfBirth = _dateOfBirth;
    _studentObj.gender = _gender;
    _studentObj.course = _course;
}

/// <summary>
/// read student.txt and fetch data to map container
/// </summary>
void Student::readStudentFile() {
    std::ifstream fileExist(studentFile);

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
/// split raw data into a readable chunk of data and fetch them into student's map container
/// </summary>
/// <param name="line"></param>
void Student::splitLine(const std::string& line) {
    std::istringstream str(line);
    std::string token;
    std::shared_ptr<std::string[]> myArray(new std::string[6], [](std::string* ptr) { delete[] ptr; });
    /*Array Reference : userArray[0] store keyvalue, schoolArray[1]-[5] store Student Variable*/

    Student studentObj = Student();

    short i = 0;
    while (std::getline(str, token, '-')) {
        myArray[i] = token;
        i++;
    }

    short key = std::stoi(myArray[0]);
    studentObj.firstName = myArray[1];
    studentObj.lastName = myArray[2];
    studentObj.dateOfBirth = myArray[3];
    studentObj.gender = myArray[4];
    studentObj.course = myArray[5];

    (*studentMapPtr)[key] = studentObj;
}

/// <summary>
/// edit student's informations
/// </summary>
void Student::editStudent() {
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select student you want to edit." << std::endl;
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
    auto it = studentMapPtr->find(finalKey);
    if (studentMapPtr->find(finalKey) != studentMapPtr->end()){
        Student newStudentObj = Student();
        userInput(newStudentObj);
        
        studentMapPtr->find(finalKey)->second.firstName = newStudentObj.firstName;
        studentMapPtr->find(finalKey)->second.lastName = newStudentObj.lastName;
        studentMapPtr->find(finalKey)->second.dateOfBirth = newStudentObj.dateOfBirth;
        studentMapPtr->find(finalKey)->second.gender = newStudentObj.gender;
        studentMapPtr->find(finalKey)->second.course = newStudentObj.course;

        // Open the file in truncation mode
        std::ofstream file(studentFile, std::ios::trunc);

        // Check if the file is open
        if (file.is_open()) {
            // Close the file
            file.close();

            //re-write edited element back to file
            for (auto it = studentMapPtr->begin(); it != studentMapPtr->end(); it++)
                updateStudentFile(it);

            std::cout << "Student Data updated successfully." << std::endl;
        }
        else
            std::cout << "Error opening Student.txt." << std::endl;

    }
    else
        std::cout << "Error cannot find student element with provided key." << std::endl;
}

/// <summary>
/// update Student.txt
/// </summary>
/// <param name="_userIt"></param>
void Student::updateStudentFile(const std::map<short, Student>::iterator& _studentIt) {
    // Open the file in append mode
    std::ofstream outFile(studentFile, std::ios::app);

    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        outFile << _studentIt->first << "-" + _studentIt->second.firstName << "-" << _studentIt->second.lastName << "-" <<
            _studentIt->second.dateOfBirth << "-" << _studentIt->second.gender << "-" << _studentIt->second.course << std::endl;

        // Close the file
        outFile.close();
    }
}

/// <summary>
/// To delete student by selected element of its map container
/// </summary>
void Student::deleteStudent() {
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select student you want to delete." << std::endl;
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
    auto it = studentMapPtr->find(finalKey);
    if (it != studentMapPtr->end())
    {
        //delete element with provided key
        studentMapPtr->erase(finalKey);

        // Open the file in truncation mode
        std::ofstream file(studentFile, std::ios::trunc);

        // Check if the file is open
        if (file.is_open()) {
            // Close the file
            file.close();
            for (auto it = studentMapPtr->begin(); it != studentMapPtr->end(); it++)
                updateStudentFile(it);

            std::cout << "Selected student deleted successfully." << std::endl;
        }
        else
            std::cout << "Error opening the file." << std::endl;
    }
    else
        std::cout << "Error cannot find element with provided key." << std::endl;
}