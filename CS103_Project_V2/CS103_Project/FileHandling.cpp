#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "FileHandling.h"
#include "School.h"

const std::string schoolFile = "SchoolInfo.txt";

void fileReading(std::shared_ptr<std::map<short, School>> _schoolPtr) {
	std::ifstream fileExist(schoolFile);
	if (fileExist.is_open()) { //file exist
		std::string line;
		while (std::getline(fileExist, line)) { // Read each line
			splitLine(_schoolPtr, line);
		}
		fileExist.close(); // Close the file
	}
}

void splitLine(std::shared_ptr<std::map<short, School>> _schoolPtr, const std::string& line) {
	std::istringstream str(line);
	std::string token;
	std::shared_ptr<std::string[]> schoolInfo(new std::string[10], [](std::string* ptr) { delete[] ptr; });
	//std::shared_ptr<short[]> schoolAddress(new short[3], [](short* ptr) {delete[] ptr; });
	std::shared_ptr<School> exp = std::make_shared<School>();

	int i = 0;
	while (std::getline(str, token, '-'))
	{
		schoolInfo[i] = token;
		i++;
	}
	std::shared_ptr<School::Address> addressPtr = std::make_shared<School::Address>(schoolInfo[5], schoolInfo[6],
		schoolInfo[7], schoolInfo[8], std::stoi(schoolInfo[9]));
	(*_schoolPtr)[std::stoi(schoolInfo[0])] = School(schoolInfo[1], schoolInfo[2], schoolInfo[3], schoolInfo[4], addressPtr);
	//_ptr->push_back(*exp);
}

void addSchool(const std::map<short, School>::iterator& it) {
	std::ifstream fileExist("SchoolInfo.txt");
	if (fileExist.is_open()) { //file exist
		fileExist.close(); // Close the file

		updateFile(it);
	}
	else {
		createNewFile(it);
	}
}

void createNewFile(const std::map<short, School>::iterator& it) {
	// Writing to a file
	std::ofstream outFile(schoolFile); // Create or open a file for writing
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

void updateFile(const std::map<short, School>::iterator& it) {
	// Open the file in append mode
	std::ofstream outFile(schoolFile, std::ios::app);

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

		std::cout << "Data added to the file successfully." << std::endl;
	}
}