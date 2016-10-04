/********************************************************************************************
Name: Gavin Wolf		Z#: 15289719
Course: Computer Operating Systems - COP 4610
Professor: Dr. Borko Furht
Due Date: 10/22/2015
Programming Assignment - CPU Scheduler

Description: This program simulates CPU scheduling algorithms on a set of processes with
 specified CPU and I/O burst times.
*********************************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef List_H
#define List_H

#include "Process.h"

/********************************************************************************************
Name: List class
Description: The List class represents a list of Processes. The List class is the base class
 for the derived classes: ReadyQueue, IO, and Completed. The derived classes inherit the base
 class functionality and add additional functions.
*********************************************************************************************/
class List
{
public:
	List(); //constructor
	void addProcess(Process & P); //add a Process to back of processList
	void addProcessToFront(Process & P); //add a Process to front of processList
	void sortAscending(); //sort Processes (used for Shortest Job First scheduling)
	Process & removeProcess(); //remove and return a Process from the front of processList
	int nextBurst(); //get next burst time
	void removeNextBurst(); //remove next burst (used when burst is completed)
	bool isEmpty(); //returns true when no Processes on processList
	int getTimeQuantum() const; //accessor for timeQuantum
	void setTimeQuantum(const int Tq); //setter for timeQuantum 

protected:
	vector<Process*> processList; //vector of pointers to Process objects
	int timeQuantum; //for Round Robin in Multilevel Feedback Queue
};

#endif