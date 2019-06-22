#include "Locations.h"

Locations::Locations(string main, vector<string> sub)
{
	mainLocal = main;
	subLocals = sub;
}

vector<string> parse(string str, string delimiter)				// used to parse strings on a delimiter
{																// returns a vector of strings (parsed)
	vector<string> parsed;

	size_t pos = 0;
	string token;

	while ((pos = str.find(delimiter)) != string::npos)
	{
		token = str.substr(0, pos);
		parsed.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	parsed.push_back(str);

	return parsed;
}

Locations::Locations()
{
	mainLocal = "";
	subLocals = {};
}

Locations::Locations(string sites)
{
	size_t pos = sites.find(" - ");
	if (sites.find(" - ") != string::npos || sites.find(" – ") != string::npos)
	{
		mainLocal = sites.substr(0, pos);
		string locations = sites.substr(pos + 3, sites.length() - 1);
		subLocals = parse(locations, ", ");
	}
	else
	{
		mainLocal = sites;
		subLocals = {};
	}
}

// GET methods
string Locations::getMainLocal()
{
	return mainLocal;
}

vector<string> Locations::getSubLocals()
{
	return subLocals;
}

string Locations::getFullLocation()
{
	string dest = mainLocal;

	int ctr = 0;
	if (subLocals.size() > 0)
	{
		dest += " - ";
		for (int j = 0; j < subLocals.size(); j++)
		{
			if (ctr != subLocals.size() - 1) dest += subLocals[j] + ", ";
			else dest += subLocals[j];
			ctr++;
		}
	}
	return dest;
}

// SET methods
void Locations::setMainLocal(string mainLocal)
{
	this->mainLocal = mainLocal;
}

void Locations::setSubLocals(vector<string> subLocals)
{
	this->subLocals = subLocals;
}