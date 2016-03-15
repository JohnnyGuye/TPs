/*************************************************************************
                           TrafficData  -  description
                             -------------------
    start                : 21 octobre 2015
    copyright            : (C) 2015 by Quentin "Johnny" Guye and Louis Mer
*************************************************************************/

//---------- Interface of the class <TrafficData> (fichier TrafficData.h) ------
#if ! defined ( TRAFFICDATA_H )
#define TRAFFICDATA_H

//------------------------------------------------------------------------
// Sumary of <TrafficData>
// Keep the informations of an event
//------------------------------------------------------------------------

class TrafficData
{

public:
//---------------------------------------------------------------- Getters

	int GetYear();
	// Return the integer corresponding to the year

	int GetMonth();
	// Return the integer corresponding to the month (between 1 and 12)

	int GetDay();
	// Return the integer corresponding to the day (between 1 and 31)

	int GetHour();
	// Return the integer corresponding to the hour (between 0 and 23)

	int GetMinute();
	// Return the integer corresponding to the minute (between 0 and 59)

	int GetDayWeek();
	// Return the integer corresponding to the day of the week (between 1 and 7)

	char GetTrafficValue();
	// Return the character corresponding to the state of the traffic (either V,J,R or N)
	

//----------------------------------------------------- Constructors et Destructors
	TrafficData(int year,int month, int day, int hour, int minute, char trafficValue );
	/* @param year : gives the year
	** @param month : give the month
	** @param day : gives the day
	** @param hour : gives the hour
	** @param minute : gives the minute
	** @trafficValue : gives the degree of trafficjam for this Sensor (V,J,R or N)
	** Create a new TrafficData and sets all the attributes'values to the corresponding parameter */
	
	TrafficData();
	//Create an empty TrafficData

	virtual ~TrafficData ();
	//The desctructor, there is nothing allocated	

protected:
//----------------------------------------------------------------- Attributs

	int year;
	int month;
	int day;
	int hour;
	int minute;
	int dayWeek;
	char trafficValue;

};

//----------------------------------------- Types dépendants de <TrafficData>

#endif // TRAFFICDATA_H
