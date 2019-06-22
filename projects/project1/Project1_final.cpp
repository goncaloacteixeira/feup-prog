#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

using namespace std;

int main();

/*		  ----- Error List -----

	Error 1: Agency file couldnt be found.
	Error 2: Clients file couldnt be found.
	Error 3: Packs file couldnt be found.

*/

struct Destiny {
	string place;
	vector<string> locations;
};

struct Address {
	string street;
	string number;
	string floor;
	string zipCode;
	string location;
};

struct Date {
	string day;
	string month;
	string year;
};

struct Agency {
	string name;
	string NIF;
	Address address;
	string URL;
	string packs;
	string clients;
};

struct Client {
	string name;
	string NIF;
	string famNum;
	Address address;
	vector<string> boughtPacks;
	string moneySpent;
};

struct TravelPack {
	string id;
	Destiny destiny;
	Date startDate;
	Date endDate;
	string pricePerPerson;
	string maxSize;
	string soldPacks;
};

// MENUS //

void mainMenu(string agency);
void optClients(string agency);
void optPacks(string agency);

// ----- //


// CHECKING FUNCTIONS //

bool checkNIF(string nif);
bool checkID(string id, string agency);
bool checkStartDate(string sdate);
bool checkEndDate(string sdate, string edate);
bool isInt(string number);

// ----- //

