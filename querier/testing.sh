#! /bin/bash

./querier testdir indexfile
#inputs will be a

./querier testdir indexfile
#inputs will be a and b

./querier testdir indexfile
#inputs will be a b

./querier testdir indexfile
#inputs will be c or a and b

./querier nottestdir indexfile
#no inputs, will return nonzero with an error message
echo $?

./querier testdir indexfile notReal
#no inputs, will return nonzero with an error message
echo $?
