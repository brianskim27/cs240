COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 5
LASTNAME = Choe
GITUSERID = taestii

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CPNUMBER)$(LASTNAME)$(USER)$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
CCFLAGS = -std=c++11 -Wall

all: pr_check3 sch_check waitlist

pr_check3: pr_check3.cpp pr_check3_main.cpp
	$(CC) $(CCFLAGS) $^ -o $@

sch_check: sch_check.cpp sch_check_main.cpp pr_check3.cpp
	$(CC) $(CCFLAGS) $^ -o $@

waitlist: waitlist.cpp pr_check3.cpp sch_check.cpp
	$(CC) $(CCFLAGS) $^ -o $@


.PHONY: all
all: pr_check3 sch_check waitlist

.PHONY: clean
clean:
	rm -f pr_check3 sch_check waitlist

.PHONY: run
run:
	./pr_check3 prereq.txt
	./sch_check prereqfile.txt schedfile.txt
	./waitlist 2023Fall prereqfile.txt schedules.txt enrollmentfile.txt
	
	