Address parseAddr(string addr)					// used to parse the information on the address line.
{												// returns a struct
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

	address.street = info[0];
	address.number = info[1];
	address.floor = info[2];
	address.zipCode = info[3];
	address.location = info[4];

	return address;
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

Date parseDate(string date)										// used to parse Date; returns a struct Date
{
	vector<string> dateParsed;
	dateParsed = parse(date, "/");
	Date dateNorm;
	dateNorm.day = dateParsed[2];
	dateNorm.month = dateParsed[1];
	dateNorm.year = dateParsed[0];

	return dateNorm;
}

Destiny parseLocations(string loc)				// used to parse locations returns a struct Locations
{
	Destiny dest;
	size_t pos = loc.find(" - ");
	if (loc.find(" - ") != string::npos || loc.find(" – ") != string::npos)
	{
		dest.place = loc.substr(0, pos);
		string locations = loc.substr(pos + 3, loc.length() - 1);
		dest.locations = parse(locations, ", ");
	}
	else
	{
		dest.place = loc;
		dest.locations = {};
	}
	return dest;
}

Agency readAgency(string filename)
{
	bool errorFound;
	ifstream agency;
	string line;
	Agency agc;
	vector<string> info;

	agency.open(filename);

	if (agency.is_open())
	{
		while (getline(agency, line)) info.push_back(line);

		agc.name = info[0];
		agc.NIF = info[1];
		agc.URL = info[2];
		agc.address = parseAddr(info[3]);
		agc.clients = info[4];
		agc.packs = info[5];

		errorFound = false;
	}
	else
	{
		cout << "Error 1";
		errorFound = true;
	}

	if (errorFound) exit(EXIT_FAILURE);
	else return agc;
}

vector<Client> readClients(string agency)
{
	string filename = readAgency(agency).clients;
	bool errorFound;
	ifstream clients;
	string line1, line2;
	vector<Client> clientsVec;

	clients.open(filename);

	if (clients.peek() == std::ifstream::traits_type::eof()) return {};		// checks if a file is empty

	if (clients.is_open())
	{
		while (getline(clients, line1))
		{
			if (line1 == "::::::::::") clientsVec.push_back(Client());
		}
		clientsVec.push_back(Client());

		int size = clientsVec.size();

		clients.close();
		clients.open(filename);

		vector<vector<string> > info;

		for (int i = 0; i < size; i++)
		{
			vector<string> row;
			while (getline(clients, line2))
			{
				if (line2 != "::::::::::") row.push_back(line2);
				//else if (line2.empty()) row.push_back("none");
				else break;
			}
			if (row.size() == 4) row.push_back("none");
			info.push_back(row);
		}

		for (int i = 0; i < size; i++)
		{
			clientsVec[i].name = info[i][0];
			clientsVec[i].NIF = info[i][1];
			clientsVec[i].famNum = info[i][2];
			clientsVec[i].address = parseAddr(info[i][3]);
			if (info[i][4] == "none") clientsVec[i].boughtPacks = {};
			else clientsVec[i].boughtPacks = parse(info[i][4], " ; ");
		}
		errorFound = false;
	}
	else
	{
		cout << "Error 2";
		errorFound = true;
	}

	clients.close();

	if (errorFound) exit(EXIT_FAILURE);
	else return clientsVec;
}

vector<TravelPack> readTPack(string agency)
{
	string filename = readAgency(agency).packs;
	bool errorFound;
	ifstream travelpacks;
	string line1, line2;
	vector<TravelPack> packsVec;

	travelpacks.open(filename);

	if (travelpacks.peek() == std::ifstream::traits_type::eof()) return {};		// checks if a file is empty

	if (travelpacks.is_open())
	{
		while (getline(travelpacks, line1))
		{
			if (line1 == "::::::::::") packsVec.push_back(TravelPack());
		}
		packsVec.push_back(TravelPack());

		int size = packsVec.size();

		travelpacks.close();
		travelpacks.open(filename);

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
			if (stoi(info[i][0]) < 0) packsVec[i].id = to_string(abs(stoi(info[i][0])));
			else packsVec[i].id = info[i][0];

			packsVec[i].destiny = parseLocations(info[i][1]);
			packsVec[i].startDate = parseDate(info[i][2]);
			packsVec[i].endDate = parseDate(info[i][3]);
			packsVec[i].pricePerPerson = info[i][4];
			packsVec[i].maxSize = info[i][5];
			packsVec[i].soldPacks = info[i][6];
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

/* Format functions */

string formatDate(Date date)
{
	string dateNorm;
	dateNorm = date.year + "/" + date.month + "/" + date.day;
	return dateNorm;
}

string formatLoc(Destiny destiny)
{
	string dest = destiny.place;

	int ctr = 0;
	if (destiny.locations.size() > 0)
	{
		dest += " - ";
		for (int j = 0; j < destiny.locations.size(); j++)
		{
			if (ctr != destiny.locations.size() - 1) dest += destiny.locations[j] + ", ";
			else dest += destiny.locations[j];
			ctr++;
		}
	}
	return dest;
}

/* ---------------- */

void addClient(string agency)
{
	system("CLS");
	cout << "\t\tAdd a Client" << endl;

	string name;
	string nif;
	string household;
	string address;
	string boughtpacks;

	cout << "\tName: ";
	getline(cin, name, '\n');

	bool ctrNIF = false;
	while (!ctrNIF)
	{
		cout << "\tNIF: ";
		getline(cin, nif, '\n');
		ctrNIF = checkNIF(nif);
	}

	cout << "\tHousehold: ";
	getline(cin, household, '\n');

	bool ctrAddress = false;
	while (!ctrAddress)
	{
		cout << "\tAddress (street / number / floor(if relevant) / ZipCode / Location): ";
		getline(cin, address, '\n');
		string a;
		bool b = false;
		while (b == false)
		{
			cout << "Is that information correct and as asked? (y/n) ";
			getline(cin, a, '\n');
			if (a == "y" || a == "n") b = true;
		}
		if (a == "y") break;
		else if (a == "n") ctrAddress = false;
	}

	bool crtbPacks = false;
	while (!crtbPacks)
	{
		cout << "\tBought Packs (id1 ; id2 ; id3 ...): ";
		getline(cin, boughtpacks, '\n');
		string a;
		bool b = false;
		while (b == false)
		{
			cout << "Is that information correct and as asked? (y/n) ";
			getline(cin, a, '\n');
			if (a == "y" || a == "n") b = true;
		}
		if (a == "y") break;
		else if (a == "n") crtbPacks = false;
	}

	ofstream clients;
	clients.open(readAgency(agency).clients, ios::ios_base::app);

	int size = readClients(agency).size();

	if (size != 0) clients << "\n::::::::::\n";
	clients << name << endl;
	clients << nif << endl;
	clients << household << endl;
	clients << address << endl;
	clients << boughtpacks;

	clients.close();

	cout << "\t\tSuccessfully Added";

	cout << "\n\n[0] back\n\n";
	string choice;
	getline(cin, choice, '\n');
	if (choice == "0") optClients(agency);
}

void addPack(string agency)
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
		ctrID = checkID(id, agency);
		if (!ctrID) cout << "\tThat ID is not available.\n";
	}

	cout << "\tDestiny: ";
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

	bool ctrTickets = false;
	while (!ctrTickets)
	{
		cout << "\tSold tickets: ";
		getline(cin, soldpacks, '\n');
		if (stoi(soldpacks) > stoi(maxSize) && stoi(soldpacks) >= 0) ctrTickets = false;
		else ctrTickets = true;
		if (!ctrTickets) cout << "\tInsert a valid sold tickets number.\n";
	}

	fstream packs2(readAgency(agency).packs, std::ios::in | std::ios::out);
	packs2 << id;
	packs2.close();

	ofstream packs1;
	packs1.open(readAgency(agency).packs, ios::ios_base::app);

	size_t size = readTPack(agency).size();

	if (size != 0) packs1 << "\n::::::::::\n";
	else packs1 << endl;
	if (stoi(maxSize) - stoi(soldpacks) == 0) packs1 << "-" + id << endl;
	else packs1 << id << endl;
	packs1 << destiny << endl;
	packs1 << startDate << endl;
	packs1 << endDate << endl;
	packs1 << pricePerPerson << endl;
	packs1 << maxSize << endl;
	packs1 << soldpacks;

	packs1.close();

	cout << "\t\tSuccessfully Added";

	cout << "\n\n[0] back\n\n";
	string choice;
	getline(cin, choice, '\n');
	if (choice == "0") optPacks(agency);
}

void writeClients(vector<Client> clientsVec, string agency)
{
	fstream clients(readAgency(agency).clients, std::ofstream::out | std::ofstream::trunc);
	int size = clientsVec.size();
	int control = 0;

	for (int i = 0; i < size; i++)
	{
		clients << clientsVec[i].name << endl;
		clients << clientsVec[i].NIF << endl;
		clients << clientsVec[i].famNum << endl;

		clients << clientsVec[i].address.street << " / ";
		clients << clientsVec[i].address.number << " / ";
		clients << clientsVec[i].address.floor << " / ";
		clients << clientsVec[i].address.zipCode << " / ";
		clients << clientsVec[i].address.location << endl;

		if (clientsVec[i].boughtPacks.size() == 0) clients << endl;
		else
		{
			int ctr = 0;
			for (int j = 0; j < clientsVec[i].boughtPacks.size(); j++)
			{
				if (ctr != clientsVec[i].boughtPacks.size() - 1) clients << clientsVec[i].boughtPacks[j] << " ; ";
				else clients << clientsVec[i].boughtPacks[j] << endl;
				ctr++;
			}
		}

		if (control != size - 1) clients << "::::::::::\n";
		control++;
	}
	clients.close();
}

void writePacks(vector<TravelPack> packsVec, string agency)
{
	fstream packs(readAgency(agency).packs, std::ofstream::out | std::ofstream::trunc);
	int size = packsVec.size();
	int control = 0;

	packs << packsVec[size - 1].id << endl;

	for (int i = 0; i < size; i++)
	{
		int avail = stoi(packsVec[i].maxSize) - stoi(packsVec[i].soldPacks);
		if (avail <= 0) packs << "-" + packsVec[i].id << endl;
		else packs << packsVec[i].id << endl;

		packs << packsVec[i].destiny.place;

		int ctr = 0;
		if (packsVec[i].destiny.locations.size() > 0)
		{
			packs << " - ";
			for (int j = 0; j < packsVec[i].destiny.locations.size(); j++)
			{
				if (ctr != packsVec[i].destiny.locations.size() - 1) packs << packsVec[i].destiny.locations[j] << ", ";
				else packs << packsVec[i].destiny.locations[j] << endl;
				ctr++;
			}
		}
		else packs << endl;

		packs << packsVec[i].startDate.year << "/" << packsVec[i].startDate.month << "/" << packsVec[i].startDate.day << endl;
		packs << packsVec[i].endDate.year << "/" << packsVec[i].endDate.month << "/" << packsVec[i].endDate.day << endl;
		packs << packsVec[i].pricePerPerson << endl;
		packs << packsVec[i].maxSize << endl;
		packs << packsVec[i].soldPacks;

		if (control != size - 1) packs << "\n::::::::::\n";
		control++;
	}
	packs.close();
}

void showClientbyNIF(string agency, string nif)
{
	system("CLS");
	cout << endl;
	vector<Client> clients = readClients(agency);

	int i = 0;
	for (i; i < clients.size(); i++)
	{
		if (clients[i].NIF == nif) break;
	}

	cout << "\n\tName: " << clients[i].name << endl;
	cout << "\tNIF: " << clients[i].NIF << endl;
	cout << "\tHousehold: " << clients[i].famNum << endl;
	cout << "\tAdress: " << clients[i].address.street << ", " << clients[i].address.number << ", " << clients[i].address.floor << ", " << clients[i].address.zipCode << " " << clients[i].address.location << endl << "\t";
	cout << "\tBought packs: ";
	for (int j = 0; j < clients[i].boughtPacks.size(); j++)
	{
		if (j != clients[i].boughtPacks.size() - 1) cout << clients[i].boughtPacks[j] << ", ";
		else cout << clients[i].boughtPacks[j] << endl;
	}
}

void showToManage(string agency)
{
	system("CLS");
	cout << endl;

	vector<Client> clients = readClients(agency);

	printf("%-33s%-8s%-30s%-35s%-10s\n", "   Name", "NIF", "Household", "Address", "Packs Bought");
	cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < clients.size(); i++)
	{
		string address;
		string bpacks;
		for (int j = 0; j < clients[i].boughtPacks.size(); j++)
		{
			if (j != clients[i].boughtPacks.size() - 1) bpacks += clients[i].boughtPacks[j] + ", ";
			else bpacks += clients[i].boughtPacks[j];
		}
		address = clients[i].address.street + ", " + clients[i].address.number + ", " + clients[i].address.floor + ", " + clients[i].address.zipCode + " " + clients[i].address.location;

		printf("%-30s%-15s%-10s%-53s%-20s\n", ("  " + clients[i].name).c_str(), clients[i].NIF.c_str(), clients[i].famNum.c_str(), address.c_str(), bpacks.c_str());
	}
}

