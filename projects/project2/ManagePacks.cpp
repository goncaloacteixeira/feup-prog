#include "ManagePacks.h"

#include <fstream>
#include <algorithm>

vector<Pack> readPacks(string packsFileName)
{
	bool errorFound;
	ifstream travelpacks;
	string line1, line2;
	vector<Pack> packsVec;

	travelpacks.open(packsFileName);

	if (travelpacks.peek() == std::ifstream::traits_type::eof()) return {};		// checks if a file is empty

	if (travelpacks.is_open())
	{
		while (getline(travelpacks, line1))
		{
			if (line1 == "::::::::::") packsVec.push_back(Pack());
		}
		packsVec.push_back(Pack());

		int size = packsVec.size();

		travelpacks.close();
		travelpacks.open(packsFileName);

		vector<vector<string> > info;

		int j = 0;

		for (int i = 0; i < size; i++)
		{
			vector<string> row;
			while (getline(travelpacks, line2))
			{
				if (j != 0)
				{
					if (line2 != "::::::::::") row.push_back(line2);
					else break;
				}
				j++;
			}
			info.push_back(row);
		}

		for (int i = 0; i < size; i++)
		{
			packsVec[i].setId(stoi(info[i][0]));
			packsVec[i].setSites(Locations::Locations(info[i][1]));
			packsVec[i].setBeginDate(Date::Date(info[i][2]));
			packsVec[i].setEndDate(Date::Date(info[i][3]));
			packsVec[i].setPricePerPerson(stoi(info[i][4]));
			packsVec[i].setMaxTickets(stoi(info[i][5]));
			packsVec[i].setSoldTickets(stoi(info[i][6]));
		}
		errorFound = false;
	}
	else
	{
		cout << "Error 3";
		errorFound = true;
	}

	travelpacks.close();

	if (errorFound) exit(EXIT_FAILURE);
	else return packsVec;
}

bool checkID(int id, vector<Pack> packsVec)
{

	for (int i = 0; i < packsVec.size(); i++)
	{
		if (packsVec[i].getId() == id || id == 0)
		{
			return false;
		}
	}

	return true;
}

bool checkStartDate(string sdate)
{
	Date date = Date::Date(sdate);

	if (date.getMonth() > 12 || date.getMonth() < 1)
	{
	return false;
	}
	if (date.getDay() > 31 || date.getDay() < 1) 
	{ 
		return false;
	}
	return true;
}

bool checkEndDate(string sdate, string edate)
{
	if (!checkStartDate(edate)) return false;

	Date startDate = Date::Date(sdate);
	Date endDate = Date::Date(edate);

	vector<unsigned int> sDateVec = { startDate.getYear() , startDate.getMonth() , startDate.getDay() };
	vector<unsigned int> eDateVec = { endDate.getYear() , endDate.getMonth() , endDate.getDay() };

	if (sDateVec[0] > eDateVec[0]) return false;
	if (sDateVec[0] == eDateVec[0])
	{
		if (sDateVec[1] > eDateVec[1]) return false;
		if (sDateVec[1] == eDateVec[1])
		{
			if (sDateVec[2] > eDateVec[2]) return false;
		}
	}
	return true;
}

void printPacks(vector<Pack> packsVec)
{
	cout << endl;

	printf("%-27s%-50s%-17s%-17s%-10s%-13s%-10s\n", "   ID", "Destination", "Start Date", "End Date", "Price", "Max Tickets", "Sold Tickets");
	cout << "   -----------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < packsVec.size(); i++)
	{
		string destination;
		string startDate, endDate;

		destination = packsVec[i].getSites().getFullLocation();

		startDate = packsVec[i].getBeginDate().getFullDate();
		endDate = packsVec[i].getEndDate().getFullDate();
		
		cout << "   ";

		int alpha = packsVec[i].getMaxTickets() - packsVec[i].getSoldTickets();
		if (alpha > 0) printf("%-12s%-62s%-16s%-17s%-13.02f%-13s%-10s\n", to_string(packsVec[i].getId()).c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), packsVec[i].getPricePerPerson(), to_string(packsVec[i].getMaxTickets()).c_str(), to_string(packsVec[i].getSoldTickets()).c_str());
		else printf("%-12s%-62s%-16s%-17s%-13.02f%-13s%-10s\n", ("-" + to_string(packsVec[i].getId())).c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), packsVec[i].getPricePerPerson(), to_string(packsVec[i].getMaxTickets()).c_str(), to_string(packsVec[i].getSoldTickets()).c_str());
	}

	cout << "\n* The (-) on the ID indicates that the pack is not available anymore.\n\n";
}

