#include "Pack.h"

Pack::Pack()
{
	id = 0;
	sites = Locations::Locations();
	begin = Date::Date();
	end = Date::Date();
	pricePerPerson = 0;
	maxTickets = 0;
	soldTickets = 0;
}

Pack::Pack(int ID, Locations SITES, Date BEGIN, Date END, double PRICEPERPERSON, unsigned MAXTICKETS, unsigned SOLDTICKETS)
{
	id = ID;
	sites = SITES;
	begin = BEGIN;
	end = END;
	pricePerPerson = PRICEPERPERSON;
	maxTickets = MAXTICKETS;
	soldTickets = SOLDTICKETS;
}

// GET methods
int Pack::getId() const
{
	if (id < 0)
	{
		return 0 - id;
	}

	else
	{
		return id;
	}
}

Locations Pack::getSites() const
{
	return sites;
}

Date Pack::getBeginDate() const 
{
	return begin;
}

Date Pack::getEndDate() const 
{
	return end;
}

double Pack::getPricePerPerson() const
{
	return pricePerPerson;
}

unsigned Pack::getMaxTickets() const
{
	return maxTickets;
}

unsigned Pack::getSoldTickets() const 
{
	return soldTickets;
}

// SET methods
void Pack::setId(int id)
{
	this->id = abs(id);
}

void Pack::setSites(Locations sites) 
{
	this->sites = sites;
}

void Pack::setBeginDate(Date begin)
{
	this->begin = begin;
}

void Pack::setEndDate(Date end) 
{
	this->end = end;
}

void Pack::setPricePerPerson(double pricePerPerson)
{
	this->pricePerPerson = pricePerPerson;
}

void Pack::setMaxTickets(unsigned maxTickets)
{
	this->maxTickets = maxTickets;
}

void Pack::setSoldTickets(unsigned soldTickets)
{
	this->soldTickets = soldTickets;
}