void printPacks(vector<TravelPack> packs, string agency);

void manageClients(string agency)
{
	/*
		alterear as informaçoes de um cliente contido nas informaçoes do ficheiro da agencia
		procurando pelo seu NIF
		escrever as alterações no ficheiro
	*/

	system("CLS");
	cout << endl;
	string nif;
	string choice;

	showToManage(agency);

	cout << endl;
	cout << "\t\tManage a Client\n";
	cout << "NIF: ";
	getline(cin, nif, '\n');

	vector<Client> clientsVec = readClients(agency);

	bool clientFound = false;
	int i = 0;
	for (i; i < clientsVec.size(); i++)
	{
		if (clientsVec[i].NIF == nif)
		{
			clientFound = true;
			break;
		}
	}
	if (clientFound)
	{
		showClientbyNIF(agency, nif);

		cout << "\n\tChange: \n\n";
		cout << "\t\t[1] Name" << endl;
		cout << "\t\t[2] NIF" << endl;
		cout << "\t\t[3] Household" << endl;
		cout << "\t\t[4] Address" << endl;
		cout << "\t\t[5] Bought Packs" << endl;

		getline(cin, choice, '\n');

		if (choice == "1")
		{
			cout << "\tDesired Name: ";
			getline(cin, clientsVec[i].name, '\n');
		}
		if (choice == "2")
		{
			bool ctrNIF = false;
			while (!ctrNIF)
			{
				cout << "\tDesired NIF: ";
				getline(cin, nif, '\n');
				ctrNIF = checkNIF(nif);
			}
		}
		if (choice == "3")
		{
			cout << "\tDesired household: ";
			getline(cin, clientsVec[i].famNum, '\n');
		}
		if (choice == "4")
		{
			cout << "\tDesired Address: \n";
			cout << "\t\tStreet: ";
			getline(cin, clientsVec[i].address.street, '\n');
			cout << "\t\tNumber: ";
			getline(cin, clientsVec[i].address.number, '\n');
			cout << "\t\tFloor ( '-' if not aplyable): ";
			getline(cin, clientsVec[i].address.floor, '\n');
			cout << "\t\tZip Code: ";
			getline(cin, clientsVec[i].address.zipCode, '\n');
			cout << "\t\tLocation: ";
			getline(cin, clientsVec[i].address.location, '\n');
		}
		if (choice == "5")
		{
			string boughtpacks;
			bool crtbPacks = false;
			while (!crtbPacks)
			{
				cout << "\tBought Packs (id1 ; id2 ; id3 ...): ";
				getline(cin, boughtpacks, '\n');
				string a;
				bool b = false;
				while (b == false)
				{
					cout << "Is that information correct and as asked? (y/n) ";
					getline(cin, a, '\n');
					if (a == "y" || a == "n") b = true;
				}
				if (a == "y") break;
				else if (a == "n") crtbPacks = false;
			}
			clientsVec[i].boughtPacks = parse(boughtpacks, " ; ");
		}

		writeClients(clientsVec, agency);
		cout << "\n\t Changes made successfully!" << endl;
	}

	else cout << "\n\n\tNIF NOT FOUND!";

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") optClients(agency);
}

