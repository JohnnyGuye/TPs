/*************************************************************************
                           TrafficData  -  description
                             -------------------
    début                : 21 octobre 2015
    copyright            : (C) 2015 par Quentin "Johnny" Guye et Louis Mer
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "TrafficData.h"

//----------------------------------------------------- Méthodes publiques
int TrafficData::GetYear ()
{
	return year;
}

int TrafficData::GetMonth ()
{
	return month;
}

int TrafficData::GetDay ()
{
	return day;
}

int TrafficData::GetHour ()
{
	return hour;
}

int TrafficData::GetMinute ()
{
	return minute;
}

char TrafficData::GetTrafficValue ()
{
	return trafficValue;
}

//-------------------------------------------- Constructeurs - destructeur
TrafficData::TrafficData()
{
	#ifdef MAP
	    cout << "Appel au constructeur de <TrafficData>" << endl;
	#endif
}

TrafficData::TrafficData(int year,int month, int day, int hour, int minute, char trafficValue )
{
	#ifdef MAP
	    cout << "Appel au constructeur de <TrafficData>" << endl;
	#endif
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->trafficValue = trafficValue;
}


TrafficData::~TrafficData ( )
{
	#ifdef MAP
	    cout << "Appel au destructeur de <TrafficData>" << endl;
	#endif
}
