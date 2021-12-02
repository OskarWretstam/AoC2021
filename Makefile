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
DATA:=$(DAY)/data.txt

all:
	$(CC) $(CC_FLAGS) $(SRC) -o $(BIN)
ifeq (,$(wildcard $(DATA)))
	$(TIME) ./$(BIN)
else
	$(TIME) $(SHELL) -c '$(CAT) $(DATA) | ./$(BIN)'
endif

clean:
	rm -f $(DAY)/app.out
