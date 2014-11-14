#!/bin/bash

function manual {
	echo "Invalid number of arguments."
	echo "Usage: ./makeGraphViz.bash <input> <output> <ext>"
	echo -e "when:\n\t<input> is 9th DIMACS Implementation Challenge or TMH format file"
	echo -e "\n\t<output> is where you want to save graph image."
	echo -e "\n\t<ext> is determinates what format the output file should have."
	echo -e "\nExample: ./makeGraphViz.bash test.gr result png\nOutput: GraphViz result.png file\n"
}

function run {
	perl toGraphViz.pl -mutf8 $1 $2
	dot -T$3 $2 -o $2.$3
	rm $2
}

if [ "$#" -ne 3 ]; then
    manual
else
	run $1 $2 $3
fi