void managePacks(string agency)
{
	/*
		alterear as informaçoes de um pack contido nas informaçoes do ficheiro da agencia
		procurando pelo seu ID
		escrever as alterações no ficheiro
	*/

	system("CLS");
	cout << endl;
	string id;
	string choice;

	vector<TravelPack> packsVec = readTPack(agency);

	printPacks(packsVec, agency);
	
	cout << endl;
	cout << "\t\tManage a Pack\n";
	cout << "ID: ";
	getline(cin, id, '\n');

	bool packFound = false;
	int i = 0;
	for (i; i < packsVec.size(); i++)
	{
		if (packsVec[i].id == id)
		{
			packFound = true;
			break;
		}
	}

	if (packFound) {

		cout << "\n\tID: " << packsVec[i].id << endl;
		cout << "\tDestiny: " << formatLoc(packsVec[i].destiny) << endl;
		cout << "\tStart Date: " << formatDate(packsVec[i].startDate) << endl;
		cout << "\tEnd Date: " << formatDate(packsVec[i].endDate) << endl;
		cout << "\tPrice per person: " << packsVec[i].pricePerPerson << endl;
		cout << "\tOriginal Tickets Number: " << packsVec[i].maxSize << endl;
		cout << "\tTickets Sold: " << packsVec[i].soldPacks;

		cout << "\n\nChange: \n\n";
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
			cout << "\tDesired ID: ";
			getline(cin, packsVec[i].id, '\n');
		}
		if (choice == "2")
		{
			cout << "\tDesired Destiny: ";
			string x;
			getline(cin, x, '\n');
			packsVec[i].destiny = parseLocations(x);
		}
		if (choice == "3")
		{
			cout << "\tDesired Start Date: ";
			string date;
			getline(cin, date, '\n');
			packsVec[i].startDate = parseDate(date);
		}
		if (choice == "4")
		{
			cout << "\tDesired End Date: ";
			string date;
			getline(cin, date, '\n');
			packsVec[i].startDate = parseDate(date);
		}
		if (choice == "5")
		{
			cout << "\tDesired price per person: ";
			getline(cin, packsVec[i].pricePerPerson, '\n');
		}
		if (choice == "6")
		{
			cout << "\tDesired original tickets number: ";
			getline(cin, packsVec[i].maxSize, '\n');
		}
		if (choice == "7")
		{
			cout << "\tDesired available tickets: ";
			getline(cin, packsVec[i].soldPacks, '\n');
		}

		writePacks(packsVec, agency);
		cout << "\n\tChanges made successfully!" << endl;
	}

	else cout << "\n\n\t\tID NOT FOUND!";

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") optPacks(agency);
}

void removeClient(string agency)
{
	system("CLS");
	cout << endl;
	vector<Client> clients = readClients(agency);
	int i = 0;
	string nif;

	showToManage(agency);
	
	cout << endl;
	cout << "\t\tRemove a client\n\n";
	cout << "\tNIF: ";
	getline(cin, nif, '\n');

	bool clientFound = false;
	for (i; i < clients.size(); i++)
	{
		if (clients[i].NIF == nif)
		{
			clientFound = true;
			break;
		}
	}

	if (clientFound) {

		clients.erase(clients.begin() + i);
		writeClients(clients, agency);
		cout << "\t\tSuccessfully Removed";
	}
	else cout << "\n\n\t\tNIF NOT FOUND!";

	cout << "\n\n[0] back\n\n";
	string choice;
	getline(cin, choice, '\n');
	if (choice == "0") optClients(agency);
}