bool sortPacks(Pack& A, Pack& B)
{
	return (A.getSoldTickets() > B.getSoldTickets());
}

ManagePacks::ManagePacks(Agency agency)
{
	packsVec = readPacks(agency.getPacks());
}

vector<Pack> ManagePacks::getPacks()
{
	return packsVec;
}

void ManagePacks::AddPack()
{
	system("CLS");
	cout << "\t\tAdd a Pack" << endl;

	string id;
	string destiny;
	string startDate;
	string endDate;
	string pricePerPerson;
	string maxSize;
	string soldpacks;

	bool ctrID = false;
	while (!ctrID)
	{
		cout << "\tID: ";
		getline(cin, id, '\n');
		ctrID = checkID(stoi(id), packsVec);
		if (!ctrID) cout << "\tThat ID is not available.\n";
	}

	cout << "\tDestiny ( 'Main Dest.' - 'Sub Dest.1', 'Sub Dest.2', (...) ) : ";
	getline(cin, destiny, '\n');

	bool ctrSDate = false;
	while (!ctrSDate)
	{
		cout << "\tStart Date (YYYY/MM/DD): ";
		getline(cin, startDate, '\n');
		ctrSDate = checkStartDate(startDate);
		if (!ctrSDate) cout << "\tInsert a correct date (YYYY/MM/DD).\n";
	}

	bool ctrEDate = false;
	while (!ctrEDate)
	{
		cout << "\tEnd Date (YYYY/MM/DD): ";
		getline(cin, endDate, '\n');
		ctrEDate = checkEndDate(startDate, endDate);
		if (!ctrEDate) cout << "\tInsert a valid end date (YYYY/MM/DD).\n";
	}

	cout << "\tPrice per Person: ";
	getline(cin, pricePerPerson, '\n');

	bool ctrMaxTickets = false;
	while (!ctrMaxTickets)
	{
		cout << "\tOriginal tickets number: ";
		getline(cin, maxSize, '\n');
		if (stoi(maxSize) <= 0) ctrMaxTickets = false;
		else ctrMaxTickets = true;
		if (!ctrMaxTickets) cout << "\tInsert a valid Original tickets number.\n";
	}

	Pack newPack;

	newPack.setId(stoi(id));
	newPack.setSites(Locations::Locations(destiny));
	newPack.setBeginDate(Date::Date(startDate));
	newPack.setEndDate(Date::Date(endDate));
	newPack.setPricePerPerson(stod(pricePerPerson));
	newPack.setMaxTickets(stoi(maxSize));
	newPack.setSoldTickets(0);

	packsVec.push_back(newPack);
	
	changesMade = true;
	cout << "\t\tSuccessfully Added\n";
	system("pause");
}

