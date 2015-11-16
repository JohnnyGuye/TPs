/*************************************************************************
                           Test  -  description
                             -------------------
    début                : 21 octobre 2015
    copyright            : (C) 2015 par Quentin "Johnny" Guye et Louis Mer
*************************************************************************/

//---------- Réalisation de la classe <Trafic> (fichier Traffic.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Traffic.h"
#include "TrafficData.h"
#include "Sensor.h"

//#define MAP
//-------------------------------------------------------Variable globales
static int nbTests = 0;
static int validated = 0;
static int unVerified = 0;

/* ============= Test de Traffic Data ============ */
bool test1()
{
	nbTests++;
	cout << "Test 1" << endl;
  	cout << "Vérification du constructeur de TrafficData : 2015,10,23,8,45,5,R" << endl;
	int y = 2015,
		m = 10,
		d = 23,
		h = 9, 
		min = 45; 
	char traf = 'R';
  	TrafficData T = TrafficData(y,m,d,h,min,traf);
	#ifdef MAP
	  	cout << "Appel des fonctions Get des attributs" << endl;
	  	cout << " Year : " <<  T.GetYear() << endl
	       		<< " Month : " <<  T.GetMonth()<< endl
	       		<< " Day : "   <<  T.GetDay() << endl
	       		<< " Hour : "   <<  T.GetHour() << endl
	       		<< " Minute : "   <<  T.GetMinute() << endl
	       		<< " TrafficValue : "  <<  T.GetTrafficValue() << endl;
	#endif

	if(T.GetYear()  == y && T.GetMonth() == m && T.GetDay() == d && T.GetHour() == h
		&& T.GetMinute() == min && T.GetTrafficValue() == traf)
	{
		cout << "Test validé" << endl << endl;
		return true;
	}
	cout << "Test erroné" << endl << endl;
	return false;

}//Test du constructeur et des Getters de la classe TrafficData

bool test2()
{
	nbTests++;
	cout << "Test 2" << endl;
	cout << "Construction d'un capteur avec un ID" << endl;
	int ID = 42;
  	Sensor C = Sensor(ID);
	#ifdef MAP
	  	cout << "Appel de GetID / Résultat attendu : " << ID << endl;
	  	cout << C.GetID() << endl;
	#endif

	if(C.GetID() == ID)
	{
		cout << "Test validé" << endl << endl;
		return true;
	}
	cout << "Test erroné" << endl << endl;
	return false;
}// Test le constructeur et la fonction GetID de la classe Sensor

bool test3()
{
	nbTests++;
	cout << "Test 3" << endl;
	int y = 2015,
		m = 10,
		d = 23,
		h = 9, 
		min = 45,
		dw = 5; 
	char traf = 'R';
  	cout << "Construction d'un capteur et insertion d'un event" << endl;
  	Sensor C = Sensor(1);
	C.AddEvent(y,m,d,h,min,traf,dw); 
	
	TrafficData * TD = C.GetEventsPerDay()[4][0];
	#ifdef MAP
		cout <<  "Paramètre entrée : 2015,10,23,8,45,R,5" << endl;
		cout << " Year : " << TD->GetYear() << endl
			<< " Month : " << TD->GetMonth()<< endl
			<< " Day : "   << TD->GetDay() << endl
			<< " Hour : "   << TD->GetHour() << endl
			<< " Minute : "   << TD->GetMinute() << endl
			<< " TrafficValue : "  << TD->GetTrafficValue() << endl;
	#endif
	
	if(TD->GetYear()  == y 
		&& TD->GetMonth() == m 
		&& TD->GetDay() == d 
		&& TD->GetHour() == h
		&& TD->GetMinute() == min
		&& TD->GetTrafficValue() == traf)
	{
		cout << "Test validé" << endl << endl;
		return true;
	}
	cout << "Test erroné" << endl << endl;
	return false;
}//Test de la fonction AddEvent et de GetEventsPerDay() de la classe Sensor