void removePack(string agency)
{
	system("CLS");
	cout << endl;

	vector<TravelPack> packs = readTPack(agency);
	int i = 0;
	string id;

	printPacks(packs, agency);

	cout << "\t\tRemove a pack\n\n";
	cout << "\tID: ";
	getline(cin, id, '\n');


	bool packFound = false;
	for (i; i < packs.size(); i++)
	{
		if (packs[i].id == id || packs[i].id == "-" + id)
		{
			packFound = true;
			break;
		}
	}

	if (packFound)
	{
		packs.erase(packs.begin() + i);
		writePacks(packs, agency);
		cout << "\t\tSuccessfully Removed";
	}

	else cout << "\t\tID NOT FOUND!";

	cout << "\n\n[0] back\n\n";
	string choice;
	getline(cin, choice, '\n');
	if (choice == "0") optPacks(agency);
}

void showClient(string agency)
{
	system("CLS");
	cout << endl;

	vector<Client> clients = readClients(agency);
	string nif;

	cout << "\t\tNIF:";
	getline(cin, nif, '\n');

	system("CLS");


	bool clientFount = false;
	int i = 0;
	for (i; i < clients.size(); i++)
	{
		if (clients[i].NIF == nif)
		{
			clientFount = true;
			break;
		}
	}

	if (clientFount) {
		cout << "\n\tName: " << clients[i].name << endl;
		cout << "\tNIF: " << clients[i].NIF << endl;
		cout << "\tHousehold: " << clients[i].famNum << endl;
		cout << "\tAdress: " << clients[i].address.street << ", " << clients[i].address.number << ", " << clients[i].address.floor << ", " << clients[i].address.zipCode << " " << clients[i].address.location << endl;
		cout << "\tBought packs: ";
		for (int j = 0; j < clients[i].boughtPacks.size(); j++)
		{
			if (j != clients[i].boughtPacks.size() - 1) cout << clients[i].boughtPacks[j] << ", ";
			else cout << clients[i].boughtPacks[j] << endl;
		}
	}

	else cout << "\n\n\t\tCLIENT NOT FOUND";

	cout << "\n\n[0] back\n\n";
	string choice;
	getline(cin, choice, '\n');
	if (choice == "0") optClients(agency);
}

void showAllCLients(string agency)
{
	system("CLS");
	cout << endl;

	vector<Client> clients = readClients(agency);

	printf("%-33s%-8s%-30s%-35s%-10s\n", "   Name", "NIF", "Household", "Address", "Packs Bought");
	cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < clients.size(); i++)
	{
		string address;
		string bpacks;
		for (int j = 0; j < clients[i].boughtPacks.size(); j++)
		{
			if (j != clients[i].boughtPacks.size() - 1) bpacks += clients[i].boughtPacks[j] + ", ";
			else bpacks += clients[i].boughtPacks[j];
		}
		address = clients[i].address.street + ", " + clients[i].address.number + ", " + clients[i].address.floor + ", " + clients[i].address.zipCode + " " + clients[i].address.location;

		printf("%-30s%-15s%-10s%-53s%-20s\n", ("  " + clients[i].name).c_str(), clients[i].NIF.c_str(), clients[i].famNum.c_str(), address.c_str(), bpacks.c_str());
	}

	cout << "\n\n[0] back\n\n";
	string choice;
	getline(cin, choice, '\n');
	if (choice == "0") optClients(agency);
}

void printPacks(vector<TravelPack> packs, string agency)
{
	system("CLS");
	cout << endl;

	printf("%-27s%-50s%-17s%-15s%-10s%-13s%-10s\n", "   ID", "Destination", "Start Date", "End Date", "Price", "Max Tickets", "Sold Tickets");
	cout << "   ---------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < packs.size(); i++)
	{
		string destination;
		string startDate, endDate;

		destination = formatLoc(packs[i].destiny);

		startDate = formatDate(packs[i].startDate);
		endDate = formatDate(packs[i].endDate);
		cout << "   ";

		int alpha = stoi(packs[i].maxSize) - stoi(packs[i].soldPacks);
		if (alpha > 0) printf("%-12s%-62s%-16s%-17s%-13s%-13s%-10s\n", packs[i].id.c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), packs[i].pricePerPerson.c_str(), packs[i].maxSize.c_str(), packs[i].soldPacks.c_str());
		else printf("%-12s%-62s%-16s%-17s%-13s%-13s%-10s\n", ("-" + packs[i].id).c_str(), destination.c_str(), startDate.c_str(), endDate.c_str(), packs[i].pricePerPerson.c_str(), packs[i].maxSize.c_str(), packs[i].soldPacks.c_str());
	}

	cout << "\n* The (-) on the ID indicates that the pack is not available anymore";
}

void showAllPacks(string agency)
{
	vector<TravelPack> packs = readTPack(agency);
	printPacks(packs, agency);

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") optPacks(agency);
}

