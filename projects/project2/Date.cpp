#include "Date.h"

Date::Date() {
	year = 0;
	month = 0;
	day = 0;
}

vector<string> parse(string str)				
{	
	vector<string> parsed;

	size_t pos = 0;
	string token;

	while ((pos = str.find("/")) != string::npos)
	{
		token = str.substr(0, pos);
		parsed.push_back(token);
		str.erase(0, pos + 1);
	}
	parsed.push_back(str);

	return parsed;
}

Date::Date(string date)
{
	vector<string> vecDate = parse(date);
	year = stoi(vecDate[0]);
	month = stoi(vecDate[1]);
	day = stoi(vecDate[2]);
}

Date::Date(unsigned YEAR, unsigned short MONTH, unsigned short DAY)
{
	year = YEAR;
	month = MONTH;
	day = DAY;
}

// GET methods

unsigned short Date::getDay() const 
{
	return day;
}

unsigned short Date::getMonth() const 
{
	return month;
}

unsigned Date::getYear() const
{
	return year;
}

string Date::getFullDate()
{
	stringstream dateNorm;
	dateNorm << year << "/";
	dateNorm << setfill('0') << setw(2) << month << "/";
	dateNorm << setfill('0') << setw(2) << day;

	return dateNorm.str();
}

// SET methods

void Date::setDay(unsigned short day) 
{
	this->day = day;
}
void Date::setMonth(unsigned short month) 
{
	this->month = month;
}

void Date::setYear(unsigned year) 
{
	this->year = year;
}