#pragma once
#include <vector>

using namespace std;

class Pluviosity {
public:
	Pluviosity();
	Pluviosity(int year);
	bool setPluv(int month, int day, int pluviosity);
	int getPluv(int month, int day) const;
	int maxPluv();
	// other methods
private:
	unsigned int year;			// year that the pluviosity data refers to  
	vector<vector<int> > pluv;	// pluviosity data, indexed by month & day
};

