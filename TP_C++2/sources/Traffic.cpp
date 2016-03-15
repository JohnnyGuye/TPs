/*************************************************************************
                           Traffic  -  description
                             -------------------
    début                : 21 octobre 2015
    copyright            : (C) 2015 par Quentin "Johnny" Guye et Louis Mer
*************************************************************************/

//---------- Réalisation de la classe <Traffic> (fichier Traffic.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Traffic.h"

//------------------------------------------------------------- Constantes
#include "Constantes/Constant.h"

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
bool Traffic::GetStatsForASensor(const int numSensor)
{
	int i = 0 ;
	while( (i < this->filled ) && (this->SensorsTab[i]->GetID() != numSensor)){	i++;	}
	if(i == this->filled)
	{
		cout << "No Sensors with this given ID" << endl;
		return false;
	}
	int * tab = SensorsTab[i]->GetStats();
	
	cout << "V " << tab[0] << "%\r\n";
	cout << "J " << tab[1] << "%\r\n";
	cout << "R " << tab[2] << "%\r\n";
	cout << "N " << tab[3] << "%\r\n";
	delete [] tab;
	return true;
}

bool Traffic::GetStatsJamADAH(const int dayWeek)
{
	double * statsTab = new double[24];
	double * statsSensor;

	for(int i = 0; i < 24 ; i++) {	statsTab[i] = 0;	}

	for(int i = 0; i < this->filled ; i++)
	{
		statsSensor = SensorsTab[i]->GetStatsJamADAH(dayWeek);//this line create a new allocation and needs to be deleted for each loop
		for(int h = 0 ; h < 24 ; h++)
		{
			statsTab[h] += statsSensor[h];
		}
		delete [] statsSensor;
	}
	for(int i = 0; i < 24; i++)
	{
		cout << dayWeek << " " << i << " " << (statsTab[i] / (double)this->filled) << "%\r\n";
	}
	delete [] statsTab;
	
	return true;
}

bool Traffic::GetStatsForADayWeek(const int dayWeek)
{
	if(dayWeek > 7 || dayWeek < 1)
	{
		return false;
	}
	double * statsTab = new double[4];
	double * statsSensor;

	for(int i = 0; i < 4 ; i++) {	statsTab[i] = 0;	}

	for(int i = 0; i < this->filled ; i++)
	{
		statsSensor = SensorsTab[i]->GetStatsForADayWeek(dayWeek);
		//this line create a new allocation and needs to be deleted for each loop
		for(int t = 0 ; t < 4 ; t++)
		{
			statsTab[t] += statsSensor[t];
		}
		delete [] statsSensor;
	}
	for(int t = 0 ; t < 4 ; t++)
	{
		statsTab[t] /= this->filled;
	}
	cout << "V " << (int)(statsTab[0]) << "%" << endl ;
	cout << "J " << (int)(statsTab[1]) << "%" << endl ;
	cout << "R " << (int)(statsTab[2]) << "%" << endl ;
	cout << "N " << 100 - (int)(statsTab[0]) - 
		(int)(statsTab[1]) - (int)(statsTab[2]) << "%" << endl ;
	
	delete [] statsTab;
	return true;
}

bool Traffic::OptimizedPath(const int dayWeek, const int hourStart, const int hourEnd, const int seg_count, int* tabSeg)
{
	if(hourStart < hourEnd)
	{
		const int MINUTE_MAX = (hourEnd - hourStart) * 60;
		/* Retrieve all the usefull datas */
		Sensor * currentSensor;
		char ** TrafficPerSensor = new char*[seg_count];
		int inexistantSensor = 0;
		
		for(int i = 0; i < seg_count; i++)
		{
			currentSensor = this->GetSensor(tabSeg[i]);
			if(currentSensor->GetID() == -1)
			{
				delete currentSensor;
				inexistantSensor++;
			}
			else
			{
				TrafficPerSensor[i - inexistantSensor] =
				 currentSensor->OptimizedPath(dayWeek, 
				 	hourStart, 
				 	hourEnd, seg_count);
			}
		}
		
		/* Algorithme */
		int 	bestTime = seg_count * 10,	//stock the best time
			bestMinute = 0;	
			//stock the best minute (ranging from 0 to (hourEnd - hourStart) * 60
		int 	time = 0;	//stock the duration in minute
		
		for(int minStart = 0; minStart < MINUTE_MAX ; minStart++)
		{
			time = 0;
			for(int i = 0 ; i < seg_count - inexistantSensor ; i++)
			{
				switch (TrafficPerSensor[i][minStart + time])
				{
					case 'V':
						time += 1;
						break;
					case 'J':
						time += 2;
						break;
					case 'R':
						time += 4;
						break;
					case 'N':
						time += 10;
						break;
				}
			}
			if(bestTime > time && time != 0)
			{
				bestTime = time;
				bestMinute = minStart;
			}
		}
		
		/* Display */
		cout << dayWeek << " " << ((bestMinute / 60) + hourStart)
			<< " " << (bestMinute % 60) << " " << bestTime << endl;
		
		/* Frees */
		for(int i = 0; i < seg_count ; i++){	delete [] TrafficPerSensor[i];	}
		delete [] TrafficPerSensor;
		return true;	
	}
	return false;
}

bool Traffic::AddEvent(int numSensor, int year,int month, int day, int hour, int minute, char trafficValue, int dayWeek)
{
	int i = 0 ;
	while( (i < this->filled ) && (this->SensorsTab[i]->GetID() != numSensor)){	i++;	}
	if(i == this->filled)
	{
		
		this->SensorsTab[i] = new Sensor(numSensor);
		this->filled++;
	}
	return SensorsTab[i]->AddEvent(year,month,day,hour,minute,trafficValue,dayWeek);
}

Sensor* Traffic::GetSensor(const int ID)
{
	int i = 0 ;
	while( (i < this->filled ) && (this->SensorsTab[i]->GetID() != ID)){	i++;	}
	if(this->SensorsTab[i]->GetID() != ID)
	{
		cout << "No Sensors with this given ID" << endl;
		return new Sensor(-1);
	}
	return SensorsTab[i];	
}
//-------------------------------------------- Constructeurs - destructeur
Traffic::Traffic ( )
{
	#ifdef MAP
	    cout << "Appel au constructeur de <Traffic>" << endl;
	#endif
	SensorsTab = new Sensor*[NB_SENSORS_MAX];
	filled = 0;
	allocated = NB_SENSORS_MAX;
}

Traffic::Traffic(int nbSensors)
{
	#ifdef MAP
	    cout << "Appel au constructeur de <Traffic>" << endl;
	#endif
	SensorsTab = new Sensor*[nbSensors];
	filled = 0;
	allocated = nbSensors;
}

Traffic::~Traffic ( )
{
	#ifdef MAP
	    cout << "Appel au destructeur de <Traffic>" << endl;
	#endif
	for(int i = 0; i < this->filled ; i++)
	{
		delete SensorsTab[i];
	}
	delete [] SensorsTab;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
