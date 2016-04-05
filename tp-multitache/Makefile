# Ce makefile compile le TP C++ n°2 : TrafficJam

# =============== VARIABLES =============================
VERB = @
MAKE = $(VERB)make
RM = rm
EDL = $(VERB)g++ 
COMP = $(VERB)g++ -std=c++11
ECHO = @echo
COPY = $(VERB)cp
SHOW = $(VERB)cat
BASH = $(VERB)bash
CD = cd


EDLFLAGS = -o -std=c++11
CPPFLAGS = -c -std=c++11
WARNINGFLAGS = -Wall -Wextra -pedantic
RMFLAGS = -f
DMAP = -DMAP

INT = $(wildcard *.h)
REAL = $(wildcard *.cpp)

OBJ = $(REAL:.cpp=.o)
TEMP = $(INT:.h=.h~) $(REAL:.cpp=.cpp~) $(wildcard *~)

EXE = Parking
MAIN = Mere
#LIBS = -lm -ltp -lncurses -ltcl 
#pour Johnny
LIBS = -lm -ltp -lncurses -ltcl8.5
LIBPATH = -Llibs
INCPATH =# -I nothing

#-------------------------------------------- Directories

bindir = bin
srcdir = ./
headdir = ./Constantes
testdir = ../tests

.PHONY: clean mrproper

# ============= FORMES GENERIQUES =======================

%.o : %.cpp %.h
	$(ECHO) "\n======================================="
	$(ECHO) "=== Compilation de <$<>"
	$(COMP) $(CPPFLAGS) $(INCPATH) $(srcdir)/$< $(WARNINGFLAGS)
	$(COPY) $@ $(bindir)

%.o : %.cpp
	$(ECHO) "=== Compilation de <$<> (sans .h)"
	$(COMP) $(CPPFLAGS) $(INCPATH) $(srcdir)/$< $(WARNINGFLAGS)
	$(COPY) $@ $(bindir)

# ===================== REGLES ==========================
# ==== PATTERNS ====

all : $(OBJ) $(MAIN).o
	$(ECHO) "\n====/\=========_/'°*°'\_=========/\===="
	$(ECHO) "=== Compilation de l'executable <$<>"
	$(EDL) -o $(EXE) $(LIBPATH) $(OBJ) $(LIBS)
	$(COPY) $(EXE) $(testdir)
	
# ==== CREATION ====

$(MAIN).o : $(MAIN).cpp GestClav.o Sortie.o Entree.o 
Heure.o : Heure.h
Menu.o : Menu.h
Outils.o : Outils.h
GestClav.o : GestClav.cpp Menu.h
Entree.o: Entree.cpp Entree.h
Sortie.o : Sortie.cpp Sortie.h

rebuild:
	$(MAKE) clean
	$(MAKE) run

# ==== REGLES DE LAUNCH ====

runLeak : all
	$(ECHO) "\n->>>>>>> Lancement du programme (with leak test) <<<<<<<<-"
	valgrind ./$(EXE) 2> $(EXE).log

run : all
	$(ECHO) "\n->>>>>>> Lancement du programme <<<<<<<<-"
	./$(EXE) 2> $(EXE).log

log : 
	clear
	$(SHOW) $(EXE).log
# ==== REGLES D'EFFACEMENT ====
oClean :
	$(RM) $(RMFLAGS) $(OBJ) $(MAIN).o test.o core

clean :
	$(MAKE) cleanProcess
	$(RM) $(RMFLAGS) $(EXE) $(OBJ) $(MAIN).o test.o $(TEMP) core


mrproper :
	$(RM) $(RMFLAGS) $(EXE) core
	
cleanProcess :	
	$(ECHO) " === Clean Canals, ipcs and pcs"
	$(BASH) cleanUp.sh

