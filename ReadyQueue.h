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

#ifndef ReadyQueue_H
#define ReadyQueue_H

#include "Process.h"
#include "List.h"

/********************************************************************************************
Name: ReadyQueue class
Description: The ReadyQueue class is a derived class of the List class.
*********************************************************************************************/
class ReadyQueue: public List
{
public:
	void display(); //displays the state of the ReadyQueue
};

#endif