#include "Outils.h"
#include "Globaux.h"

#include <signal.h> //pour sigaction SIGUSR2 et SIGCHLD
#include <stdlib.h> //pour exit
#include <iostream>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>	//shared memory
#include <sys/sem.h>	//semget et autres
#include <sys/types.h>
#include <sys/stat.h>

#include <map>
#include <tuple>

void Sortie ( int memId, int semId);