bool test4()
{
	nbTests++;
	cout << "Test 4" << endl;
	cout << "Construction d'un capteur et insertion de 4 valeurs" << endl;
	Sensor C = Sensor(1);

	C.AddEvent(2015,10,23,8,45,'R',5);
	C.AddEvent(2015,10,23,9,0,'N',5);
	C.AddEvent(2015,10,23,10,15,'R',5);
	C.AddEvent(2015,10,23,10,30,'R',5);
	C.AddEvent(2015,10,23,11,15,'R',5);
	C.AddEvent(2015,10,23,12,15,'J',5);
	C.AddEvent(2015,10,23,13,15,'J',5);

	int * statsTab = C.GetStats();
	#ifdef MAP
		cout << "Résultat attendu : V 0 % J 0% R 75% N 25 %" << endl;
		cout << "Appel de la fonction GetStats" << endl
			<< "V " << statsTab[0] << endl
			<< "J " << statsTab[1] << endl
			<< "R " << statsTab[2] << endl
			<< "N " << statsTab[3] << endl;
	#endif
	if(statsTab[0] == 0 
		&& statsTab[1] == 28 
		&& statsTab[2] == 57 
		&& statsTab[3] == 15)
	{
		delete [] statsTab;
		cout << "Test validé" << endl << endl;
		return true;
	}
	delete [] statsTab;
	cout << "Test erroné" << endl << endl;
	return false;	 
}//Test de la fonction GetStats de la classe Sensor

bool test5()
{
	nbTests++;
	cout << "Test 5" << endl;
	cout << "Test de la fonction GetStatsJamADAH()" << endl;

	int day = 5;
	Sensor C = Sensor(1);
	
	C.AddEvent(2015,10,23,8,45,'R',day);
	C.AddEvent(2015,10,23,8,0,'N',day);
	C.AddEvent(2015,10,23,10,15,'R',day);
	C.AddEvent(2015,10,23,10,30,'R',day);
	C.AddEvent(2015,10,23,10,15,'V',day);
	C.AddEvent(2015,10,23,13,15,'J',day);
	C.AddEvent(2015,10,24,10,15,'J',6);

	double * statsTabADAH = C.GetStatsJamADAH(day);
	#ifdef MAP
		cout << "Appel de la fonction GetStatsJamADAH" << endl;
		for (int i = 0; i < 24; i++)
		{
			cout << "Jour " << day << " : " << i 
				<< "h, " << statsTabADAH[i] << endl;
		}
	#endif
	
	if((int)statsTabADAH[8] == 100 
		&& (int)statsTabADAH[10] == 66 
		&& (int)statsTabADAH[0] == 0)
	{
		cout << "Test validé" << endl << endl;
		delete [] statsTabADAH;
		return true;
	}
	cout << "Test erroné" << endl << endl;
	delete [] statsTabADAH;
	return false;
}//Test de la fonction GetStatsJamADAH de la classe Sensor

bool test6()
{
	nbTests++;
	cout << "Test 6" << endl;
	cout << "Test de la fonction GetStatsForADayWeek" << endl;
	
	int day = 3;
	Sensor C = Sensor(1);

	C.AddEvent(2015,10,23,8,45,'R',day);
	C.AddEvent(2015,10,23,8,0,'N',day);
	C.AddEvent(2015,10,23,10,15,'R',day);
	C.AddEvent(2015,10,23,10,30,'R',day);
	C.AddEvent(2015,10,23,10,15,'V',day);
	C.AddEvent(2015,10,23,13,15,'R',day);
	C.AddEvent(2015,10,24,10,15,'J',6);

	double * statsTabADW = C.GetStatsForADayWeek(day);

	#ifdef MAP
		cout << "Appel de la fonction GetStatsForADayWeek(int dayWeek)" 
			<< endl;
		cout << "Jour " << day << " : V " << statsTabADW[0] << endl;
		cout << "Jour " << day << " : J " << statsTabADW[1] << endl;
		cout << "Jour " << day << " : R " << statsTabADW[2] << endl;
		cout << "Jour " << day << " : N " << statsTabADW[3] << endl;
	#endif

	if((int)statsTabADW[0] == 16 && (int)statsTabADW[1] == 0 
		&& (int)statsTabADW[2] == 66 &&(int)statsTabADW[3] == 16)
	{
		cout << "Test validé" << endl << endl;
		delete [] statsTabADW;
		return true;
	}
	cout << "Test erroné" << endl << endl;
	delete [] statsTabADW;
	return false;
}//Test de la fonction GetStatsForADayWeek de la classe Sensor

