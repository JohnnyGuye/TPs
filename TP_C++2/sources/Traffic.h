/*************************************************************************
                           Traffic  -  description
                             -------------------
    début                : 21 octobre 2015
    copyright            : (C) 2015 par Quentin "Johnny" Guye et Louis Mer
*************************************************************************/

//---------- Interface de la classe <Traffic> (fichier Traffic.h) ------
#if ! defined ( TRAFFIC_H )
#define TRAFFIC_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 
#include "Constantes/Constant.h"

//------------------------------------------------------------------ Types 
#include "Sensor.h"

//------------------------------------------------------------------------ 
// <Traffic> represent a city with a bunch of Sensors wich have 
// a lot of events corresponding to the traffic for a specificated time
//------------------------------------------------------------------------ 

class Traffic
{
//----------------------------------------------------------------- PUBLIC

public:
//---------------------------------------------------- Méthodes publiques

	bool GetStatsForASensor(const int numSensor);
	/** @param numSensor : the Sensor for wich you want the stats
	*** @return : true if the Sensor exists 
	**/

	bool GetStatsJamADAH(const int dayWeek);
	/** @param : a day of a week (number between 1 and 7)
	*** @return : true if there is informations for this day
	*** Display the percentage of Jam (R and N) for the dayWeek, hour by hour
	**/

	bool GetStatsForADayWeek(const int dayWeek);
	/** @param : a day of a week (number between 1 and 7)
	*** @return : the stats in percent for all Sensors and for the
	*** whole day [V,J,R,N] (assuming V+J+R+N=100%)
	**/

	bool OptimizedPath(const int dayWeek, const int hourStart, const int hourEnd, const int seg_count, int* tabSeg);
	/** @param dayWeek : a day of a week(number between 1 and 7)
	*** @param hourStart : hour of beginning of the research
	*** @param hourEnd : hour of ending of the research
	*** @return : nothing
	**/

	bool AddEvent(int numSensor, int year,int month, int day, int hour, int minute, char trafficValue, int dayWeek);
	/** @param year : gives the year
	*** @param month : give the month
	*** @param day : gives the day
	*** @param hour : gives the hour
	*** @param minute : gives the minute
	*** @param trafficValue : gives the degree of trafficjam for this Sensor (V,J,R or N)
	*** @return : true if the event is created
	*** Create a new entry in the eventsPerDay tab of TrafficData with these values */

/* ==== Getters === */
	
	Sensor* GetSensor(const int ID);
	/** @return : the Sensor with this ID **/
	
	Traffic ();
	Traffic (int nbSensors);

	virtual ~Traffic ( );
	

//------------------------------------------------------------------ PRIVE 

protected:

Sensor** SensorsTab;
int allocated;
int filled;

};

//----------------------------------------- Types dépendants de <Traffic>

#endif // TRAFFIC_H
