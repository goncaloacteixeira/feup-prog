#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

class Date
{
private:
	unsigned short day;
	unsigned short month;
	unsigned year;

public:
	Date();
	Date(string date);
	Date(unsigned YEAR, unsigned short MONTH, unsigned short DAY);

	// GET methods
	unsigned short getDay() const;
	unsigned short getMonth() const;
	unsigned getYear() const;
	string getFullDate();


	// SET methods
	void setDay(unsigned short day);
	void setMonth(unsigned short month);
	void setYear(unsigned year);

};

