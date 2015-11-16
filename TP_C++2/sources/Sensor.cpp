/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 21 octobre 2015
    copyright            : (C) 2015 par Quentin "Johnny" Guye et Louis Mer
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
int* Sensor::GetStats() const 
{
	int* statsTab = new int[4];

	int totalEvents = 0;
	for(int i = 0 ; i < 4 ;i++) {	statsTab[i] = 0;	}

	for(int day = 0 ; day < 7 ;day++)
	{
		totalEvents += filled[day];
		for (int i = 0; i < filled[day] ; i++)
		{
			char TV = eventsPerDay[day][i]->GetTrafficValue(); 
			switch (TV)
			{
				cout << TV << " : " << i << endl;
				case 'V':
					statsTab[0] += 1;
					break;
				case 'J':
					statsTab[1] += 1;
					break;
				case 'R':
					statsTab[2] += 1;
					break;
				case 'N':
					statsTab[3] += 1;
					break;
			}
		}
	}
	for(int i = 0 ; i < 4 ;i++) {	
		statsTab[i] = (totalEvents != 0 ? (statsTab[i] * 100.0 + 0.4999999) / totalEvents : statsTab[i]);	
	}
	statsTab[3] += 100 - statsTab[0] - statsTab[1] - statsTab[2] - statsTab[3];

	return statsTab;
}	

double* Sensor::GetStatsJamADAH(int dayWeek) const
{
	int *statsTab = new int[24];
	int *nbEvents = new int[24];
	double *statsTabRet = new double[24];

	char trafficValue;
	int hour;

	dayWeek--;

	for(int i = 0 ; i < 24 ;i++) 
	{	
		statsTab[i] = 0;
		nbEvents[i] = 0;	
	}

	for(int i = 0; i < this->filled[dayWeek] ; i++)
	{
		trafficValue = this->eventsPerDay[dayWeek][i]->GetTrafficValue();
		hour = this->eventsPerDay[dayWeek][i]->GetHour();
		if( trafficValue == 'R' || trafficValue == 'N')
		{
			statsTab[hour] += 1; 	
		}
		nbEvents[hour] += 1;
	}
	for (int i = 0; i < 24 ; i++)
	{
		statsTabRet[i] = (nbEvents[i] != 0 ? ((double)statsTab[i] * 100 )/ (double)nbEvents[i] : statsTab[i] * 100);
	}

	delete [] statsTab;
	delete [] nbEvents;

	return statsTabRet;
}

double* Sensor::GetStatsForADayWeek(int dayWeek) const
{
	dayWeek--;

	double *statsTab = new double[4];

	for(int i = 0 ; i < 4 ;i++) {	statsTab[i] = 0;	}

	for (int i = 0; i < this->filled[dayWeek] ; i++)
	{
		char TV = this->eventsPerDay[dayWeek][i]->GetTrafficValue(); 
		switch (TV)
		{
			case 'V':
				statsTab[0] += 1;
				break;
			case 'J':
				statsTab[1] += 1;
				break;
			case 'R':
				statsTab[2] += 1;
				break;
			case 'N':
				statsTab[3] += 1;
				break;
		}
	}
	int totalEvents = statsTab[0] + statsTab[1] + statsTab[2] + statsTab[3];
	for(int i = 0; i < 4; i++)
	{
		statsTab[i] = (totalEvents != 0 ? statsTab[i] * 100 / (totalEvents) : 0);
	}
	return statsTab;
}


