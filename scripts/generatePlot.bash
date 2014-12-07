#!/bin/bash

function execute {

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
		octave --eval "
		addpath(\"$OCTAVEPATH\")
		dataArray = {
			\"$DATAPATH/BFP\",
			\"$DATAPATH/DKQd\"
		}
	 	styleArray = {
			\"b-\",
			\"r--\"
		}
	 	legendArray = {
			\"Bellman-Ford-More with parent checking\",
			\"Naive Dijkstra Impl. with D-L lists\"
		}
	 	generatePlot(\"$title\",\"$xLabelName\",\"$yLabelName\",dataArray,styleArray,legendArray,\"$OUTPATH/$outputFileName\",\"$outputFileExtension\",2)
		"
		echo -e "Plot has been saved to: \"$OUTPATH\" as \"$outputFileName.$outputFileExtension\"\n"
	fi

}

echo '----------------------------------------------------'
execute
