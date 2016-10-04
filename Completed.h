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

#ifndef COMPLETED_H
#define COMPLETED_H

#include "Process.h"
#include "List.h"

/********************************************************************************************
Name: Completed class
Description: The Completed class is a derived class of the List class.
*********************************************************************************************/
class Completed : public List
{
public:
	void addProcess(Process & P); //add a Process to Completed, ordered by processID
	void display(); //to display Completed list at each context switch

	double averageWaitingTime(); //average waiting time of all Processes
	double averageTurnaroundTime(); //average turnaround time of all Processes
	double averageResponseTime(); //average response time of all Processes

	void displayWaitingTimes();
	void displayTurnaroundTimes();
	void displayResponseTimes();
};

#endif