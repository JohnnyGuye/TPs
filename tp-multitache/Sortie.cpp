#include "Sortie.h"


//---------------------------------Private


static int semId, memId;
static int tubeFromKeyboard;

static deque<pair<pid_t, Voiture>> voitures;

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
		
		deque<pair<pid_t, Voiture>>::iterator it;
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
		voitures.pop_front();
	
	}
}

static void run()
{
	Voiture voiture;
	unsigned int valeur;
	pid_t voiturier;
	
	if( read(tubeFromKeyboard, &valeur, sizeof(valeur)) > 0)
	{
		shMem *sharedMemory = (shMem *) shmat(memId, NULL, 0);
		voiture = sharedMemory->places[valeur -1];
		sharedMemory->places[valeur -1] = { 0, 0, AUCUN };
		shmdt(sharedMemory);
		
		voiturier = SortirVoiture ( valeur );
		cerr << "--" << valeur;
		voitures.push_back(pair<pid_t, Voiture>(voiturier, voiture));
		
		
		Effacer( (TypeZone)( ETAT_P1 + (valeur - 1)) );
		cerr << "efface";
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