char* Sensor::OptimizedPath(int dayWeek, const int hourStart, const int hourEnd, const int seg_count)
{
	dayWeek--;
	
	int minutes = (hourEnd - hourStart) * 60 + seg_count * 10;
	//seg_count * 10 permits all the traffic around the end of clock
	char* topoTraf = new char[minutes];
	//each case is a minute with the corresponding trafficValue
	char code[] = {'V','J','R','N'};
	//serv for the convertion number->letter
	int trafficValueMoy = 0;
	
	
	/* Allocation and initialisation of trafByMiute */
	int **trafByMinute = new int*[4];
	//each tab is for a state and each cells in these tabs are for a minute
	for(int i = 0; i < 4; i++)
	{	
		trafByMinute[i] = new int[minutes];	
		for(int j = 0; j < minutes; j++ )
		{	
			trafByMinute[i][j] = 0;	
		}
	}
	
	
	/* Fill trafByMinute with the traf for the dayWeek */
	for(int i = 0; i < this->filled[dayWeek] ; i++)
	{
		if(this->eventsPerDay[dayWeek][i]->GetHour() >= hourStart 
			&& this->eventsPerDay[dayWeek][i]->GetHour() < hourEnd)
		{
			TrafficData * Event = eventsPerDay[dayWeek][i];
			char TV = Event->GetTrafficValue(); 
			int min = Event->GetMinute() + 
				(Event->GetHour() - hourStart) * 60;
				
			switch (TV)
			{
				case 'V':
					trafByMinute[0][min] += 1;
					break;
				case 'J':
					trafByMinute[1][min] += 1;
					break;
				case 'R':
					trafByMinute[2][min] += 1;
					break;
				case 'N':
					trafByMinute[3][min] += 1;
					break;
			}
			
		}
	}
	
	topoTraf[0] = 'N';
	/*If no value of traffic sets for the moment 
	of starting, we statuate for the worst case*/
	
	
	/* Convert trafByMinute[][] into topoTraf[] 
	keeping only the principal state for a minute */
	for(int i = 0; i < minutes; i++)
	{
		/* In case of non-consecutive events, 
		the traficValue for a non-event-assigned minute is 
		the same as the precedent one, else it is the state 
		in more cases that is kept */
		if(trafByMinute[0][i] == 0 
			&& trafByMinute[1][i] == 0 
			&& trafByMinute[2][i] == 0 
			&& trafByMinute[3][i] == 0)
		{
			topoTraf[i] = topoTraf[i - 1];
		}
		else
		{
			for(int j = 0 ; j < 4 ;j++)
			{
				if(trafByMinute[j][i] > trafByMinute[trafficValueMoy][i])
				{
					trafficValueMoy = j;
				}
			}
			
			topoTraf[i] = code[trafficValueMoy];
			trafficValueMoy = 0;
		}
	}
	
	/* Stop leach */
	for(int i = 0; i < 4 ; i++){	delete [] trafByMinute[i];	}
	delete [] trafByMinute;
	return topoTraf;
}



int Sensor::GetID() const
{
	return this->ID;
}



TrafficData *** Sensor::GetEventsPerDay() const
{
	return eventsPerDay;
}



bool Sensor::AddEvent(int year,int month, int day, int hour, int minute, char trafficValue, int dayWeek)
{	
	dayWeek--;
	if(dayWeek > 7 || dayWeek < 1){
		return false;
		cout << "Error : the day needs to be a int between 1 and 7" << endl;	
	}
	
	if(filled[dayWeek] >= allocated[dayWeek])
	{
		//réalloue dynamiquement le tableau 
		TrafficData ** temp = new TrafficData*[(int)(this->allocated[dayWeek] * 1.5)];
		for(int i = 0; i < this->filled[dayWeek] ; i++)
		{
			temp[i] = eventsPerDay[dayWeek][i];
		}
		delete [] eventsPerDay[dayWeek];
		eventsPerDay[dayWeek] = temp;
	}
	eventsPerDay[dayWeek][filled[dayWeek]++] = new TrafficData(year, month, day, hour, minute, trafficValue);

	return true;
}



//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor (int ID)
{
	#ifdef MAP
	    cout << "Appel au constructeur de <Sensor>" << endl;
	#endif
	this->ID = ID;
	
	this->allocated = new int[NB_DAYS_BY_WEEKS];
	this->filled = new int[NB_DAYS_BY_WEEKS];
	eventsPerDay = new TrafficData**[NB_DAYS_BY_WEEKS];
	for(int i = 0; i < NB_DAYS_BY_WEEKS; i++)
	{	
		eventsPerDay[i] = new TrafficData*[BASE_EVENTTAB_SIZE];	
	}

	/* Initialise allocated et filled */
	for(int i = 0 ; i < NB_DAYS_BY_WEEKS; i++)
	{
		this->filled[i] = 0;
		this->allocated[i] = BASE_EVENTTAB_SIZE;
	}

}


Sensor::~Sensor ( )
{
	#ifdef MAP
	    cout << "Appel au destructeur de <Sensor>" << endl;
	#endif
	
	for(int i = 0; i < NB_DAYS_BY_WEEKS; i++)
	{
		for(int j = 0; j < filled[i]; j++)
		{
			delete eventsPerDay[i][j];		
		}
		delete [] eventsPerDay[i];
	}
	
	delete [] eventsPerDay;
	delete [] filled;
	delete [] allocated;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
