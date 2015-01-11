package com.PWrTS.main;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

import edu.princeton.cs.algs4.Digraph;


public class DigraphHelper extends Digraph {

	public static final String COMMENT_FLAG = "c";
	public static final String PROBLEM_DEFFINITION_FLAG = "p";
	public static final String ARC_FLAG = "p";	
	
	public static final String SP_PROBLEM = "sp";

	public static final String NEWLINE = System.getProperty("line.separator");

	public DigraphHelper(Digraph G) {
		super(G);
	}
	
	public String toString( String additionalComment, int minArcCost, int maxArcCost ) {
		String[] commentLines = additionalComment.split(NEWLINE);
		StringBuilder s = new StringBuilder();
		
		for ( String line : commentLines ) {
			s.append(COMMENT_FLAG + " " + line + NEWLINE);
		}
		s.append(this.toString(minArcCost,maxArcCost));
		
		return s.toString();
	}
	
	public void toFile( FileWriter fw, String additionalComment, int minArcCost, int maxArcCost ) throws IOException {
		String[] commentLines = additionalComment.split(NEWLINE);
		
		for ( String line : commentLines ) {
			fw.write(COMMENT_FLAG + " " + line + NEWLINE);
		}
		
		this.toFile(fw,minArcCost,maxArcCost);
		return;
	}
	
	/**
	 * Returns string representation of graph in the 9th DIMACS Implementation Challenge's format.
	 */
	public String toString( int minArcCost, int maxArcCost ) {
		StringBuilder s = new StringBuilder();
		
		int numberOfNodes = super.V();
		int numberOfArcs = super.E();
		Iterable<Integer> adj = null;
		Random r = new Random();
		int delta = maxArcCost - minArcCost + 1;
		
		s.append( PROBLEM_DEFFINITION_FLAG + " " 
			+ SP_PROBLEM + " " 
			+ numberOfNodes + " " 
			+ numberOfArcs + " "
			+ NEWLINE);
		    
		s.append( COMMENT_FLAG + " graph contains "
			+ numberOfNodes + " nodes and " 
			+ numberOfArcs + " arcs"
			+ NEWLINE);
		   
		s.append( COMMENT_FLAG + NEWLINE);
		   
		for ( int v = 0; v < numberOfNodes; v += 1 ) {
			adj = super.adj(v);
				   
			for ( int e : adj ) {
				s.append(String.format("%s %d %d %d%s",ARC_FLAG,v+1,e+1,r.nextInt(delta)+minArcCost,NEWLINE));
			}
		}
		return s.toString();
	}

	public void toFile( FileWriter fw, int minArcCost, int maxArcCost) throws IOException {
		
		int numberOfNodes = super.V();
		int numberOfArcs = super.E();
		Iterable<Integer> adj = null;
		Random r = new Random();
		int delta = maxArcCost - minArcCost + 1;
		
		fw.write( PROBLEM_DEFFINITION_FLAG + " " 
			+ SP_PROBLEM + " " 
			+ numberOfNodes + " " 
			+ numberOfArcs + " "
			+ NEWLINE);
		    
		fw.write( COMMENT_FLAG + " graph contains "
			+ numberOfNodes + " nodes and " 
			+ numberOfArcs + " arcs"
			+ NEWLINE);
		   
		fw.write( COMMENT_FLAG + NEWLINE);
		   
		for ( int v = 0; v < numberOfNodes; v += 1 ) {
			adj = super.adj(v);
				   
			for ( int e : adj ) {
				fw.write(String.format("%s %d %d %d%s",ARC_FLAG,v+1,e+1,r.nextInt(delta)+minArcCost,NEWLINE));
			}
		}
		return;
	}
}
