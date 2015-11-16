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
REAL = $(INT:.h=.cpp)

OBJ = $(REAL:.cpp=.o)
TEMP = $(INT:.h=.h~) $(REAL:.cpp=.cpp~) $(wildcard *~)

EXE = TrafficJam
TEST = TrafficJamT
NRTEST = NRTester.sh
LIBS = -lm
LIBPATH =# -Lnothing
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
# ==== REGLES DE CREATION ====

all : $(OBJ) main.o
	$(ECHO) "\n====/\=========_/'°*°'\_=========/\===="
	$(ECHO) "=== Compilation de l'executable <$<>"
	$(EDL) -o $(EXE) $(LIBPATH) $(OBJ) main.o $(LIBS)
	$(COPY) $(EXE) $(testdir)

allTest : $(OBJ) test.o
	$(ECHO) "\n====/\=========_/'°*°'\_=========/\===="
	$(ECHO) "=== Compilation de l'executable <$<>"
	$(EDL) -o $(TEST) $(LIBPATH) $(OBJ) test.o $(LIBS)
	$(COPY) $(TEST) $(testdir)
	
main.o : main.cpp 
test.o : test.cpp
Traffic.o : Traffic.cpp Traffic.h Sensor.o
Sensor.o : Sensor.cpp Sensor.h $(headdir)/Constant.h TrafficData.o
TrafficData.o : TrafficData.cpp TrafficData.h

# ==== REGLES DE LAUNCH ====

runLeach : all
	$(ECHO) "\n->>>>>>> Lancement du programme (with leach test) <<<<<<<<-"
	valgrind ./$(EXE)

run : all
	$(ECHO) "\n->>>>>>> Lancement du programme <<<<<<<<-"
	./$(EXE)

test : allTest
	$(ECHO) "\n->>>>>>> Lancement du test <<<<<<<<-"
	./$(TEST)
	
testLeach : allTest
	$(ECHO) "\n->>>>>>> Lancement du test (with leach test) <<<<<<<<-"
	valgrind ./$(TEST)
	
#testNR : all
#	$(ECHO) "\n->>>>>>> Lancement du testNR <<<<<<<<-"
#	cd  $(testdir)
#	bash NRTester.sh $(EXE)
#Not working

# ==== REGLES D'EFFACEMENT ====
oClean :
	$(RM) $(RMFLAGS) $(OBJ) main.o test.o core

clean :
	$(RM) $(RMFLAGS) $(EXE) $(TEST) $(OBJ) main.o test.o $(TEMP) core

mrproper :
	$(RM) $(RMFLAGS) $(EXE) $(TEST) core

