#include "Sortie.h"


//---------------------------------Private


static int semId, memId;
static int tubeFromKeyboard;

static map<pid_t, Voiture> voitures;

static void killVoiturier(int);
static void killBarriere(int);
static void run();

static void killBarriere(int signal)
{
	if(signal == SIGUSR2)
	{
		struct sigaction action;
		action.sa_handler = SIG_IGN;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;
		sigaction(SIGCHLD, &action, NULL);
		
		map<pid_t, Voiture>::iterator it;
		for(it = voitures.begin(); it != voitures.end(); it++)
			kill((it)->first, SIGUSR2);
		
		for(it = voitures.begin(); it != voitures.end(); it++)
			waitpid((it)->first, NULL, 0);

		close(tubeFromKeyboard);
		exit(0);
	}

}

static void killVoiturier(int signal)
{
	if(signal == SIGCHLD)
	{
		struct sembuf pSM = {MutexSM, -1, 0};
		struct sembuf vSM = {MutexSM, 1, 0};
	
		int retour;
		Voiture reqPBP, reqABP, reqGB, v;
		
		pid_t voiturier = wait(&retour);
		retour = WEXITSTATUS(retour);
		
		//Accèse mémoire
		while(semop(semId, &pSM, 1) == -1 && errno == EINTR);		
		shMem *sharedMemory = (shMem *) shmat(memId, NULL, 0);
		v = sharedMemory->places[retour -1];//recup de la voiture puis effacement de son existance dans la sm
		sharedMemory->places[retour -1] = { 0, 0, AUCUN };
		sharedMemory->nbPlacesTaken--;
		reqPBP = sharedMemory->requetes[(int)PROF_BLAISE_PASCAL - 1];
		reqABP = sharedMemory->requetes[(int)AUTRE_BLAISE_PASCAL -1];
		reqGB = sharedMemory->requetes[(int)ENTREE_GASTON_BERGER -1];
		shmdt(sharedMemory);		
		semop(semId, &vSM, 1);
		//--Fin accès mémoire
		
		AfficherSortie( v.usager, v.numIndex, v.arrivee, time(NULL) );
		
		map<pid_t, Voiture>::iterator it = voitures.find(voiturier);
		voitures.erase(it);
		
		//On choisir l'ordre des priorité. 
		//La porte exclusive prof est prioritaire.
		//Ensuite c'est GB s'il y a un prof
		//Si deux usagers lambda sont présents, c'est le premier qui est servi
		//On note que si deux profs sont aux deux portes, celui qui s'est mis dans la porte fourre tout est perdant
		TypeBarriere nextV;
		if( reqPBP.usager == PROF )			
			nextV = PROF_BLAISE_PASCAL;
		else if( reqGB.usager == PROF ) 	
			nextV = ENTREE_GASTON_BERGER;
		else if( (reqABP.usager == AUTRE ) && (reqGB.usager == AUTRE ) )
			nextV = ( reqABP.arrivee > reqGB.arrivee ? ENTREE_GASTON_BERGER : AUTRE_BLAISE_PASCAL );
		else if( reqABP.usager != AUCUN )
			nextV = AUTRE_BLAISE_PASCAL;
		else if( reqGB.usager != AUCUN )
			nextV = ENTREE_GASTON_BERGER;
		else
			nextV = AUCUNE;
		
		cerr << nextV << "--";
		if( nextV != 0 )
		{
			struct sembuf v = {(short unsigned int)nextV, 1, 0};
			
			//Accès mémoire
			while(semop(semId, &pSM, 1) == -1 && errno == EINTR);
			shMem *sharedMemory = (shMem *) shmat(memId, NULL, 0);
			sharedMemory->requetes[nextV - 1] = {0, 0, AUCUN};
			sharedMemory->nbPlacesTaken++;
			shmdt(sharedMemory);
			semop(semId, &vSM, 1);
			//--Fin accès mémoire
			
			semop(semId, &v, 1);
		}	
		
	
	}
}

static void run()
{
	Voiture voiture;
	unsigned int valeur;
	pid_t voiturier;
	
	//struct sembuf v = {type, 1, 0};
	struct sembuf pSM = {MutexSM, -1, 0};
	struct sembuf vSM = {MutexSM, 1, 0};
	
	if( read(tubeFromKeyboard, &valeur, sizeof(valeur)) > 0)
	{
		
		voiturier = SortirVoiture ( valeur );
		
		if( voiturier != -1 )//Ca marche moins bien quand y a pas de voiture à cette place..
		{
			while(semop(semId, &pSM, 1) == -1 && errno == EINTR);
		
			shMem *sharedMemory = (shMem *) shmat(memId, NULL, 0);
			voiture = sharedMemory->places[valeur -1];
			shmdt(sharedMemory);
		
			semop(semId, &vSM, 1);
		
			voitures.insert(pair<pid_t, Voiture>(voiturier, voiture));
		
			Effacer( (TypeZone)( ETAT_P1 + (valeur - 1)) );
		}
	}

}

//--------------------------------Public

void Sortie( int memID, int semID )
{
	semId = semID;
	memId = memID;
	
	//init
	//Handler kill en premier pour éviter les mauvaises surprises
	struct sigaction action;
	action.sa_handler = killBarriere;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGUSR2, &action, NULL);
	
	//Pour ne pas ignorer la mort des processus de voiturier
	struct sigaction mortVoiturier;
	mortVoiturier.sa_handler = killVoiturier ;
	sigemptyset(&mortVoiturier.sa_mask);
	mortVoiturier.sa_flags = 0 ;
	sigaction(SIGCHLD, &mortVoiturier, NULL);
	
	tubeFromKeyboard = open(CANAL_S, O_RDONLY);
	
	for(;;)	run();
}
