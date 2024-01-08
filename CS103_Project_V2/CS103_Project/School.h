#pragma once
#include "SystemFunction.h"
class School {
public:
	using schoolMapPtr = std::shared_ptr<std::map<short, School>>; //type name alias share pointer map container
	using schoolMapIt = std::map<short, School>::iterator;
	class Address {
	public:
		std::string streetNumber;
		std::string streetName;
		std::string suburb;
		std::string city;
		short postCode;

	public:
		// Constructor to initialize the Address object
		Address() = default;
		Address(const std::string& _streetNumber, const std::string& _streetName, const std::string& _suburb,
			const std::string& _city, const short _postCode);
		void display() const;
	};

	// Constructor to initialize the School object
	School() = default;
	School(const std::string& schoolName, const std::string& phoneNumber, const std::string& email,
		const std::string& website, const std::shared_ptr<Address>& address);

	//Member function to read SchoolInfo.txt
	void readSchoolFile(schoolMapPtr& _schoolPtr);

	//Member function to split line in SchoolInfo.txt and fetch them into school map container
	void splitLine(schoolMapPtr& _schoolPtr, const std::string& line);

	//Member function to add school information to SchoolInfo.txt
	void addSchool(const schoolMapIt& it);

	//Member function to create SchoolInfo.txt
	void createNewFile(const schoolMapIt& _school);

	//Member function to update SchoolInfo.txt
	void updateSchoolFile(const schoolMapIt& _school);

	//Member function to delete school information
	void deleteSchool(const schoolMapPtr& _schoolPtr);

	//Member function to update school information
	void editSchool(const schoolMapPtr& _schoolPtr);

	//Member function to display school information
	void display() const;

	//Member function return single iterator of container map
	schoolMapIt userInput_School(std::shared_ptr<std::map<short, School>>& _school);

public:
	std::string schoolName;
	std::string phoneNumber;
	std::string email;
	std::string website;
public:
	std::shared_ptr<Address> address = std::make_shared<Address>();
};
