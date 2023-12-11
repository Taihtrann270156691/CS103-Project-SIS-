#include "School.h"

//global variable
const std::string SchoolInfo = "SchoolInfo.txt";

//School constructor
School::School(const std::string& schoolName, const std::string& phoneNumber, const std::string& email,
	const std::string& website, const std::shared_ptr<Address>& address)
	: schoolName(schoolName), phoneNumber(phoneNumber), email(email), website(website), address(address) {}

/// <summary>
/// print school information
/// </summary>
void School::display() const {
	std::cout << schoolName << std::endl;
	address->display();
}

/// <summary>
/// prompt user for school information input, then return as a single element iterator
/// </summary>
/// <param name="_schoolPtr"></param>
/// <returns></returns>
std::map<short, School>::iterator School::userInput_School(std::shared_ptr<std::map<short, School>>& _schoolPtr) {
	School schlObj;
	short key;

	std::string input;

	//if not empty, get last key value and increment it by 1
	if (!_schoolPtr->empty()) {
		auto value = --_schoolPtr->end();
		key = value->first + 1;
	}
	else//map is empty assign 1 to key for first element
		key = 1;

	std::cout << "Please enter School name: ";
	std::getline(std::cin, input);

	schlObj.schoolName = input;
	schlObj.phoneNumber = "phone";
	schlObj.email = "email";
	schlObj.website = "website";
	schlObj.address->streetNumber = "streetnum";
	schlObj.address->streetName = "streetname";
	schlObj.address->suburb = "suburb,";
	schlObj.address->city = "city";
	schlObj.address->postCode = 1234;
	(*_schoolPtr)[key] = schlObj; //assign school object to map pointer
	/*std::cout << "Please enter School Phone Number: ";
	std::getline(std::cin, schoolArray[2]);

	std::cout << "Please enter School email: ";
	std::getline(std::cin, schoolArray[3]);

	std::cout << "Please enter School website: ";
	std::getline(std::cin, schoolArray[4]);

	std::cout << "Please enter School street number: ";
	std::getline(std::cin, schoolArray[5]);

	std::cout << "Please enter School street name: ";
	std::getline(std::cin, schoolArray[6]);

	std::cout << "Please enter School suburb: ";
	std::getline(std::cin, schoolArray[7]);

	std::cout << "Please enter School city: ";
	std::getline(std::cin, schoolArray[8]);

	std::cout << "Please enter School postcode: ";
	std::getline(std::cin, schoolArray[9]); */

	auto it = --_schoolPtr->end(); //fetch element we just added to single iterator
	return it;  //return iterator
}

/// <summary>
///
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
bool School::isValid(std::string& input) {
	return true;
}

/// <summary>
/// read and fetch all data to school map pointer
/// </summary>
/// <param name="_schoolPtr"></param>
void School::readSchoolFile(schoolMapPtr& _schoolPtr) {
	std::ifstream fileExist(SchoolInfo);
	if (fileExist.is_open()) { //file exist
		std::string line;
		while (std::getline(fileExist, line)) { // Read each line
			splitLine(_schoolPtr, line);
		}
		fileExist.close(); // Close the file
	}
}

/// <summary>
/// tokenise raw data into a readable texts
/// </summary>
/// <param name="_schoolPtr"></param>
/// <param name="line"></param>
void School::splitLine(schoolMapPtr& _schoolPtr, const std::string& line) {
	std::istringstream str(line);
	std::string token;
	std::shared_ptr<std::string[]> schoolArray(new std::string[10], [](std::string* ptr) { delete[] ptr; });
	/*Array Reference : schoolArray[0] -> keyvalue, schoolArray[1]-[4] -> School Variable,
						schoolArray[5]-[9] -> School::Address Variable*/

	School schlObj;

	int i = 0;
	while (std::getline(str, token, '-')) {
		schoolArray[i] = token;
		i++;
	}

	short key = std::stoi(schoolArray[0]);
	schlObj.schoolName = schoolArray[1];
	schlObj.phoneNumber = schoolArray[2];
	schlObj.email = schoolArray[3];
	schlObj.website = schoolArray[4];
	schlObj.address->streetNumber = schoolArray[5];
	schlObj.address->streetName = schoolArray[6];
	schlObj.address->suburb = schoolArray[7];
	schlObj.address->city = schoolArray[8];
	schlObj.address->postCode = std::stoi(schoolArray[9]);

	(*_schoolPtr)[std::stoi(schoolArray[0])] = schlObj;
}

/// <summary>
/// add school function
/// </summary>
/// <param name="it"></param>
void School::addSchool(const schoolMapIt& it) {
	std::ifstream fileExist(SchoolInfo);
	if (fileExist.is_open()) { //file exist
		fileExist.close(); // Close the file
		updateSchoolFile(it); //adding new element to file
	}
	else {
		createNewFile(it);
	}
}

/// <summary>
/// //create a new file "SchoolInfo.txt" with user input element
/// </summary>
/// <param name="it"></param>
void School::createNewFile(const schoolMapIt& it) {
	// Writing to a file
	std::ofstream outFile(SchoolInfo); // Create or open a file for writing
	if (outFile.is_open())
	{ // Check if the file is open
		outFile << it->first << "-" << it->second.schoolName
			<< "-" << it->second.phoneNumber << "-" << it->second.email
			<< "-" << it->second.website << "-" << it->second.address->streetNumber
			<< "-" << it->second.address->streetName << "-" << it->second.address->suburb
			<< "-" << it->second.address->city
			<< "-" << it->second.address->postCode << std::endl;

		outFile.close(); // Close the file

		std::cout << "Data has been written to the file name School.txt." << std::endl;
	}
	else
		std::cerr << "Unable to open the file for writing." << std::endl;
}

