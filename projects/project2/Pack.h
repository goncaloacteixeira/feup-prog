#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Date.h"
#include "Locations.h"

using namespace std;

class Pack
{
private:
	int id;
	Locations sites;
	Date begin;
	Date end;
	double pricePerPerson;
	unsigned maxTickets;
	unsigned soldTickets;

public:
	Pack();
	Pack(int ID, Locations SITES, Date BEGIN, Date END, double PRICEPERPERSON, unsigned MAXTICKETS, unsigned SOLDTICKETS);

	// GET methods
	int getId() const;
	Locations getSites() const;
	Date getBeginDate() const;
	Date getEndDate() const;
	double getPricePerPerson() const;
	unsigned getMaxTickets() const;
	unsigned getSoldTickets() const;

	// SET methods
	void setId(int id);		// to set to negative if sold out
	void setSites(Locations sites);
	void setBeginDate(Date begin);
	void setEndDate(Date end);
	void setPricePerPerson(double pricePerPerson);
	void setMaxTickets(unsigned maxTickets);
	void setSoldTickets(unsigned soldTickets);

};

