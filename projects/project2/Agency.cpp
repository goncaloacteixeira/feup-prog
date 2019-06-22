#include <fstream>

#include "Agency.h"


vector<int> parse(string str, string delimiter)				// used to parse strings on a delimiter
{																// returns a vector of strings (parsed)
	vector<int> parsed;

	size_t pos = 0;
	string token;

	while ((pos = str.find(delimiter)) != string::npos)
	{
		token = str.substr(0, pos);
		parsed.push_back(stoi(token));
		str.erase(0, pos + delimiter.length());
	}
	parsed.push_back(stoi(str));

	return parsed;
}

//vector<Client> readClients(string clientsFileName)
//{
//	bool errorFound;
//	ifstream clients;
//	string line1, line2;
//	vector<Client> clientsVec;
//
//	clients.open(clientsFileName);
//
//	if (clients.peek() == std::ifstream::traits_type::eof()) return {};		// checks if a file is empty
//
//	if (clients.is_open())
//	{
//		while (getline(clients, line1))
//		{
//			if (line1 == "::::::::::") clientsVec.push_back(Client());
//		}
//		clientsVec.push_back(Client());
//
//		int size = clientsVec.size();
//
//		clients.close();
//		clients.open(clientsFileName);
//
//		vector<vector<string> > info;
//
//		for (int i = 0; i < size; i++)
//		{
//			vector<string> row;
//			while (getline(clients, line2))
//			{
//				if (line2 != "::::::::::") row.push_back(line2);
//				//else if (line2.empty()) row.push_back("none");
//				else break;
//			}
//			if (row.size() == 5) row.push_back("none");
//			info.push_back(row);
//		}
//
//		for (int i = 0; i < size; i++)
//		{
//			clientsVec[i].setName(info[i][0]);
//			clientsVec[i].setVATnumber(stoi(info[i][1]));
//			clientsVec[i].setFamilySize(stoi(info[i][2]));
//			clientsVec[i].setAddress(Address::Address(info[i][3]));
//			if (info[i][5] == "none") 
//			{
//				clientsVec[i].setPackList({});
//				clientsVec[i].setTotalPurchased(stoi(info[i][4]));
//			}
//			else
//			{
//				clientsVec[i].setPackList(parse(info[i][4], " ; "));
//				clientsVec[i].setTotalPurchased(stoi(info[i][5]));
//			}
//		}
//		errorFound = false;
//	}
//	else
//	{
//		cout << "Error 2";
//		errorFound = true;
//	}
//
//	clients.close();
//
//	if (errorFound) exit(EXIT_FAILURE);
//	else return clientsVec;
//}

//vector<Pack> readPacks(string packsFileName)
//{
//	bool errorFound;
//	ifstream travelpacks;
//	string line1, line2;
//	vector<Pack> packsVec;
//
//	travelpacks.open(packsFileName);
//
//	if (travelpacks.peek() == std::ifstream::traits_type::eof()) return {};		// checks if a file is empty
//
//	if (travelpacks.is_open())
//	{
//		while (getline(travelpacks, line1))
//		{
//			if (line1 == "::::::::::") packsVec.push_back(Pack());
//		}
//		packsVec.push_back(Pack());
//
//		int size = packsVec.size();
//
//		travelpacks.close();
//		travelpacks.open(packsFileName);
//
//		vector<vector<string> > info;
//
//		int j = 0;
//
//		for (int i = 0; i < size; i++)
//		{
//			vector<string> row;
//			while (getline(travelpacks, line2))
//			{
//				if (j != 0)
//				{
//					if (line2 != "::::::::::") row.push_back(line2);
//					else break;
//				}
//				j++;
//			}
//			info.push_back(row);
//		}
//
//		for (int i = 0; i < size; i++)
//		{
//			if (stoi(info[i][0]) < 0) packsVec[i].setId(abs(stoi(info[i][0])));
//			else packsVec[i].setId(stoi(info[i][0]));
//
//			packsVec[i].setSites(Locations::Locations(info[i][1]));
//			packsVec[i].setBeginDate(Date::Date(info[i][2]));
//			packsVec[i].setEndDate(Date::Date(info[i][3]));
//			packsVec[i].setPricePerPerson(stoi(info[i][4]));
//			packsVec[i].setMaxTickets(stoi(info[i][5]));
//			packsVec[i].setSoldTickets(stoi(info[i][6]));
//		}
//		errorFound = false;
//	}
//	else
//	{
//		cout << "Error 3";
//		errorFound = true;
//	}
//
//	travelpacks.close();
//
//	if (errorFound) exit(EXIT_FAILURE);
//	else return packsVec;
//}

Agency::Agency(string fileName)
{
	ifstream agency;
	string line;
	vector<string> info;

	agency.open(fileName);

	if (agency.is_open())
	{
		while (getline(agency, line))
		{
			info.push_back(line);
		}

		name = info[0];
		VATnumber = stoi(info[1]);
		URL = info[2];
		address = Address::Address(info[3]);
		clients = info[4];
		packs = info[5];
	}
}

// GET methods
string Agency::getName() const 
{
	return name;
}

unsigned Agency::getVATnumber() const 
{
	return VATnumber;
}

Address Agency::getAddress() const 
{
	return address;
}

string Agency::getURL() const 
{
	return URL;
}

string Agency::getClients() const 
{
	return clients;
}

string Agency::getPacks() const
{
	return packs;
}

// SET Methods
void Agency::setName(string name) 
{
	this->name = name;
}

void Agency::setVATnumber(unsigned VATnumber)
{
	this->VATnumber = VATnumber;
}

void Agency::setAddress(Address address)
{
	this->address = address;
}
void Agency::setURL(string url) 
{
	this->URL = url;
}

void Agency::setClients(string clients)
{
	this->clients = clients;
}

void Agency::setPacks(string packs) 
{
	this->packs = packs;
}