void ManagePacks::ChangePack(int ID)
{
	/*
	alterear as informaçoes de um pack contido nas informaçoes do ficheiro da agencia
	procurando pelo seu ID
	escrever as alterações no ficheiro
	*/

	// Usar esta função no seguimento de uma função de ShowAPack ou ShowAllPacks

	//system("CLS");
	cout << endl;
	
	string choice;

	string id;
	string destiny;
	string startDate;
	string endDate;
	string pricePerPerson;
	string maxSize;
	string soldpacks;

	bool packFound = false;
	int i = 0;
	for (i; i < packsVec.size(); i++)
	{
		if (packsVec[i].getId() == ID)
		{
			packFound = true;
			break;
		}
	}

	if (packFound) {

		cout << "\n\n\t\tChange: \n\n";
		cout << "\t[1] ID" << endl;
		cout << "\t[2] Destiny" << endl;
		cout << "\t[3] Start Date" << endl;
		cout << "\t[4] End Date" << endl;
		cout << "\t[5] Price per Person" << endl;
		cout << "\t[6] Orinal tickets number" << endl;
		cout << "\t[7] Tickets sold" << endl;


		getline(cin, choice, '\n');

		if (choice == "1")
		{
			bool ctrID = false;
			while (!ctrID)
			{
				cout << "\tDesired ID: ";
				getline(cin, id, '\n');
				ctrID = checkID(stoi(id), packsVec);
				if (!ctrID) cout << "\tThat ID is not available.\n";
			}
			packsVec[i].setId(stoi(id));
		}
		if (choice == "2")
		{
			cout << "\tDesired destiny ( 'Main Dest.' - 'Sub Dest.1', 'Sub Dest.2', (...) ) : ";
			getline(cin, destiny, '\n');
			packsVec[i].setSites(Locations::Locations(destiny));
		}
		if (choice == "3")
		{
			bool ctrSDate = false;
			while (!ctrSDate)
			{
				cout << "\tDesired start Date (YYYY/MM/DD): ";
				getline(cin, startDate, '\n');
				ctrSDate = checkStartDate(startDate);
				if (!ctrSDate) cout << "\tInsert a correct date (YYYY/MM/DD).\n";
			}
			packsVec[i].setBeginDate(Date::Date(startDate));
		}
		if (choice == "4")
		{
			bool ctrEDate = false;
			while (!ctrEDate)
			{
				cout << "\tDesired end Date (YYYY/MM/DD): ";
				getline(cin, endDate, '\n');
				ctrEDate = checkEndDate(startDate, endDate);
				if (!ctrEDate) cout << "\tInsert a valid end date (YYYY/MM/DD).\n";
			}
			packsVec[i].setEndDate(Date::Date(endDate));
		}
		if (choice == "5")
		{
			cout << "\tDesired price per Person: ";
			getline(cin, pricePerPerson, '\n');
			packsVec[i].setPricePerPerson(stod(pricePerPerson));
		}
		if (choice == "6")
		{
			cout << "\tDesired original tickets number: ";
			getline(cin, maxSize, '\n');
			packsVec[i].setMaxTickets(stoi(maxSize));
		}
		if (choice == "7")
		{
			cout << "\tDesired sold tickets number: ";
			getline(cin, soldpacks, '\n');
			packsVec[i].setSoldTickets(stoi(soldpacks));
		}

		changesMade = true;
		cout << "\n\tChanges made successfully!" << endl;
	}

	else cout << "\n\n\t\tID NOT FOUND!\n";
	system("pause");
}

void ManagePacks::MakeUnavailable(int ID)
{
	bool packFound = false;
	int i = 0;
	for (i; i < packsVec.size(); i++)
	{
		if (packsVec[i].getId() == ID)
		{
			packFound = true;
			break;
		}
	}

	if (packFound) 
	{
		packsVec[i].setSoldTickets(packsVec[i].getMaxTickets());

		changesMade = true;
		cout << "\n\t Changes made successfully!" << endl;
	}

	else cout << "\n\n\t\tID NOT FOUND!\n";
	system("pause");
}

void ManagePacks::ShowAPack(int ID)
{
	system("CLS");
	cout << endl;

	cout << "\t\tPack INFO\n";

	bool packFound = false;
	int i = 0;
	for (i; i < packsVec.size(); i++)
	{
		if (packsVec[i].getId() == ID)
		{
			packFound = true;
			break;
		}
	}

	if (packFound) {
		cout << "\n\tID: " << packsVec[i].getId() << endl;
		cout << "\tDestiny: " << packsVec[i].getSites().getFullLocation() << endl;
		cout << "\tBegin Date: " << packsVec[i].getBeginDate().getFullDate() << endl;
		cout << "\tEnd Date: " << packsVec[i].getEndDate().getFullDate() << endl;
		cout << "\tPrice per Person: " << packsVec[i].getPricePerPerson() << endl;
		cout << "\tMax tickets: " << packsVec[i].getMaxTickets() << endl;
		cout << "\tSold tickets: " << packsVec[i].getSoldTickets() << endl;

		if (packsVec[i].getMaxTickets() == packsVec[i].getSoldTickets())
		{
			cout << "\n\t  Note: Not available.";
		}
	}

	else cout << "\n\n\t\tPACK NOT FOUND";
}

