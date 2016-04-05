#include "Entree.h"

static int tubeFromKeyboard;	//Canal de communication avec l'entrée
static int memId, semId;

static map<pid_t, Voiture> voitures;

static void killBarriere (int signal);
static void run (TypeBarriere type);
static void killVoiturier(int signal);

//Le moteur du process
static void run(TypeBarriere type)
{
	
	Voiture voiture;//Stocke la dernière voiture dans la file
	struct sembuf p = {type, -1, 0};
	struct sembuf pSM = {MutexSM, -1, 0};
	struct sembuf vSM = {MutexSM, 1, 0};
	
	if( read(tubeFromKeyboard, &voiture, sizeof(Voiture)) > 0)//A chaque fois qu'une voiture arrive
	{
		DessinerVoitureBarriere(type, voiture.usager);
		
		while(semop(semId, &pSM, 1) == -1 && errno == EINTR);	//On demande l'accès à la SM	
		shMem *sharedMemory = (shMem *) shmat(memId, NULL, 0);	
		if(sharedMemory->nbPlacesTaken == NB_PLACES)
		{
			AfficherRequete(type, voiture.usager, voiture.arrivee);
			sharedMemory->requetes[type - 1] = voiture;
			shmdt(sharedMemory);
			
			semop(semId, &vSM, 1);
			
			while(semop(semId, &p, 1) == -1 && errno == EINTR);
		}
		else
		{
			sharedMemory->nbPlacesTaken++;
			shmdt(sharedMemory);
			
			semop(semId, &vSM, 1);
		}
		pid_t voiturier = GarerVoiture(type);
		voitures.insert(pair<pid_t, Voiture>(voiturier, voiture));
		
		//Y avait le soucis de la requete qui restait affichée même quand la voiture se garait
		Effacer( (TypeZone) (REQUETE_R1 + (type - 1) )  );
		
	}
}

//Quand on demande à la barrière de mourrir
static void killBarriere(int signal)
{
	//On vérifie le signal
	if(signal == SIGUSR2)
	{
		
		struct sigaction action;
		action.sa_handler = SIG_IGN;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;
		sigaction(SIGCHLD, &action, NULL);
		
		map<pid_t, Voiture>::iterator it;
		for(it = voitures.begin(); it != voitures.end(); it++)//Tuez moi ces gosses
		{
			kill(it->first, SIGUSR2);
		}
		
		for(it = voitures.begin(); it != voitures.end(); it++)//Attendons qu'ils soient bien morts
		{
			waitpid(it->first, NULL, 0);
		}
		
		close(tubeFromKeyboard);
		exit(0);
	}
}

//Quand un voiturier meurt
static void killVoiturier (int signal)
{
	//La voiture vient de se garer, il faut l'écrire en mémoire et l'afficher
	//le wait, permet de savoir où
	if(signal == SIGCHLD)
	{
		Voiture v;
		int retour;
		
		pid_t voiturier = wait(&retour);
		retour = WEXITSTATUS(retour);
		v = ( voitures.find(voiturier) )->second;
		
		AfficherPlace(retour, v.usager, v.numIndex, v.arrivee);
		
		shMem *sharedMemory = (shMem*) shmat(memId, NULL, 0);
		sharedMemory->places[retour - 1] = v;
		shmdt(sharedMemory);
		
		voitures.erase(voiturier);
	}
}

//	------------------------------------------------ PUBLIC
//	Processus complet 
void Entree(TypeBarriere type, int memID, int semID)
{
	switch(type)
	{
		case 1: cerr << "I1\n";	break;
		case 2: cerr << "I2\n";	break;
		case 3: cerr << "I3\n";	break;
		default:cerr << "Fail\n";	break;
	}
	memId = memID;
	semId = semID;
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
	
	switch(type)
	{
		case PROF_BLAISE_PASCAL:
			tubeFromKeyboard = open(CANAL_PBP, O_RDONLY);
			break;
		case ENTREE_GASTON_BERGER:
			tubeFromKeyboard = open(CANAL_GB, O_RDONLY);
			break;
		case AUTRE_BLAISE_PASCAL:
			tubeFromKeyboard = open(CANAL_ABP, O_RDONLY);
			break;
		default:
			tubeFromKeyboard = -1;
			break;
	}
	
	for(;;)	run(type);
	
}
