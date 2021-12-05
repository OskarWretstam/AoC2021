# What to build
DAY?=01

# Compiler
CC:=gcc
CC_FLAGS:=-O3

# Tools
TIME:=/usr/bin/time -p
CAT:=/usr/bin/cat
SHELL:=/usr/bin/sh

# Structure
SRC:=$(DAY)/code.c
BIN:=$(DAY)/app.out
DATA:=$(DAY)/input
TASK:=$(DAY)/task.md

all:
	$(CC) $(CC_FLAGS) $(SRC) -o $(BIN)
ifeq (,$(wildcard $(DATA)))
	$(TIME) ./$(BIN)
else
	$(TIME) $(SHELL) -c '$(CAT) $(DATA) | ./$(BIN)'
endif

create:
ifeq (,$(wildcard $(SRC)))
	aoc -d $(DAY) -y 2021 r > tmp
	aoc -d $(DAY) -y 2021 d
	mkdir $(DAY)
	cp template.c $(SRC)
	mv input $(DATA)
	mv tmp $(TASK)
else
	$(error Structure for day $(DAY) already exists)
endif

clean:
	rm -f $(DAY)/app.out
