#pragma once

#include "Menu.h"
#include "Globaux.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h> //pour exit
#include <iostream>

// 	----------------------------------- PUBLIC

void ClavManager();

void Commande( char code, unsigned int value);