void showPacksDates(string agency)
{
	string a, b;

	vector<TravelPack> packsVec = readTPack(agency);
	vector<TravelPack> toPrint;

	system("CLS");
	cout << endl;

	cout << "\t\tShow Pack between Dates\n";
	
	bool ctrSDate = false;
	while (!ctrSDate)
	{
		cout << "\n\tStart Date (YYYY/MM/DD): ";
		getline(cin, a, '\n');
		ctrSDate = checkStartDate(a);
		if (!ctrSDate) cout << "\n\tInsert a correct date (YYYY/MM/DD).\n";
	}

	bool ctrEDate = false;
	while (!ctrEDate)
	{
		cout << "\n\tEnd Date (YYYY/MM/DD): ";
		getline(cin, b, '\n');
		ctrEDate = checkEndDate(a, b);
		if (!ctrEDate) cout << "\n\tInsert a valid end date (YYYY/MM/DD).\n";
	}

	Date sDate, eDate;
	sDate = parseDate(a);
	eDate = parseDate(b);

	vector<int> startDate = { stoi(sDate.year),stoi(sDate.month),stoi(sDate.day) };
	vector<int> endDate = { stoi(eDate.year),stoi(eDate.month),stoi(eDate.day) };

	for (int i = 0; i < packsVec.size(); i++)
	{
		if (startDate[0] == stoi(packsVec[i].startDate.year) && endDate[0] == stoi(packsVec[i].endDate.year))
		{
			if (startDate[1] == stoi(packsVec[i].startDate.month) && endDate[1] == stoi(packsVec[i].endDate.month))
			{
				if (startDate[2] <= stoi(packsVec[i].startDate.day) && endDate[2] >= stoi(packsVec[i].endDate.day))
				{
					toPrint.push_back(packsVec[i]);
				}
			}
			else if (startDate[1] < stoi(packsVec[i].startDate.month) && endDate[1] >= stoi(packsVec[i].endDate.month))
			{
				toPrint.push_back(packsVec[i]);
			}
			else if (startDate[1] <= stoi(packsVec[i].startDate.month) && endDate[1] > stoi(packsVec[i].endDate.month))
			{
				toPrint.push_back(packsVec[i]);
			}
		}
		else if (startDate[0] < stoi(packsVec[i].startDate.year) && endDate[0] >= stoi(packsVec[i].endDate.year))
		{
			toPrint.push_back(packsVec[i]);
		}
		else if (startDate[0] <= stoi(packsVec[i].startDate.year) && endDate[0] > stoi(packsVec[i].endDate.year))
		{
			toPrint.push_back(packsVec[i]);
		}
	}
	printPacks(toPrint, agency);

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") optPacks(agency);
}

void showPacksLoc(string agency)
{
	string loc;
	vector<TravelPack> packsVec = readTPack(agency);
	vector<TravelPack> toPrint;

	system("CLS");
	cout << endl;

	cout << "\t\tShow Pack for a location\n";
	cout << "\n\tLocation: ";
	getline(cin, loc, '\n');

	for (int i = 0; i < packsVec.size(); i++)
	{
		if (loc == packsVec[i].destiny.place) toPrint.push_back(packsVec[i]);
	}

	printPacks(toPrint, agency);

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") optPacks(agency);
}

void showPacksLocDates(string agency)
{
	string loc, a, b;
	vector<TravelPack> packsVec = readTPack(agency);
	vector<TravelPack> toPrint;

	system("CLS");
	cout << endl;

	cout << "\t\tShow Pack for a location between dates\n";
	cout << "\n\tLocation: ";
	getline(cin, loc, '\n');

	bool ctrSDate = false;
	while (!ctrSDate)
	{
		cout << "\n\tStart Date (YYYY/MM/DD): ";
		getline(cin, a, '\n');
		ctrSDate = checkStartDate(a);
		if (!ctrSDate) cout << "\n\tInsert a correct date (YYYY/MM/DD).\n";
	}

	bool ctrEDate = false;
	while (!ctrEDate)
	{
		cout << "\n\tEnd Date (YYYY/MM/DD): ";
		getline(cin, b, '\n');
		ctrEDate = checkEndDate(a, b);
		if (!ctrEDate) cout << "\n\tInsert a valid end date (YYYY/MM/DD).\n";
	}

	Date sDate, eDate;
	sDate = parseDate(a);
	eDate = parseDate(b);

	vector<int> startDate = { stoi(sDate.year),stoi(sDate.month),stoi(sDate.day) };
	vector<int> endDate = { stoi(eDate.year),stoi(eDate.month),stoi(eDate.day) };

	for (int i = 0; i < packsVec.size(); i++)
	{
		if (startDate[0] == stoi(packsVec[i].startDate.year) && endDate[0] == stoi(packsVec[i].endDate.year))
		{
			if (startDate[1] == stoi(packsVec[i].startDate.month) && endDate[1] == stoi(packsVec[i].endDate.month))
			{
				if (startDate[2] <= stoi(packsVec[i].startDate.day) && endDate[2] >= stoi(packsVec[i].endDate.day))
				{
					toPrint.push_back(packsVec[i]);
				}
			}
			else if (startDate[1] < stoi(packsVec[i].startDate.month) && endDate[1] >= stoi(packsVec[i].endDate.month))
			{
				toPrint.push_back(packsVec[i]);
			}
			else if (startDate[1] <= stoi(packsVec[i].startDate.month) && endDate[1] > stoi(packsVec[i].endDate.month))
			{
				toPrint.push_back(packsVec[i]);
			}
		}
		else if (startDate[0] < stoi(packsVec[i].startDate.year) && endDate[0] >= stoi(packsVec[i].endDate.year))
		{
			toPrint.push_back(packsVec[i]);
		}
		else if (startDate[0] <= stoi(packsVec[i].startDate.year) && endDate[0] > stoi(packsVec[i].endDate.year))
		{
			toPrint.push_back(packsVec[i]);
		}
	}

	vector<TravelPack> toPrint2;

	for (int i = 0; i < toPrint.size(); i++)
	{
		if (loc == toPrint[i].destiny.place) toPrint2.push_back(toPrint[i]);
	}

	printPacks(toPrint2, agency);

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") optPacks(agency);
}

