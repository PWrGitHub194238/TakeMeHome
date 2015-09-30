#!/bin/bash

function useage() {
	echo -e "bash generatePlot.bash <file name> <octave line style> <function label> [...]\n\n"
	echo -e "\t<file name> - name of the file with data in given format i.e.\n\t\t1\t1\n\t\t2\t4\n\t\t3\t9\n\t\t...\t...\n\tis an example of function f(x)=x^2\n"
	echo -e "\t<octave line style> - style of octave drawing in FMT format. To learn more see Octave's 'plot' documentation.\n"
	echo -e "\t<function label> - how given function will be named on a plot.\n"
}

echo '----------------------------------------------------'


inputArray=( "$@" )
dataArray=()
styleArray=()
legendArray=()


if [ $# != 0 -a $(($#%3)) = 0 ];
then
	#fillArrays

	for (( i=0; i<$#; ))
		do
		dataArray+=(${inputArray[$i]})
		echo "Add to dataArray: " ${inputArray[$i]}
		i=$(($i+1))

		styleArray+=(${inputArray[$i]})
		echo "Add to styleArray: " ${inputArray[$i]}
		i=$(($i+1))

		legendArray+=(${inputArray[$i]})
		echo "Add to legendArray: " ${inputArray[$i]}
		i=$(($i+1))
	done
	
	#runScript

	read -p "Enter path to generatePlot Octave's function or leave empty (./octave):" OCTAVEPATH
	if [ -z "$OCTAVEPATH" ] 
	then
		OCTAVEPATH='./octave'
	fi

	read -p "Enter path to folder with Data Input Files or leave empty (./plots/inData):" DATAPATH
	if [ -z "$DATAPATH" ] 
	then
		DATAPATH='./plots/inData'
	fi

	read -p "Enter full path to output or leave empty (./plots/outData):" OUTPATH
	if [ -z "$OUTPATH" ] 
	then
		OUTPATH='./plots/outData'
	fi

	if [ ! -d "$OUTPATH" ] 
	then
		mkdir -p $OUTPATH
	fi

	read -p "Enter plot's title (Plot's title):" title
	if [ -z "$title" ] 
	then
		title="Plot's title"
	fi

	read -p "Enter title of plot's X label (X):" xLabelName
	if [ -z "$xLabelName" ] 
	then
		xLabelName='X'
	fi

	read -p "Enter title of plot's Y label (Y):" yLabelName
	if [ -z "$yLabelName" ] 
	then
		yLabelName='Y'
	fi

	read -p "Enter name of output file (out):" outputFileName
	if [ -z "$outputFileName" ] 
	then
		outputFileName='out'
	fi

	read -p "Enter extension of output file (epsc):" outputFileExtension
	if [ -z "$outputFileExtension" ] 
	then
		outputFileExtension='epsc'
	fi

	echo -e "Plot configuration summary: 
	Octave function path:\t$OCTAVEPATH
	Input data path:\t$DATAPATH
	Output plot path:\t$OUTPATH
	Plot's title:\t$title
	Plot X label:\t$xLabelName
	Plot Y label:\t$yLabelName
	Output file:\t$outputFileName.$outputFileExtension"

	read -p 'Do you want to create this plot? (y/n): ' createPlot
	if [ $createPlot == "y" ] 
	then

		# Replace colons

		sed -i 's/,/./g' $DATAPATH/*

		#generateOctaveString
			
		octaveString="addpath(\"$OCTAVEPATH\")"

		octaveString="$octaveString; dataArray = {"
		for (( i=0; i<$((${#dataArray[@]}-1)); i+=1 ))
		do
			octaveString="$octaveString \"$DATAPATH/${dataArray[$i]}\","
			echo "CHECK dataArray: " ${dataArray[$i]}
		done
		octaveString="$octaveString \"$DATAPATH/${dataArray[$i]}\""
		octaveString="$octaveString}"

		octaveString="$octaveString; styleArray = {"
		for (( i=0; i<$((${#styleArray[@]}-1)); i+=1 ))
		do
			octaveString="$octaveString \"${styleArray[$i]}\","
			echo "CHECK styleArray: " ${styleArray[$i]}
		done
		octaveString="$octaveString \"${styleArray[$i]}\""
		octaveString="$octaveString}"

		octaveString="$octaveString; legendArray = {"
		for (( i=0; i<$((${#legendArray[@]}-1)); i+=1 ))
		do
			octaveString="$octaveString \"${legendArray[$i]}\","
			echo "CHECK legendArray: " ${legendArray[$i]}
		done
		octaveString="$octaveString \"${legendArray[$i]}\""
		octaveString="$octaveString}"

		octaveString="$octaveString; generatePlot(\"$title\",\"$xLabelName\",\"$yLabelName\",dataArray,styleArray,legendArray,\"$OUTPATH/$outputFileName\",\"$outputFileExtension\",$(($#/3)))"

		echo -e "$octaveString"
		octave --eval "$octaveString"
		echo -e "Plot has been saved to: \"$OUTPATH\" as \"$outputFileName.$outputFileExtension\"\n"
	fi

else
	useage
fi



