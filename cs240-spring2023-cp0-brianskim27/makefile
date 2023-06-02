# Specifiy the target
all: study

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
study: Study.o Course.o Roster.o
	g++ Study.o Course.o Roster.o -o study

# Specify how the object files should be created from source files
Roster.o: Roster.cpp Roster.h
	g++ -c Roster.cpp

Course.o: Course.cpp Course.h Roster.h
	g++ -c Course.cpp

Study.o: Study.cpp Course.h
	g++ -c Study.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o study
