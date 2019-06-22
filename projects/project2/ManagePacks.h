#pragma once

#include "Agency.h"
#include "Client.h"
#include "Pack.h"

#include <vector>
#include <string>
#include <iostream>

class ManagePacks
{
private:
	bool changesMade;
	vector<Pack> packsVec;

public:
	ManagePacks();
	ManagePacks(Agency agency);

	void MakeUnavailable(int ID);
	void ChangePack(int ID);
	void AddPack();

	void ShowAPack(int ID);
	void ShowAllPacks();
	void ShowNMostVisited(unsigned int N);
	void ShowPacksDates(Date begin, Date end);
	void ShowPacksPlace(string place);
	void ShowPacksDatesPlace(Date begin, Date end, string place);
	
	void BuyAPack(vector<int> info);			// {id, toBuy}

	vector<Pack> getPacks();

	void WriteToFile(Agency agency);

	bool wasChanged();
	void wasChanged(bool opt);

};

