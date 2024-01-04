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
		Address() = default;
		Address(const std::string& _streetNumber, const std::string& _streetName, const std::string& _suburb,
			const std::string& _city, const short _postCode);
		void display() const;
	};

	School() = default;
	School(const std::string& schoolName, const std::string& phoneNumber, const std::string& email,
		const std::string& website, const std::shared_ptr<Address>& address);
	void readSchoolFile(schoolMapPtr& _schoolPtr);
	void splitLine(schoolMapPtr& _schoolPtr, const std::string& line);
	void addSchool(const schoolMapIt& it);
	void createNewFile(const schoolMapIt& _school);
	void updateSchoolFile(const schoolMapIt& _school);
	void deleteSchool(const schoolMapPtr& _schoolPtr);
	void editSchool(const schoolMapPtr& _schoolPtr);
	void display() const;
	schoolMapIt userInput_School(std::shared_ptr<std::map<short, School>>& _school);

public:
	std::string schoolName;
	std::string phoneNumber;
	std::string email;
	std::string website;
public:
	std::shared_ptr<Address> address = std::make_shared<Address>();
};
