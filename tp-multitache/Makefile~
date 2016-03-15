# Ce makefile compile le TP C++ n°2 : TrafficJam

# =============== VARIABLES =============================
MAKE = @make
EDL = g++
COMP = g++
RM = rm
ECHO = @echo
COPY = @cp
CD = cd


EDLFLAGS = -o
CPPFLAGS = -c
WARNINGFLAGS = -Wall -Wextra -pedantic
RMFLAGS = -f
DMAP = -DMAP

INT = $(wildcard *.h)
REAL = $(wildcard *.cpp)

OBJ = $(REAL:.cpp=.o)
TEMP = $(INT:.h=.h~) $(REAL:.cpp=.cpp~) $(wildcard *~)

EXE = Parking
LIBS = -lm -ltp
#-lncurses -ltcl
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

all : $(OBJ) main.o
	$(ECHO) "\n====/\=========_/'°*°'\_=========/\===="
	$(ECHO) "=== Compilation de l'executable <$<>"
	$(EDL) -o $(EXE) $(LIBPATH) $(OBJ) main.o $(LIBS)
	$(COPY) $(EXE) $(testdir)
	
# ==== CREATION ====

main.o : main.cpp
Heure.o : Heure.h
Menu.o : Menu.h
Outils.o : Outils.h

# ==== REGLES DE LAUNCH ====

runLeach : all
	$(ECHO) "\n->>>>>>> Lancement du programme (with leak test) <<<<<<<<-"
	valgrind ./$(EXE)

run : all
	$(ECHO) "\n->>>>>>> Lancement du programme <<<<<<<<-"
	./$(EXE)

# ==== REGLES D'EFFACEMENT ====
oClean :
	$(RM) $(RMFLAGS) $(OBJ) main.o test.o core

clean :
	$(RM) $(RMFLAGS) $(EXE) $(OBJ) main.o test.o $(TEMP) core

mrproper :
	$(RM) $(RMFLAGS) $(EXE) core

