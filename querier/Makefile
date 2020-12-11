#based off of the indexer makefile

TARGET = querier

LIBS = libcs50.a

PATH1 = ../libcs50/
PATH2 = ../common/

OBJS = querier.o $(PATH2)index.o $(PATH2)word.o $(PATH2)pagedir.o

LLIBS = $(PATH1)$(LIBS)

FLAGS = -I$(PATH1) -I$(PATH2)

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

$(TARGET): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@


index.o: $(PATH1)$(LIBS) $(PATH1)webpage.o $(PATH2)word.o $(PATH2)index.h
word.o:  $(PATH1)$(LIBS) $(PATH2)word.h
pagedir.o: $(PATH1)pagedir.h $(PATH1)file.o
