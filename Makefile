# Makefile written by NuoyanChen 8/21/2020
# 2020s2 UNIMELB COMP20003 assignment 1


# Not sure if you markers will do the test manully, so I commented it out
# Also commented out the 'run' and 'show'
# but clean object files remains :)
##########################################################################

CC = gcc
CFLAGS = -Wall -g

VALGRIND = valgrind
VALGRINDFLAG = --leak-check=full --read-var-info=no  --track-origins=yes --tool=memcheck

PROGRAM = dict
SOURCE_FILES = $(shell find . -maxdepth 1 -type f -name '*.c')
HEADER_FILES = $(shell find . -maxdepth 1 -type f -name '*.h')
OBJECT_FILES = $(SOURCE_FILES:.c=.o)
cls_cmd:=tput clear

.PHONY: all build clean run show valgrind

#DATA_FILE = small.csv
DATA_FILE = Business_establishment_trading_name_and_industry_classification_2018.csv
OUTPUT_FILE = sampleOutput.txt
KEYWORD_FILE = sampleInput.txt

all: build clean #run show 

build: $(PROGRAM)

clean:
	rm -f $(OBJECT_FILES)
	#$(cls_cmd)
    
run: build clean
	./$(PROGRAM) $(DATA_FILE) $(OUTPUT_FILE) < $(KEYWORD_FILE)
    
show:
	cat $(OUTPUT_FILE)

valgrind: build clean
	$(cls_cmd)
	$(VALGRIND) $(VALGRINDFLAG) ./$(PROGRAM) $(DATA_FILE) $(OUTPUT_FILE) < $(KEYWORD_FILE)

$(PROGRAM): $(OBJECT_FILES)
	$(CC) -o $@ $^
