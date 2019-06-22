#include "ManageClients.h"

#include <fstream>
#include <algorithm>

vector<int> parse1(string str, string delimiter)				// used to parse strings on a delimiter
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

vector<Client> readClients(string clientsFileName)
{
	bool errorFound;
	ifstream clients;
	string line1, line2;
	vector<Client> clientsVec;

	clients.open(clientsFileName);

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
		clients.open(clientsFileName);

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
			if (row.size() == 5) row.push_back("none");
			info.push_back(row);
		}

		for (int i = 0; i < size; i++)
		{
			clientsVec[i].setName(info[i][0]);
			clientsVec[i].setVATnumber(stoi(info[i][1]));
			clientsVec[i].setFamilySize(stoi(info[i][2]));
			clientsVec[i].setAddress(Address::Address(info[i][3]));
			if (info[i][5] == "none")
			{
				clientsVec[i].setPackList({});
				clientsVec[i].setTotalPurchased(stoi(info[i][4]));
			}
			else
			{
				clientsVec[i].setPackList(parse1(info[i][4], " ; "));
				clientsVec[i].setTotalPurchased(stoi(info[i][5]));
			}
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

bool isInt(string number)
{
	if (any_of(begin(number), end(number), ::isalpha)) return false;
	return true;
}

bool checkNIF(string nif)
{
	if (nif.length() == 9 && isInt(nif)) return true;
	else return false;
}

ManageClients::ManageClients(Agency agency)
{
	clientsVec = readClients(agency.getClients());
}

void ManageClients::AddClient()
{
	Client newClient;
	system("CLS");
	cout << "\t\tAdd a Client" << endl;

	string name;
	string VAT;
	string famNum;
	string address;

	cout << "\tName: ";
	getline(cin, name, '\n');

	bool ctrNIF = false;
	while (!ctrNIF)
	{
		cout << "\tVAT number: ";
		getline(cin, VAT, '\n');
		ctrNIF = checkNIF(VAT);
	}

	bool ctrFamNum = false;
	while (!ctrFamNum)
	{
		cout << "\tHousehold: ";
		getline(cin, famNum, '\n');
		ctrFamNum = isInt(famNum);
	}

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

	Address addr = Address::Address(address);


	newClient.setName(name);
	newClient.setVATnumber(stoi(VAT));
	newClient.setFamilySize(stoi(famNum));
	newClient.setAddress(addr);
	newClient.setPackList({ 0 });
	newClient.setTotalPurchased(0);

	clientsVec.push_back(newClient);

	cout << "\t\tSuccessfully Added\n";
	system("pause");
	changesMade = true;
}

void ManageClients::ChangeClient(unsigned int VATnumber)
{
	/*
		alterear as informaçoes de um cliente contido nas informaçoes do ficheiro da agencia
		procurando pelo seu NIF
		escrever as alterações no ficheiro
	*/

	// Usar esta função no seguimento de uma função de ShowAClient ou ShowAllClients

	string choice;

	cout << endl;
	cout << "\t\tManage a Client\n";

	bool clientFound = false;
	int i = 0;
	for (i; i < clientsVec.size(); i++)
	{
		if (to_string(clientsVec[i].getVATnumber()) == to_string(VATnumber))
		{
			clientFound = true;
			break;
		}
	}
	if (clientFound)
	{
		cout << "\n\tChange: \n\n";
		cout << "\t\t[1] Name" << endl;
		cout << "\t\t[2] NIF" << endl;
		cout << "\t\t[3] Household" << endl;
		cout << "\t\t[4] Address" << endl;

		getline(cin, choice, '\n');

		if (choice == "1")
		{
			string name;
			cout << "\tDesired Name: ";
			getline(cin, name, '\n');
			clientsVec[i].setName(name);
		}
		if (choice == "2")
		{
			bool ctrNIF = false;
			string VAT;
			while (!ctrNIF)
			{
				cout << "\tDesired VAT number: ";
				getline(cin, VAT, '\n');
				ctrNIF = checkNIF(VAT);
			}
			clientsVec[i].setVATnumber(stoi(VAT));
		}

		if (choice == "3")
		{
			bool ctrFamNum = false;
			string famNum;
			while (!ctrFamNum)
			{
				cout << "\tDesired household: ";
				getline(cin, famNum, '\n');
				ctrFamNum = isInt(famNum);
			}
			clientsVec[i].setFamilySize(stoi(famNum));
		}
		if (choice == "4")
		{
			bool ctrAddress = false;
			string address;
			while (!ctrAddress)
			{
				cout << "\tDesired address (street / number / floor(if relevant) / ZipCode / Location): ";
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
			Address addr = Address::Address(address);
			clientsVec[i].setAddress(addr);
		}
		changesMade = true;
		cout << "\n\t Changes made successfully!\n" << endl;
		system("pause");
	}

	else
	{
		cout << "\n\n\tNIF NOT FOUND!\n";
		system("pause");
	}

}

void ManageClients::RemoveClient(unsigned int VATnumber)
{
	system("CLS");
	cout << endl;

	bool clientFound = false;
	int i = 0;
	for (i; i < clientsVec.size(); i++)
	{
		if (clientsVec[i].getVATnumber() == VATnumber)
		{
			clientFound = true;
			break;
		}
	}

	if (clientFound) {

		clientsVec.erase(clientsVec.begin() + i);

		changesMade = true;

		cout << "\t\tSuccessfully Removed\n";
		system("pause");
	}
	else
	{
		cout << "\n\n\t\tNIF NOT FOUND!\n";
		system("pause");
	}
}

void ManageClients::ShowAllClients()
{
	system("CLS");
	cout << endl;

	printf("%-33s%-8s%-30s%-35s%-19s%-80s\n", "   Name", "NIF", "Household", "Address", "Packs Bought", "Money Spent");
	cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < clientsVec.size(); i++)
	{
		string address;
		string bpacks;

		for (int j = 0; j < clientsVec[i].getPackList().size(); j++)
		{
			if (j != clientsVec[i].getPackList().size() - 1)
			{
				bpacks += to_string(clientsVec[i].getPackList()[j]) + ", ";
			}
			else
			{
				bpacks += to_string(clientsVec[i].getPackList()[j]);
			}
		}
		address = clientsVec[i].getAddress().getStreet() + ", " + to_string(clientsVec[i].getAddress().getNumber()) + ", " + clientsVec[i].getAddress().getFloor() + ", " + clientsVec[i].getAddress().getZipCode() + " " + clientsVec[i].getAddress().getLocation();

		printf("%-30s%-15s%-10s%-53s%-20s%-30s\n", ("  " + clientsVec[i].getName()).c_str(), to_string(clientsVec[i].getVATnumber()).c_str(), to_string(clientsVec[i].getFamilySize()).c_str(), address.c_str(), bpacks.c_str(), to_string(clientsVec[i].getTotalPurchased()).c_str());
	}

	cout << "\n*ID 0 (zero) means the client has no bought packs yet.\n";
}

void ManageClients::ShowAClient(unsigned int VATnumber)
{

	system("CLS");

	cout << "\n\t\tClient INFO\n";

	bool clientFound = false;
	int i = 0;
	for (i; i < clientsVec.size(); i++)
	{
		if (clientsVec[i].getVATnumber() == VATnumber)
		{
			clientFound = true;
			break;
		}
	}

	if (clientFound) {
		cout << "\n\tName: " << clientsVec[i].getName() << endl;
		cout << "\tVAT number: " << clientsVec[i].getVATnumber() << endl;
		cout << "\tHousehold: " << clientsVec[i].getFamilySize() << endl;
		cout << "\tAdress: " << clientsVec[i].getAddress().getStreet() << ", " << clientsVec[i].getAddress().getNumber() << ", " << clientsVec[i].getAddress().getFloor() << ", " << clientsVec[i].getAddress().getZipCode() << " " << clientsVec[i].getAddress().getLocation() << endl;
		cout << "\tBought packs: ";
		for (int j = 0; j < clientsVec[i].getPackList().size(); j++)
		{
			if (j != clientsVec[i].getPackList().size() - 1)
			{
				cout << clientsVec[i].getPackList()[j] << ", ";
			}
			else 
			{
				cout << clientsVec[i].getPackList()[j] << endl;
			}
		}
		cout << "\tMoney Spent: " << clientsVec[i].getTotalPurchased() << endl;
	}

	else cout << "\n\n\t\tCLIENT NOT FOUND";
}

void printPacks2(vector<Pack> packsVec)
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

vector<int> ManageClients::BuyAPack(unsigned int VATnumber, ManagePacks& packs)
{
	Client target;
	bool clientFound = false;
	int j = 0;
	for (j; j < clientsVec.size(); j++)
	{
		if (clientsVec[j].getVATnumber() == VATnumber)
		{
			target = clientsVec[j];
			clientFound = true;
			break;
		}
	}

	if (clientFound) {

		int toBuy = target.getFamilySize();

		vector<Pack> toPrint;

		for (int i = 0; i < packs.getPacks().size(); i++)
		{
			if (packs.getPacks()[i].getMaxTickets() - packs.getPacks()[i].getSoldTickets() >= toBuy) toPrint.push_back(packs.getPacks()[i]);
		}

		cout << "\n\t ----> Available Packs for " << target.getName() << endl << endl;
		printPacks2(toPrint);
		cout << "\n\n\tChose a pack to buy: ";
		string opt;
		getline(cin, opt, '\n');

		Pack targetPack;
		int i = 0;
		for (i; i < packs.getPacks().size(); i++)
		{
			if (packs.getPacks()[i].getId() == stoi(opt) || "-" + to_string(packs.getPacks()[i].getId()) == opt) {
				targetPack = packs.getPacks()[i];
				break;
			}
		}

		vector<int> toAdd = clientsVec[j].getPackList();
		if (toAdd[0] == 0)
		{
			clientsVec[j].setPackList({ packs.getPacks()[i].getId() });
		}
		else
		{ 
			toAdd.push_back(packs.getPacks()[i].getId()); 
			clientsVec[j].setPackList(toAdd);
		}
				

		clientsVec[j].setTotalPurchased(clientsVec[j].getTotalPurchased() + toBuy * targetPack.getPricePerPerson());
		packs.wasChanged(true);
		changesMade = true;

		cout << "\n\tPack Bought!\n";
		return { packs.getPacks()[i].getId(), toBuy };
	}
	else
	{
		cout << "\n\n\t\tNIF NOT FOUND!\n";
		return { 0,0 };
	}
}

bool ManageClients::wasChanged()
{
	if (changesMade)
	{
		return true;
	}
	return false;
}

void ManageClients::wasChanged(bool opt)
{
	changesMade = opt;
}

vector<Client> ManageClients::getClients()
{
	return clientsVec;
}