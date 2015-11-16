#include <iostream>
#include <string>

#include "TrafficData.h"
#include "Sensor.h"
#include "Traffic.h"

//#define MAP

using namespace std;

int main()
{
	#ifdef MAP
		cout << "==== Beginning of TrafficJam ====" << endl;
  	#endif

  	string in = "START";//stock the command
  
  	/* ADD variables */
  	int 	id, 	//stock the ID of the Sensor
  		y,  	//stock the year
  		mo, 	//stock the month
  		d, 	//stock the day
  		h, 	//stock the hour
  		mi, 	//stock the minute
  		w;	//stock the day of the week (ranging from 1 to 7)
  	char t;		//stock the value of the traffic
  	
  	/* OPT variables */
  	int 	hourStart, 	//stock the starting hour for OPT
  		hourEnd,	//stock the ending hour for OPT
  		seg;		//the number of segments
  	int* segments;		//stock the id of the <seg> segments
  	
  	Traffic* T = new Traffic();
  	//The traffic object on wich we execute methods
  	
  	do
    	{
      		cin >> in;
      		if(in == "ADD")
		{
	  		cin >> id >> y >> mo >> d >> h >> mi >> w >> t;
	  		T->AddEvent(id,y,mo,d,h,mi,t,w);
	  		#ifdef MAP
		  		int * tab = T->GetSensor(id)->GetStats();
		  		cout << in << " " 
		  			<< id << " " 
		  			<< y << " " 
		  			<< mo << " " 
		  			<< d << " " 
		  			<< h << " " 
		  			<< mi << " " 
		  			<< t << " " 
		  			<< w << " " << endl;
				cout << tab[0] << endl;
				cout << tab[1] << endl;
				cout << tab[2] << endl;
				cout << tab[3] << endl;
				
				delete [] tab;
		  		cout << "fin fonction ADD" << endl;
		  	#endif
	  	}
	  	else if(in == "STATS_C")
	  	{
	  		cin >> w;
	  		T->GetStatsForASensor(w);
	  		#ifdef MAP
		  		cout << in << " " << w << " " << endl;
		  		cout << "fin fonction STATS_C-" << endl;
			#endif
	  	}
	      	else if(in == "STATS_D7")
		{
		  	cin >> w;
		  	T->GetStatsForADayWeek(w);
		  	#ifdef MAP
		  		cout << in << " " << w << " " << endl;
		  		cout << "fin fonction STATS_D7-" << endl;
			#endif
		}
	      	else if(in == "JAM_DH")
		{
		  	cin >> w;
		  	T->GetStatsJamADAH(w);
		  	#ifdef MAP
		  		cout << "-" << in << " " << w << " " << endl;
		  		cout << "fin fonction JAM_DH-" << endl;
			#endif
		}
	      	else if (in == "OPT")
		{
			/* Recuperation of the entries */
		  	cin >> w >> hourStart >> hourEnd >> seg;
		  	segments = new int[seg];
		  	
		  	for(int i = 0; i<seg; i++)
		    	{
		      		cin >> id;
		      		segments[i] = id;
		    	}

		    	/* Process */
		    	T->OptimizedPath(w,hourStart,hourEnd,seg,segments);
		    	
		    	#ifdef MAP
			  	cout << "-" << in << " " << w 
			  		<< " " << hourStart 
			  		<< " " << hourEnd 
			  		<< " " << seg 
			  		<< " " << endl;
			  	for(int i = 0; i < seg ; i++)
			  	{
			  		cout << i << " - " << segments[i] << endl;
			  	}
			  	cout << "fin fonction OPT" << endl;
		  	#endif
		  	
		  	delete [] segments;
		}
    	}while(in != "EXIT");
    
    	delete T;

	#ifdef MAP
  		cout << "==== Work done ====" << endl;
	#endif

  	return 0;
}
