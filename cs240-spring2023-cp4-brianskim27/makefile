COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 4
LASTNAME = Kim
GITUSERID = brianskim27
EXE = main

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/bst.o $(OBJ)/main.o 
	$(CC) $(FLAGS) $(OBJ)/bst.o $(OBJ)/main.o -o $@

$(OBJ)/bst.o: bst.cpp bst.h
	$(CC) $(FLAGS) -c bst.cpp -o $@

$(OBJ)/main.o: main.cpp bst.h
	$(CC) $(FLAGS) -c main.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
