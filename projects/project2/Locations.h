#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Locations
{
private:
	string mainLocal;
	vector<string> subLocals;

public:
	Locations();
	Locations(string main, vector<string> sub);
	Locations(string sites);

	// GET methods
	string getMainLocal();
	vector<string> getSubLocals();
	string getFullLocation();

	// SET methods
	void setMainLocal(string mainLocal);
	void setSubLocals(vector<string> subLocals);
};

