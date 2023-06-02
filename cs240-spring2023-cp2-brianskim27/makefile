COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 2
LASTNAME = Kim
GITUSERID = brianskim27
EXE = schedule_cp2

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/course.o $(OBJ)/student.o $(OBJ)/schedule_cp2.o 
	$(CC) $(FLAGS) $(OBJ)/course.o $(OBJ)/student.o $(OBJ)/schedule_cp2.o -o $@

$(OBJ)/course.o: course.cpp course.h
	$(CC) $(FLAGS) -c course.cpp -o $@

$(OBJ)/student.o: student.cpp student.h
	$(CC) $(FLAGS) -c student.cpp -o $@

$(OBJ)/schedule_cp2.o: schedule_cp2.cpp course.h student.h
	$(CC) $(FLAGS) -c schedule_cp2.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
