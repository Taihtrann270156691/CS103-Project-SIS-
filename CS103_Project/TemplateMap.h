#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "School.h"

const std::string schoolFile = "SchoolInfo.txt";

//template class for map container that hold key, and class object for its element
template <typename TypeKey, typename TypeObj>
class TemplateMap
{
public:
	using tempMap = std::map<TypeKey, TypeObj>; //alias for map
	tempMap myMap;

	TemplateMap() = default;

	void push_back(TypeKey key, TypeObj obj) {
		myMap[key] = obj;
	}

	void fileReading(std::shared_ptr<TemplateMap<short, School>> TempMapSchool) {
		std::ifstream fileExist(schoolFile);
		if (fileExist.is_open()) { //file exist
			std::string line;
			while (std::getline(fileExist, line)) { // Read each line
				splitLine(TempMapSchool, line);
			}
			fileExist.close(); // Close the file
		}
	}

	void splitLine(std::shared_ptr<TemplateMap<short, School>> TempMapSchool, const std::string& line) {
		std::istringstream str(line);
		std::string token;
		std::shared_ptr<std::string[]> schoolInfo(new std::string[8], [](std::string* ptr) { delete[] ptr; });
		std::shared_ptr<School> exp = std::make_shared<School>();

		int i = 0;
		while (std::getline(str, token, '-'))
		{
			schoolInfo[i] = token;
			i++;
		}

		//_ptr->push_back(*exp);
	}

	void addData(const typename tempMap::iterator& it) {
		//auto it = myMap.find(key);
		if (it != myMap.end()) {
			std::ifstream fileExist("SchoolInfo.txt");
			if (fileExist.is_open()) { //file exist
				fileExist.close(); // Close the file

				updateData(it);
			}
			else {
				createNewData(it);
			}
		}
		else {
			std::cout << "Error, cannot find the data with provided key!" << std::endl;
		}
	}

	void updateData(const typename tempMap::iterator& it) {
		// Open the file in append mode
		std::ofstream outFile("SchoolInfo.txt", std::ios::app);

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

	void createNewData(const typename tempMap::iterator& it) {
		// Writing to a file
		std::ofstream outFile("SchoolInfo.txt"); // Create or open a file for writing
		if (outFile.is_open())
		{ // Check if the file is open
			outFile << it->first << "-" << it->second.schoolName
				<< "-" << it->second.phoneNumber << "-" << it->second.email
				<< "-" << it->second.website << "-" << it->second.address->streetNumber
				<< "-" << it->second.address->streetName << "-" << it->second.address->suburb
				<< "-" << it->second.address->city
				<< "-" << it->second.address->postCode << std::endl;

			outFile.close(); // Close the file

			std::cout << "Data has been written to the file name SchoolInfo.txt." << std::endl;
		}
		else
			std::cerr << "Unable to open the file for writing." << std::endl;
	}
};
