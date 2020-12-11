#!bin/bash

make
mkdir testdir

#checking the validness of the number of arguments
echo the next result should be an error, saying theres the wrong amount of inputs
./crawler this is a check to see whether or not this program identifies amount of inputs
echo exitStatus: $?
echo


#checking the validness of the depth input
echo the next result should be an error with the third input argument
./crawler this isa check
echo exitStatus: $?
echo

#checking the validness of the url
echo the next two result should be an error dealing with the url not being valid/internal
./crawler http://www.google.com definitelyDontletthisonework 4
echo exitStatus: $?
echo
./crawler dkfgotvicsm directory 2
echo exitStatus: $?
echo

#checking the validness of the directory
echo The next result should be an error because of a directory that cannot be found/written into
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html notatestdir 3
echo exitStatus: $?
echo

echo "now for some of the longer tests, I will check how many files are created in testdir from a couple crawls"
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html testdir 3
ls -l testdir | wc -l | cat
echo the above value should be 7
echo

rm ./testdir/*
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/toscrape/index.html testdir 1
ls -l testdir | wc -l | cat
echo "The above value should be 74 for the 73 links on the scrape page, plus the page itself"

