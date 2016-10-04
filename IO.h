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

#ifndef IO_H
#define IO_H

#include "Process.h"
#include "ReadyQueue.h"
#include "List.h"

/********************************************************************************************
Name: IO class
Description: The IO class is a derived class of the List class.
*********************************************************************************************/
class IO : public List
{
public:
	void addProcess(Process & P); //add a Process, ordered by shortest next burst
	void decrementBursts(); //decrements all bursts in processList
	void display(); //displays each Process and its remaining time in I/O
};

#endif