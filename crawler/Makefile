#started from the libcs50 makefile

# object files, and the target library

TARGET = crawler

LIBS = libcs50.a

PATH1 = ../libcs50/
PATH2 = ../common/

OBJS = crawler.o $(PATH2)pagedir.o

LLIBS = $(PATH1)$(LIBS)

FLAGS = -I$(PATH1) -I$(PATH2) # -DMEMTEST  # -DNOSLEEP

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

# Build the library by archiving object files
$(TARGET): $(OBJS) $(LLIBS)
	 $(CC) $(CFLAGS) $^ -o $@
 
test: $(TARGET) testing.sh
	bash testing.sh > testing.out


# clean up after our compilation
clean:
	rm -f core
	rm -f ./testdir/*
	rm -f crawler.o
	rm -f crawler

