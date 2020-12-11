#! /bin/bash

chmod 775 testout
chmod 775 testoutCheck
gawk -f indexsort.awk testout > testout.sorted
gawk -f indexsort.awk testoutCheck > testoutCheck.sorted
cmp testout.sorted testoutCheck.sorted
echo $?

echo "return value of 0 means that the two files are identical"

exit 0

