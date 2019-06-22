#include "Address.h"


Address::Address() {
	street = "";
	number = 0;
	floor = "";
	zipCode = "";
	local = "";
}

Address::Address(string addr)
{
	Address address;
	string delimiter = " / ";
	vector<string> info;
	size_t pos = 0;
	string token;

	while ((pos = addr.find(delimiter)) != string::npos)
	{
		token = addr.substr(0, pos);
		info.push_back(token);
		addr.erase(0, pos + delimiter.length());
	}
	info.push_back(addr);

	street = info[0];
	number = stoi(info[1]);
	floor = info[2];
	zipCode = info[3];
	local = info[4];
}

Address::Address(string STREET, unsigned short int NUMBER, string FLOOR, string ZIPCODE, string LOCAL) 
{
	street = STREET;
	number = NUMBER;
	floor = FLOOR;
	zipCode = ZIPCODE;
	local = LOCAL;
}

// GET methods

string Address::getStreet() const {
	return street;
}

unsigned short int Address::getNumber() const {
	return number;
}

string Address::getFloor() const {
	return floor;
}

string Address::getZipCode() const {
	return zipCode;
}

string Address::getLocation() const {
	return local;
}

// metodos SET

void Address::setStreet(string street) {
	this->street = street;
}

void Address::setNumber(unsigned short int doorNumber) {
	this->number = doorNumber;
}

void Address::setFloor(string floor) {
	this->floor = floor;
}

void Address::setZipCode(string postalCode) {
	this->zipCode = postalCode;
}

void Address::setLocation(string location) {
	this->local = location;
}