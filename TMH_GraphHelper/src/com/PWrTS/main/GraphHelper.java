package com.PWrTS.main;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import edu.princeton.cs.algs4.DigraphGenerator;

public class GraphHelper {
	
	public static void main(String[] args) throws IOException {
		
		if ( args.length == 5 ) {
			start(args);
		} else {
			usage();
		}
	}

	private static void start(String[] args) throws IOException {
		DigraphHelper g;
		int numberOfNodes = Integer.valueOf(args[0]);
		int minArcCost = Integer.valueOf(args[2]);
		int maxArcCost = Integer.valueOf(args[3]);

		String outputFileName = args[4];

		if ( args[1].contains(".") || args[1].contains(",") ) {
			g = new DigraphHelper(
					DigraphGenerator.simple(
							numberOfNodes,
							Double.valueOf(args[1])));
		} else {
			g = new DigraphHelper(
					DigraphGenerator.simple(
							numberOfNodes,
							Integer.valueOf(args[1])));
		}

		File file = new File(outputFileName);
		FileWriter fw = new FileWriter(file);
		g.toFile(fw,minArcCost,maxArcCost);
		fw.close();

	}

	private static void usage() {
		System.out.println("java -jar GraphHelper.jar <numberOfNodes> <numberOfArcs/ArcProbability> <minArcCost> <maxArcCost> <outputFileName>\n");		
	}
}