void showPacksSoldtoClient(string agency)
{
	string nif;
	vector<Client> clientsVec = readClients(agency);
	vector<TravelPack> packsVec = readTPack(agency);
	Client target;
	vector<TravelPack> toPrint;

	system("CLS");
	cout << endl;

	cout << "\t\tView Packs sold to a client\n";
	cout << "\n\tClient's NIF: ";
	getline(cin, nif, '\n');

	for (int i = 0; i < clientsVec.size(); i++)
	{
		if (clientsVec[i].NIF == nif)
		{
			target = clientsVec[i];
			break;
		}
	}

	for (int i = 0; i < target.boughtPacks.size(); i++)
	{
		for (int j = 0; j < packsVec.size(); j++)
		{
			if (target.boughtPacks[i] == packsVec[j].id || "-" + target.boughtPacks[i] == packsVec[j].id) toPrint.push_back(packsVec[j]);
		}
	}
	printPacks(toPrint, agency);

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") mainMenu(agency);
}

void showAllPacksSold(string agency)
{
	vector<TravelPack> packsVec = readTPack(agency);
	vector<TravelPack> toPrint;

	for (int i = 0; i < packsVec.size(); i++)
	{
		if (stoi(packsVec[i].soldPacks) > 0) toPrint.push_back(packsVec[i]);
	}

	printPacks(toPrint, agency);

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") mainMenu(agency);
}

void buyPack(string agency)
{
	string nif;
	vector<Client> clientsVec = readClients(agency);
	vector<TravelPack> packsVec = readTPack(agency);
	Client target;

	system("CLS");
	cout << endl;

	cout << "\t\tBuy a pack for a client\n";
	cout << "\n\tClient's NIF: ";
	getline(cin, nif, '\n');

	bool clientFound = false;
	int j = 0;
	for (j; j < clientsVec.size(); j++)
	{
		if (clientsVec[j].NIF == nif)
		{
			target = clientsVec[j];
			clientFound = true;
			break;
		}
	}

	if (clientFound) {

		int toBuy = stoi(target.famNum);

		vector<TravelPack> toPrint;

		for (int i = 0; i < packsVec.size(); i++)
		{
			if (stoi(packsVec[i].maxSize) - stoi(packsVec[i].soldPacks) >= toBuy) toPrint.push_back(packsVec[i]);
		}

		cout << "\n\tAvailable Packs for that client\n\n";
		printPacks(toPrint, agency);
		cout << "\n\n\tChose a pack to buy: ";
		string opt;
		getline(cin, opt, '\n');

		TravelPack targetPack;
		int i = 0;
		for (i; i < packsVec.size(); i++)
		{
			if (packsVec[i].id == opt || "-" + packsVec[i].id == opt) {
				targetPack = packsVec[i];
				break;
			}
		}

		packsVec[i].soldPacks = to_string(stoi(packsVec[i].soldPacks) + toBuy);
		clientsVec[j].boughtPacks.push_back(packsVec[i].id);

		writeClients(clientsVec, agency);
		writePacks(packsVec, agency);

		cout << "\n\tPack Bought!\n";
	}

	else cout << "\n\n\tNIF NOT FOUND!";

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") mainMenu(agency);
}

void agencyIncome(string agency)
{
	system("CLS");
	cout << endl;

	cout << "\t\t---- INCOME ----\n";

	vector<TravelPack> packsVec = readTPack(agency);

	int nPacksSold = 0;
	double income = 0.0;

	for (int i = 0; i < packsVec.size(); i++)
	{
		nPacksSold += stoi(packsVec[i].soldPacks);
		income += stod(packsVec[i].soldPacks) * stod(packsVec[i].pricePerPerson);
	}

	cout << "\n\tTotal Packs Sold: " << nPacksSold << endl;
	cout << "\n\tIncome: " << income << " euro";

	cout << "\n\n[0] back\n\n";
	string choice1;
	getline(cin, choice1, '\n');
	if (choice1 == "0") mainMenu(agency);
}