bool test7()
{
	nbTests++;
 	cout << "Test 7" << endl;
	cout << "Test de la fonction OPT" << endl;
	
	int day(4), hourStart(10), hourEnd(11);
	Sensor C = Sensor(5);
	
	C.AddEvent(2015,10,23,8,15,'R',day);
	C.AddEvent(2015,10,23,8,30,'N',day);
	
	C.AddEvent(2015,10,23,10,0,'N',day);
	C.AddEvent(2015,10,23,10,15,'R',day);
	C.AddEvent(2015,10,23,10,30,'V',day);
	C.AddEvent(2015,10,23,10,45,'J',day);
	
	C.AddEvent(2015,10,23,13,15,'R',day);
	
	C.AddEvent(2015,10,24,10,15,'J',6);
	
	char *tabOPT = C.OptimizedPath(day, hourStart, hourEnd, 2);
	#ifdef MAP
		for(int i = 0; i < 60 * (hourEnd - hourStart) + 2 * 10; i++)
		{
			cout << (hourStart + i/60) <<"h" << i 
				<< " " << tabOPT[i] << endl;
		}
	#endif
	
	bool testVal = true;
	for(int i = 0; i < 60 * (hourEnd - hourStart) + 2 * 10; i++)
	{
		if(i < 15)
		{
			if(tabOPT[i] != 'N')
			{
				testVal = false;
			}
		}
		else if(i < 30)
		{
			if(tabOPT[i] != 'R')
			{
				testVal = false;
			}
		}
		else if(i < 45)
		{
			if(tabOPT[i] != 'V')
			{
				testVal = false;
			}
		}
		else if(i < 80)
		{
			if(tabOPT[i] != 'J')
			{
				testVal = false;
			}
		}
	}
	
	if(testVal)
	{
		cout << "Test validé" << endl << endl;
		delete [] tabOPT;
		return true;
	}
	cout << "Test erroné" << endl << endl;
	delete [] tabOPT;
	return false;
}//Test de la fonction OptimizedPath de la classe Sensor

bool test8()
{
	nbTests++;
	cout << "Test 8" << endl;
	cout << "Insertion d'un évènement dans un Traffic" << endl;

	int y = 2015,
		m = 10,
		d = 23,
		h = 9, 
		min = 45,
		Sensor = 10,
		dw = 5; 
	char traf = 'R';

  	Traffic T = Traffic();
  	T.AddEvent(Sensor,y,m,d,h,min,traf,dw); 
	TrafficData *TD = T.GetSensor(Sensor)->GetEventsPerDay()[--dw][0];

	#ifdef MAP
		cout << " Year : " << TD->GetYear() << endl
		       << " Month : " << TD->GetMonth()<< endl
		       << " Day : "   << TD->GetDay() << endl
		       << " Hour : "   << TD->GetHour() << endl
		       << " Minute : "   << TD->GetMinute() << endl
		       << " TrafficValue : "  << TD->GetTrafficValue() << endl;
	#endif
	if(TD->GetYear() == y && TD->GetMonth() == m
		&& TD->GetDay() == d && TD->GetHour() == h
		&& TD->GetMinute() == min && TD->GetTrafficValue() == traf)
	{
		cout << "Test validé" << endl << endl;
		return true;
	}
	cout << "Test erroné" << endl << endl;
	return false;
}//Test du constructeur et des fonctions AddEvent et GetSensor(int ID) de la classe Traffic

bool test9()
{
	unVerified++;
	cout << "Test 9" << endl; 
  	cout << "Test de la fonction GetStats()" << endl;
  	Traffic T = Traffic();
  	T.AddEvent(1,2015,10,23,8,45,'R',5);
  	T.AddEvent(1,2015,10,23,9,0,'N',5);
  	T.AddEvent(1,2015,10,23,9,15,'V',5);
  	T.AddEvent(1,2015,10,23,9,30,'V',5);
	T.AddEvent(1,2015,10,23,9,35,'R',5);
	T.AddEvent(1,2015,10,23,9,38,'R',5);
	T.AddEvent(1,2015,10,23,9,48,'R',5);
	
	T.GetStatsForASensor(1);
	#ifdef MAP
	  	cout << "Résultat attendu : V 0 % J 0% R 75% N 25 %" << endl;
	  	cout << "Appel de la fonction GetStats" << endl;
	#endif
	
	cout << "->>>> VERIFIER SOI MEME LE TEST <<<<-" << endl << endl;
	return false;
}//Test de la fonction GetStats de la classe Traffic