void ManagePacks::ShowAllPacks()
{
	printPacks(packsVec);
}

void ManagePacks::ShowPacksDates(Date begin, Date end)
{
	vector<Pack> toPrint;

	system("CLS");
	cout << endl;

	vector<unsigned int> startDate = { begin.getYear() , begin.getMonth() , begin.getDay() };
	vector<unsigned int> endDate = { end.getYear() , end.getMonth() , end.getDay() };


	for (int i = 0; i < packsVec.size(); i++)
	{
		if (startDate[0] == packsVec[i].getBeginDate().getYear() && endDate[0] == packsVec[i].getEndDate().getYear())
		{
			if (startDate[1] == packsVec[i].getBeginDate().getMonth() && endDate[1] == packsVec[i].getEndDate().getMonth())
			{
				if (startDate[2] <= packsVec[i].getBeginDate().getDay() && endDate[2] >= packsVec[i].getEndDate().getDay())
				{
					toPrint.push_back(packsVec[i]);
				}
			}
			else if (startDate[1] < packsVec[i].getBeginDate().getMonth() && endDate[1] >= packsVec[i].getEndDate().getMonth())
			{
				toPrint.push_back(packsVec[i]);
			}
			else if (startDate[1] <= packsVec[i].getBeginDate().getMonth() && endDate[1] > packsVec[i].getEndDate().getMonth())
			{
				toPrint.push_back(packsVec[i]);
			}
		}
		else if (startDate[0] < packsVec[i].getBeginDate().getYear() && endDate[0] >= packsVec[i].getEndDate().getYear())
		{
			toPrint.push_back(packsVec[i]);
		}
		else if (startDate[0] <= packsVec[i].getBeginDate().getYear() && endDate[0] > packsVec[i].getEndDate().getYear())
		{
			toPrint.push_back(packsVec[i]);
		}
	}
	printPacks(toPrint);
	system("pause");
}

void ManagePacks::ShowPacksPlace(string place)
{
	vector<Pack> toPrint;

	system("CLS");
	cout << endl;

	for (int i = 0; i < packsVec.size(); i++)
	{
		if (packsVec[i].getSites().getSubLocals().size() == 0)
		{
			if (place == packsVec[i].getSites().getMainLocal())
			{
				toPrint.push_back(packsVec[i]);
			}
		}

		for (int j = 0; j < packsVec[i].getSites().getSubLocals().size(); j++)
		{
			if (place == packsVec[i].getSites().getMainLocal() || place == packsVec[i].getSites().getSubLocals()[j])
			{
				toPrint.push_back(packsVec[i]);
				break;
			}
		}
	}
	printPacks(toPrint);
	system("pause");
}