void optClients(string agency)
{
	system("CLS");
	cout << endl;

	cout << "\t\t---- MANAGE CLIENTS MENU ----\n\n";

	string choice;
	vector<Client> clients = readClients(agency);

	cout << "\t[1] Show a client\n";
	cout << "\t[2] Show all clients\n";
	cout << "\t[3] Add a client\n";
	cout << "\t[4] Remove a client\n";
	cout << "\t[5] Manage a client\n\t";
	cout << "\n\t[6] back";
	cout << "\n\t[0] exit\n\t";


	getline(cin, choice, '\n');

	if (choice == "1")
	{
		showClient(agency);
	}
	if (choice == "2")
	{
		showAllCLients(agency);
	}
	if (choice == "3")
	{
		addClient(agency);
	}
	if (choice == "4")
	{
		removeClient(agency);
	}
	if (choice == "5")
	{
		manageClients(agency);
	}
	if (choice == "6")
	{
		mainMenu(agency);
	}
	if (choice == "0")
	{
		exit(EXIT_SUCCESS);
	}
}

void optPacks(string agency)
{
	system("CLS");
	cout << endl;

	cout << "\t\t---- MANAGE PACKS MENU ----\n\n";

	string choice;
	vector<TravelPack> packs = readTPack(agency);

	cout << "\t[1] Show all* packs\n";
	cout << "\t[2] Show all* packs between dates\n";
	cout << "\t[3] Show all* packs for a destination\n";
	cout << "\t[4] Show all* packs for a destination between dates\n";
	cout << "\t[5] Add a pack\n";
	cout << "\t[6] Remove a pack\n";
	cout << "\t[7] Change a pack\n\t";
	cout << "\n\t[8] back";
	cout << "\n\t[0] exit\n\t";


	getline(cin, choice, '\n');

	if (choice == "1")
	{
		showAllPacks(agency);
	}
	if (choice == "2")
	{
		showPacksDates(agency);
	}
	if (choice == "3")
	{
		showPacksLoc(agency);
	}
	if (choice == "4")
	{
		showPacksLocDates(agency);
	}
	if (choice == "5")
	{
		addPack(agency);
		optPacks(agency);
	}
	if (choice == "6")
	{
		removePack(agency);
	}
	if (choice == "7")
	{
		managePacks(agency);
	}
	if (choice == "8")
	{
		mainMenu(agency);
	}
	if (choice == "0")
	{
		exit(EXIT_SUCCESS);
	}
}

void mainMenu(string agency)
{
	string choice;

	system("CLS");
	cout << endl;

	cout << "\t\t------ " << readAgency(agency).name << " ------" << endl << endl;

	cout << "\tURL: " << readAgency(agency).URL << endl;
	cout << "\tAddress: " << readAgency(agency).address.street << ", " << readAgency(agency).address.number << ", " << readAgency(agency).address.floor << ", " << readAgency(agency).address.zipCode << ", " << readAgency(agency).address.location << endl << endl;

	cout << "\t[1] Manage Clients\n";
	cout << "\t[2] Manage Packs\n";
	cout << "\t[3] Buy a pack for a client\n";
	cout << "\t[4] View sold packs to a client\n";
	cout << "\t[5] View all sold packs\n";
	cout << "\t[6] View income from packs\n\n";

	cout << "\t[0] exit\n\n";

	getline(cin, choice, '\n');

	if (choice == "1") optClients(agency);
	if (choice == "2") optPacks(agency);
	if (choice == "3") buyPack(agency);
	if (choice == "4") showPacksSoldtoClient(agency);
	if (choice == "5") showAllPacksSold(agency);
	if (choice == "6") agencyIncome(agency);
	if (choice == "0") exit(EXIT_SUCCESS);
}

// CHECKING FUNCTIONS //

bool checkNIF(string nif)
{
	if (nif.length() == 9 && isInt(nif)) return true;
	else return false;
}

bool checkID(string id, string agency)
{
	vector<TravelPack> packsVec = readTPack(agency);

	for (int i = 0; i < packsVec.size(); i++)
	{
		if (packsVec[i].id == id) return false;
	}

	return true;
}

bool checkStartDate(string sdate)
{
	Date date = parseDate(sdate);

	if (date.day.length() != 2 || date.month.length() != 2 || date.year.length() != 4) return false;
	if (stoi(date.month) > 12 || stoi(date.month) < 1) return false;
	if (stoi(date.day) > 31 || stoi(date.day) < 1) return false;
	return true;
}

bool checkEndDate(string sdate, string edate)
{
	if (!checkStartDate(edate)) return false;

	Date startDate = parseDate(sdate);
	Date endDate = parseDate(edate);

	vector<int> sDateVec = { stoi(startDate.year) , stoi(startDate.month) , stoi(startDate.day) };
	vector<int> eDateVec = { stoi(endDate.year) , stoi(endDate.month) , stoi(endDate.day) };

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

bool isInt(string number)
{
	if (any_of(begin(number), end(number), ::isalpha)) return false;
	return true;
}

// ------------------ //

int main()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1400, 800, TRUE);

	string agency;

	system("CLS");
	cout << endl;

	cout << "\t ___________________________________________________________\n";
	cout << "\t|                                                           |\n";
	cout << "\t|                     AGENCY MANAGEMENT                     |\n";
	cout << "\t|                         SOFTWARE                          |\n";
	cout << "\t|___________________________________________________________|\n\n";

	cout << "\t\tAgency's file name: ";
	getline(cin, agency, '\n');

	// Testar a validade dos ficheiros

	readAgency(agency);
	readClients(agency);
	readTPack(agency);

	mainMenu(agency);

	return 0;
}