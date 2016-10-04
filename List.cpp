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
#include <algorithm>

#include "Process.h"
#include "List.h"

using namespace std;

/********************************************************************************************
Name: List
Description: Default constructor for a List object
*********************************************************************************************/
List::List()
{
	processList = {};
	timeQuantum = 0;
}

/********************************************************************************************
Name: addProcess
Description: Accepts a reference to a Process object and adds it to the back of the 
 processList vector
*********************************************************************************************/
void List::addProcess(Process & P)
{
	processList.push_back(&P);
}

/********************************************************************************************
Name: addProcessToFront
Description: Accepts a reference to a Process object and adds it to the front of the 
 processList vector
*********************************************************************************************/
void List::addProcessToFront(Process & P)
{
	processList.insert(processList.begin(), &P);
}

/********************************************************************************************
Name: sortAscending
Description: Sorts the processList vector in ascending order of next burst time
*********************************************************************************************/
void List::sortAscending()
{
	sort(processList.begin(), processList.end(), shorterNextBurst());
}

/********************************************************************************************
Name: removeProcess
Description: Removes and returns the first Process in the processList vector
*********************************************************************************************/
Process & List::removeProcess()
{
	Process * P = processList[0];
	processList.erase(processList.begin());
	return *P;
}

/********************************************************************************************
Name: nextBurst
Description: Returns the next burst for the first Process object in the processList vector
*********************************************************************************************/
int List::nextBurst()
{
	return (*processList[0]).getNextBurst();
}

/********************************************************************************************
Name: removeNextBurst
Description: Removes the next burst for the first Process object in the processList vector
*********************************************************************************************/
void List::removeNextBurst()
{
	(*processList[0]).removeNextBurst();
}

/********************************************************************************************
Name: isEmpty
Description: Returns true when there are no Processes in the processList vector
*********************************************************************************************/
bool List::isEmpty()
{
	return processList.size() == 0;
}

/********************************************************************************************
Name: getTimeQuantum
Description: Accessor for timeQuantum
*********************************************************************************************/
int List::getTimeQuantum() const
{
	return timeQuantum;
}

/********************************************************************************************
Name: setTimeQuantum
Description: Sets timeQuantum to the value of "Tq"
*********************************************************************************************/
void List::setTimeQuantum(const int Tq)
{
	timeQuantum = Tq;
}