void ManagePacks::ShowPacksDatesPlace(Date begin, Date end, string place)
{

	vector<Pack> toPrint;

	system("CLS");
	cout << endl;

	vector<unsigned int> startDate = { begin.getYear() , begin.getMonth() , begin.getDay() };
	vector<unsigned int> endDate = { end.getYear() , end.getMonth() , end.getDay() };


	for (int i = 0; i < packsVec.size(); i++)
	{
		if (startDate[0] == packsVec[i].getBeginDate().getYear() && endDate[0] == packsVec[i].getEndDate().getYear())
		{
			if (startDate[1] == packsVec[i].getBeginDate().getMonth() && endDate[1] == packsVec[i].getEndDate().getMonth())
			{
				if (startDate[2] <= packsVec[i].getBeginDate().getDay() && endDate[2] >= packsVec[i].getEndDate().getDay())
				{
					toPrint.push_back(packsVec[i]);
				}
			}
			else if (startDate[1] < packsVec[i].getBeginDate().getMonth() && endDate[1] >= packsVec[i].getEndDate().getMonth())
			{
				toPrint.push_back(packsVec[i]);
			}
			else if (startDate[1] <= packsVec[i].getBeginDate().getMonth() && endDate[1] > packsVec[i].getEndDate().getMonth())
			{
				toPrint.push_back(packsVec[i]);
			}
		}
		else if (startDate[0] < packsVec[i].getBeginDate().getYear() && endDate[0] >= packsVec[i].getEndDate().getYear())
		{
			toPrint.push_back(packsVec[i]);
		}
		else if (startDate[0] <= packsVec[i].getBeginDate().getYear() && endDate[0] > packsVec[i].getEndDate().getYear())
		{
			toPrint.push_back(packsVec[i]);
		}
		system("pause");
	}

	vector<Pack> toPrint2;

	for (int i = 0; i < toPrint.size(); i++)
	{
		if (toPrint[i].getSites().getSubLocals().size() == 0)
		{
			if (place == toPrint[i].getSites().getMainLocal())
			{
				toPrint2.push_back(toPrint[i]);
			}
		}

		for (int j = 0; j < toPrint[i].getSites().getSubLocals().size(); j++)
		{
			if (place == toPrint[i].getSites().getMainLocal() || place == toPrint[i].getSites().getSubLocals()[j])
			{
				toPrint2.push_back(toPrint[i]);
				break;
			}
		}
	}
	printPacks(toPrint2);
	system("pause");
}

void ManagePacks::ShowNMostVisited(unsigned int N)
{
	if (N > packsVec.size())
	{
		cout << "\n\t\tError: N is too high.";
	}
	else
	{
		vector<Pack> temp = packsVec;
		sort(temp.begin(), temp.end(), sortPacks);

		system("CLS");
		cout << endl;

		cout << "\t\t\t\t\t\t\t\tTOP " << N << " PACKS\n" << endl;

		printf("%-27s%-53s%-17s%-17s%-10s%-13s%-10s\n", "       ID", "Destination", "Start Date", "End Date", "Price", "Max Tickets", "Sold Tickets");
		cout << "   -----------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		int j = 1;

		for (int i = 0; i < N; i++)
		{
			string destination;
			string startDate, endDate;


			destination = temp[i].getSites().getFullLocation();

			startDate = temp[i].getBeginDate().getFullDate();
			endDate = temp[i].getEndDate().getFullDate();

			cout << " ";

			int alpha = temp[i].getMaxTickets() - temp[i].getSoldTickets();
			if (alpha > 0) printf("%-5s%-12s%-62s%-16s%-17s%-13.02f%-13s%-10s\n", to_string(j).c_str(), to_string(temp[i].getId()).c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), temp[i].getPricePerPerson(), to_string(temp[i].getMaxTickets()).c_str(), to_string(temp[i].getSoldTickets()).c_str());
			else printf("%-5s%-12s%-62s%-16s%-17s%-13.02f%-13s%-10s\n", to_string(j).c_str(), ("-" + to_string(temp[i].getId())).c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), temp[i].getPricePerPerson(), to_string(temp[i].getMaxTickets()).c_str(), to_string(temp[i].getSoldTickets()).c_str());
			j++;
		}

		cout << "\n* The (-) on the ID indicates that the pack is not available anymore.\n";
	}
}

bool ManagePacks::wasChanged()
{
	if (changesMade)
	{
		return true;
	}
	return false;
}

void ManagePacks::wasChanged(bool opt)
{
	changesMade = opt;
}

void ManagePacks::BuyAPack(vector<int> info)
{
	bool packFound = false;
	int i = 0;
	for (i; i < packsVec.size(); i++)
	{
		if (packsVec[i].getId() == info[0])
		{
			packFound = true;
			break;
		}
	}

	packsVec[i].setSoldTickets(packsVec[i].getSoldTickets() + info[1]);
	changesMade = true;
}