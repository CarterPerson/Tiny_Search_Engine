#started from the libcs50 makefile

# object files, and the target library

TARGET = indexer

LIBS = libcs50.a

PATH1 = ../libcs50/
PATH2 = ../common/

OBJS = indexer.o  $(PATH2)index.o $(PATH1)webpage.o  $(PATH2)word.o $(PATH2)pagedir.o $(PATH1)file.o

LLIBS = $(PATH1)$(LIBS)

FLAGS = -I$(PATH1) -I$(PATH2) # -DMEMTEST  # -DNOSLEEP

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

# Build the library by archiving object files
$(TARGET): $(OBJS) $(LLIBS)
	 $(CC) $(CFLAGS) $^ -o $@

index.o: $(PATH1)$(LIBS) $(PATH1)webpage.o $(PATH2)word.o $(PATH2)index.h
word.o:  $(PATH1)$(LIBS) $(PATH2)word.h
webpage.o: $(PATH1)webpage.h
pagedir.o: $(PATH2)pagedir.h $(PATH1)file.o
indextester: index.o
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) -o $@


test: $(TARGET) testing.sh
	./testing.sh > testingout

clean:
	rm indexer
	rm indexer.o
	rm testingout
	rm testout.sorted
	rm testoutCheck
	rm testoutCheck.sorted
	rm testout
	rm core*