/// <summary>
/// update file with added element
/// </summary>
/// <param name="it"></param>
void School::updateSchoolFile(const schoolMapIt& it) {
	// Open the file in append mode
	std::ofstream outFile(SchoolInfo, std::ios::app);

	if (!outFile) {
		std::cerr << "Error opening the file!" << std::endl;
	}
	else {
		// Add data to the end of the file
		outFile << it->first << "-" << it->second.schoolName
			<< "-" << it->second.phoneNumber << "-" << it->second.email
			<< "-" << it->second.website << "-" << it->second.address->streetNumber
			<< "-" << it->second.address->streetName << "-" << it->second.address->suburb
			<< "-" << it->second.address->city
			<< "-" << it->second.address->postCode << std::endl;

		// Close the file
		outFile.close();

		//std::cout << "Data added to the file successfully." << std::endl;
	}
}

/// <summary>
/// delete selected key element of school object
/// </summary>
/// <param name="_schoolPtr"></param>
void School::deleteSchool(const schoolMapPtr& _schoolPtr) {
	std::string key;
	bool validKey;
	std::cout << "Please provide key value to select school you want to delete." << std::endl;
	std::cout << "Key value must be positive integer.";
	do {
		std::cout << "Please enter key: ";
		std::getline(std::cin, key);
		//lambda function to check for positive number
		auto valid = [=]()->bool {std::regex pattern("^[1-9]\\d*$"); //regular expression for positive number
		return std::regex_match(key, pattern); };
		validKey = valid();
		if (!validKey)
			std::cout << "Invalid input!" << std::endl;
	} while (!validKey); //keep looping to get a valid input

	short finalKey = std::stoi(key); //finally a valid key

	//check if element exist with provided key
	auto it = _schoolPtr->find(finalKey);
	if (it != _schoolPtr->end())
	{
		//delete element with provided key
		_schoolPtr->erase(finalKey);

		// Open the file in truncation mode
		std::ofstream file(SchoolInfo, std::ios::trunc);

		// Check if the file is open
		if (file.is_open()) {
			// Close the file
			file.close();
			for (auto it = _schoolPtr->begin(); it != _schoolPtr->end(); it++)
				updateSchoolFile(it);

			std::cout << "Selected School Data deleted successfully." << std::endl;
		}
		else
			std::cout << "Error opening the file." << std::endl;
	}
	else
		std::cout << "Error cannot find element with provided key." << std::endl;
}

/// <summary>
/// edit school element by key value
/// </summary>
/// <param name="_schoolPtr"></param>
void School::editSchool(const schoolMapPtr& _schoolPtr) {
	std::string key;
	bool validKey;
	std::cout << "Please provide key value to select school you want to edit." << std::endl;
	std::cout << "Key value must be positive integer.";

	do {
		std::cout << "Please enter key: ";
		std::getline(std::cin, key);
		//lambda function to check for positive number
		auto valid = [=]()->bool {std::regex pattern("^[1-9]\\d*$"); //regular expression for positive number
		return std::regex_match(key, pattern); };
		validKey = valid();
		if (!validKey)
			std::cout << "Invalid input!" << std::endl;
	} while (!validKey); //keep looping to get a valid input

	short finalKey = std::stoi(key); //finally a valid key
	auto it = _schoolPtr->find(finalKey);
	if (it != _schoolPtr->end())
	{
		std::string schoolName;
		std::cout << "Please enter school name: ";
		std::getline(std::cin, schoolName);

		/*std::cout << "Please enter School Phone Number: ";
		std::getline(std::cin, schoolArray[2]);

		std::cout << "Please enter School email: ";
		std::getline(std::cin, schoolArray[3]);

		std::cout << "Please enter School website: ";
		std::getline(std::cin, schoolArray[4]);

		std::cout << "Please enter School street number: ";
		std::getline(std::cin, schoolArray[5]);

		std::cout << "Please enter School street name: ";
		std::getline(std::cin, schoolArray[6]);

		std::cout << "Please enter School suburb: ";
		std::getline(std::cin, schoolArray[7]);

		std::cout << "Please enter School city: ";
		std::getline(std::cin, schoolArray[8]);

		std::cout << "Please enter School postcode: ";
		std::getline(std::cin, schoolArray[9]); */

		//edit element with provided key
		it->second.schoolName = schoolName;

		// Open the file in truncation mode
		std::ofstream file(SchoolInfo, std::ios::trunc);

		// Check if the file is open
		if (file.is_open()) {
			// Close the file
			file.close();

			//re-write edited element back to file
			for (auto it = _schoolPtr->begin(); it != _schoolPtr->end(); it++)
				updateSchoolFile(it);

			std::cout << "School Data updated successfully." << std::endl;
		}
		else
			std::cout << "Error opening SchoolInfo.txt." << std::endl;
	}
	else
		std::cout << "Error cannot find school element with provided key." << std::endl;
}

School::Address::Address(const std::string& _streetNumber, const std::string& _streetName, const std::string& _suburb,
	const std::string& _city, const short _postCode)
	: streetNumber(_streetNumber), streetName(_streetName), suburb(_suburb), city(_city), postCode(_postCode) {}

void School::Address::display() const {
	std::cout << "Address: " << std::endl << streetNumber << " " << streetName << std::endl;
	std::cout << suburb << std::endl;
	std::cout << city << std::endl;
	std::cout << postCode << std::endl;
}