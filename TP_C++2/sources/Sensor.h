/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 21 octobre 2015
    copyright            : (C) 2015 par Quentin "Johnny" Guye et Louis Mer
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ------
#if ! defined ( Sensor_H )
#define Sensor_H

//--------------------------------------------------------------Constantes
#include "Constantes/Constant.h"

//------------------------------------------------------------------ Types 
#include "TrafficData.h"
//------------------------------------------------------------------------ 
// Summary of <Sensor>
// This class is supposed to be a collection of TrafficDatas events
// This, is, sparta !!!
//------------------------------------------------------------------------ 

class Sensor
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	int* GetStats() const;
	/* return : the stats of this Sensor activities */ 
	
	double* GetStatsJamADAH(int dayWeek) const;
	/* @param dayWeek : a day of a week (number between 1 and 7)
	** @param statsTab : the tab in wich we stock the stats
	** return : the stats for the day, each cell is the percentage of Jam in an hour	
	*/

	double* GetStatsForADayWeek(int dayWeek) const;
	/* @param : a day of a week (number between 1 and 7)
	** return : the stats in percent for the day [V,J,R,N] (assuming V+J+R+N=100%)
	*/

	char* OptimizedPath(int dayWeek, const int hourStart, const int hourEnd, const int seg_count);
	/* @param dayWeek : a day of a week(number between 1 and 7)
	** @param hourStart : hour of beginning of the research
	** @param hourEnd : hour of ending of the research
	** return : a char* with in each case, the average traffic for this minute
	*/

	bool AddEvent(int year,int month, int day, int hour, int minute, char trafficValue, int dayWeek);
	/* @param year : gives the year
	** @param month : give the month
	** @param day : gives the day
	** @param hour : gives the hour
	** @param minute : gives the minute
	** @trafficValue : gives the degree of trafficjam for this Sensor (V,J,R or N)
	** Create a new entry in the eventsPerDay tab of TrafficDatas with these values */
	
/* === Getters === */

	int GetID() const;
	/* return the ID of the Sensor */

	TrafficData*** GetEventsPerDay() const;
	/* return the tab eventsPerDay of this Sensor */

//-------------------------------------------- Constructeurs - destructeur
    	Sensor ( const Sensor & unSensor );
    	/* No reason to create a copy */

	Sensor (int ID);
	/* @param : the parameter is the ID of the Sensor.
	** It creates a new Sensor empty of events with the proper ID 
	*/

	virtual ~Sensor ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
int ID;
int* filled;
int* allocated;
TrafficData *** eventsPerDay;


};

//----------------------------------------- Types dépendants de <Sensor>

#endif // Sensor_H
