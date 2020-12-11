## Author: Carter Person, May 24th, 2020

# Querier

## Compiling
to compile, use the "make" command from the command line inside the querier directory


## Usage

when using this function, pass in a path to a directory made by crawler and a path to a file made an indexer call on that directory. The function will then prompt for a "query", where you may type in the keywords that you would like to search the webpages found by crawler for. 

This function will print to stdout lines for all pages that match the query search to some degree, giving the "score" for each page, as well as the document ID and the url for the page. These lines are ordered with the highest scoring page at the top, and the lowest scoring page at the bottom


## assumptions

1. it is assumed that the largest crawler produced directory has less than 10,000,000 files.
