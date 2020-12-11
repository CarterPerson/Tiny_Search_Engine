# authored by Carter Person, May 6th, 2020

## Crawler


# to compile:

run make from the crawler directory


# Usage

This function is used to crawl through a certain webpage down to a certain depth, copying all of the html code from each URL that it encounters.


To run, pass in 3 variables.

1. the URL of the site that you would like to be the "seed" site. This is where the crawler will start crawling.

2. the directory where you would like all of the datafiles to go. These datafiles will hold the URL of each site, the depth at which that site was found, and all of the site's HTML code.

3. The depth to which you would like to search. The function will only go this many URL's away from the seed site.


# to clean:

run the command make clean from the crawler directory.


# to test

run the command "make test" from this directory. The results will be put into an output file named "testing.out"