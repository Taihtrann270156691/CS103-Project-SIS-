#include "Parent.h"
std::shared_ptr<std::map<short, Parent>> parentMapPtr = std::make_shared<std::map<short, Parent>>();

/// <summary>
/// print Parent's informations
/// </summary>
void Parent::displayInfo() const {
    if (parentMapPtr->size() != 0) {
        for (auto it = parentMapPtr->begin(); it != parentMapPtr->end(); it++) {
            std::cout << "Key Element: " << it->first << std::endl;
            std::cout << "First Name: " << it->second.firstName << std::endl;
            std::cout << "Last Name: " << it->second.lastName << std::endl;
            std::cout << "Date of Birth: " << it->second.dateOfBirth << std::endl;
            std::cout << "Gender: " << it->second.gender << std::endl << std::endl;
        }
    }
    else
        std::cout << "Parent's file is empty!\n";
}

/// <summary>
/// Add parent's informations to Parent.txt
/// </summary>
void Parent::addParent() {
    Parent newParentObj = Parent();
    userInput(newParentObj);

    short newKey = 1;
    // Open the file in append mode
    std::ofstream outFile(parentFile, std::ios::app);
    if (parentMapPtr->size() != 0) { //if map is not empty
        auto it = --parentMapPtr->end(); //fetch the last element
        newKey = it->first + 1; //fetch last element's key
    }

    (*parentMapPtr)[newKey] = newParentObj;
    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        outFile << newKey << "-" + newParentObj.firstName << "-" << newParentObj.lastName << "-" << newParentObj.dateOfBirth << "-" <<
            newParentObj.gender << std::endl;

        // Close the file
        outFile.close();
        std::cout << "Parent: " << newParentObj.firstName << " " << newParentObj.lastName << " has been added successfully!\n";
    }
}

/// <summary>
/// fetch parent input for parent object
/// </summary>
/// <param name="_parentObj"></param>
void Parent::userInput(Parent& _parentObj){
    std::string _firstName, _lastName, _dateOfBirth, _gender;

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

    _parentObj.firstName = _firstName;
    _parentObj.lastName = _lastName;
    _parentObj.dateOfBirth = _dateOfBirth;
    _parentObj.gender = _gender;
}

/// <summary>
/// read parent.txt and fetch data to map container
/// </summary>
void Parent::readParentFile() {
    std::ifstream fileExist(parentFile);

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
/// split raw data into a readable chunk of data and fetch them into parent's map container
/// </summary>
/// <param name="line"></param>
void Parent::splitLine(const std::string& line) {
    std::istringstream str(line);
    std::string token;
    std::shared_ptr<std::string[]> myArray(new std::string[5], [](std::string* ptr) { delete[] ptr; });
    /*Array Reference : userArray[0] store keyvalue, schoolArray[1]-[4] store Parent Variables*/

    Parent parentObj = Parent();

    short i = 0;
    while (std::getline(str, token, '-')) {
        myArray[i] = token;
        i++;
    }

    short key = std::stoi(myArray[0]);
    parentObj.firstName = myArray[1];
    parentObj.lastName = myArray[2];
    parentObj.dateOfBirth = myArray[3];
    parentObj.gender = myArray[4];

    (*parentMapPtr)[key] = parentObj;
}

/// <summary>
/// edit Parent's information
/// </summary>
void Parent::editParent() {
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select parent you want to edit." << std::endl;
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

    if (parentMapPtr->find(finalKey) != parentMapPtr->end()) {
        Parent newParentObj = Parent();
        userInput(newParentObj);
        parentMapPtr->find(finalKey)->second.firstName = newParentObj.firstName;
        parentMapPtr->find(finalKey)->second.lastName = newParentObj.lastName;
        parentMapPtr->find(finalKey)->second.dateOfBirth = newParentObj.dateOfBirth;
        parentMapPtr->find(finalKey)->second.gender = newParentObj.gender;
        // Open the file in append mode
        std::ofstream outFile(parentFile, std::ios::app);

        if (!outFile) {
            std::cerr << "Error opening Parent.txt file!" << std::endl;
        }
        else {
            // Close the file
            outFile.close();

            for (auto it = parentMapPtr->begin(); it != parentMapPtr->end(); it++)
                updateParentFile(it);

            std::cout << "Parent Data updated successfully." << std::endl;
        }
    }
    else
        std::cout << "Error cannot find Parent element with provided key." << std::endl;
}

/// <summary>
/// update parent.txt
/// </summary>
/// <param name="_userIt"></param>
void Parent::updateParentFile(const std::map<short, Parent>::iterator& _parentIt){
    // Open the file in append mode
    std::ofstream outFile(parentFile, std::ios::app);

    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else {
        // Add data to the end of the file
        outFile << _parentIt->first << "-" + _parentIt->second.firstName << "-" << _parentIt->second.lastName << "-" <<
            _parentIt->second.dateOfBirth << "-" << _parentIt->second.gender << std::endl;

        // Close the file
        outFile.close();
    }
}

/// <summary>
/// To delete parent by selected element of its map container
/// </summary>
void Parent::deleteParent(){
    std::string key;
    bool validKey;
    std::cout << "Please provide key value to select parent you want to delete." << std::endl;
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
    auto it = parentMapPtr->find(finalKey);
    if (it != parentMapPtr->end())
    {
        //delete element with provided key
        parentMapPtr->erase(finalKey);

        // Open the file in truncation mode
        std::ofstream file(parentFile, std::ios::trunc);

        // Check if the file is open
        if (file.is_open()) {
            // Close the file
            file.close();
            for (auto it = parentMapPtr->begin(); it != parentMapPtr->end(); it++)
                updateParentFile(it);

            std::cout << "Selected parent deleted successfully." << std::endl;
        }
        else
            std::cout << "Error opening the file." << std::endl;
    }
    else
        std::cout << "Error cannot find element with provided key." << std::endl;
}