bool test10()
{
	unVerified++;
	cout << "Test 10" << endl;
	cout << "Construction de 2 capteurs du traffic et insertion de valeurs"
		 << endl;
	Traffic T = Traffic();
	T.AddEvent(1,2015,10,23,9,0,'R',5);
	T.AddEvent(1,2015,10,23,9,15,'N',5);
	T.AddEvent(1,2015,10,23,9,30,'J',5);
	T.AddEvent(1,2015,10,23,9,45,'V',5); 
	T.AddEvent(2,2015,10,23,9,0,'J',5);
	T.AddEvent(2,2015,10,23,9,15,'J',5);
	T.AddEvent(2,2015,10,23,9,30,'R',5);
	T.AddEvent(2,2015,10,23,9,45,'V',5);
	T.AddEvent(2,2015,10,23,10,30,'R',5);
	T.AddEvent(2,2015,10,23,11,45,'V',5);
	
	
  	cout << "Résultat attendu : 5 0 0%" << endl 
		<< "5 1 0%" << endl << "..." << endl 
		<< "5 9 38%" << endl
		<< "5 10 50%" << endl 
		<< "..." << endl << "5 23 0%" << endl;
  	cout << "Appel de la fonction GetStatsJamADAH" << endl;
	
  	cout << T.GetStatsJamADAH(5) << endl;
	
	cout << "->>>> VERIFIER SOI MEME LE TEST <<<<-" << endl << endl;
	return false;
}//Test de la fonction GetStatsJamADAH de la classe Traffic

bool test11()
{
	unVerified++;
	cout << "Test 11" << endl;
  	cout << "Test de la fonction GetStatsForADayWeek()" << endl;
  	Traffic T = Traffic();

  	T.AddEvent(1,2015,10,23,9,0,'R',5);
  	T.AddEvent(1,2015,10,23,9,15,'N',5);
  	T.AddEvent(1,2015,10,23,9,30,'J',5);
  	T.AddEvent(1,2015,10,23,9,45,'V',5);
  	T.AddEvent(2,2015,10,23,9,0,'J',5);
  	T.AddEvent(2,2015,10,23,9,15,'J',5);
  	T.AddEvent(2,2015,10,23,9,30,'R',5);
  	T.AddEvent(2,2015,10,23,9,45,'V',5);
  	
	cout << "Résultat attendu : " << endl 
		<< "V 25%" << endl 
		<< "J 37.5%" << endl
		<< "R 25%" << endl
		<< "N 12.5%" << endl;
  	cout << "Appel de la fonction GetStatsForADayWeek" << endl;
  	cout << T.GetStatsForADayWeek(5) << endl;
	
	cout << "->>>> VERIFIER SOI MEME LE TEST <<<<-" << endl << endl;
	return false;
}//Test de la fonction GetStatsForADayWeek de la classe Traffic

bool test12()
{
	unVerified++;
	cout << "Test 12" << endl;
	cout << "Test de la méthode OptimizedPath(params) de Traffic" << endl;
	
	int sensorID[] = {1,2,3};
	Traffic T = Traffic();
	
	T.AddEvent(1,2015,10,23,9,0,'R',5);
  	T.AddEvent(1,2015,10,23,9,15,'V',5);
  	T.AddEvent(1,2015,10,23,9,30,'J',5);
  	T.AddEvent(1,2015,10,23,9,45,'J',5);
  	
  	T.AddEvent(2,2015,10,23,9,0,'R',5);
  	T.AddEvent(2,2015,10,23,9,15,'R',5);
  	T.AddEvent(2,2015,10,23,9,30,'N',5);
  	T.AddEvent(2,2015,10,23,9,45,'R',5);
  	
  	T.AddEvent(3,2015,10,23,9,0,'V',5);
  	T.AddEvent(3,2015,10,23,9,15,'N',5);
  	T.AddEvent(3,2015,10,23,9,30,'J',5);
  	T.AddEvent(3,2015,10,23,9,45,'V',5);
  	
  	T.OptimizedPath(5, 9, 10, 3, sensorID);
	
	cout << "->>>> VERIFIER SOI MEME LE TEST <<<<-" << endl << endl;
	return false;
}//Test de la fonction OptimizedPath pour la classe Traffic

void testTrafficData()
{
	cout << "=== TrafficData ===" << endl;
	validated += (int)test1();
}

void testSensor()
{
	cout << "=== Sensor ===" << endl;
	validated += (int)test2();
	validated += (int)test3();
	validated += (int)test4();
	validated += (int)test5();
	validated += (int)test6();
	validated += (int)test7();
}

void testTraffic()
{
	cout << "=== Traffic ===" << endl;
	validated += (int)test8();
	validated += (int)test9();
	validated += (int)test10();
	validated += (int)test11();
	validated += (int)test12();
}

int main()
{
	cout << endl << "Begin of the test program" << endl;
	testTrafficData();
  	testSensor();
  	testTraffic();
	cout << "Tests validated :" << endl
		<< validated << " out of " << nbTests << endl 
		<< unVerified << " 'up to your consideration' tests. "<< endl;
	cout << "Define MAP for details on the tests" << endl;
	cout << "End of the program" << endl;
}
