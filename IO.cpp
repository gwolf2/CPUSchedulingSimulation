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
#include "ReadyQueue.h"
#include "IO.h"

using namespace std;

/********************************************************************************************
Name: addProcess
Description: Accepts a reference to a Process object and adds the object to the IO object's 
 processList in order, sorted by shortest next burst time
*********************************************************************************************/
void IO::addProcess(Process & P)
{
	processList.push_back(&P);
	sort(processList.begin(), processList.end(), shorterNextBurst());
}

/********************************************************************************************
Name: display
Description: Displays the processID and next burst time for all Processes on the IO objects's 
 processList
*********************************************************************************************/
void IO::display()
{
	cout << "In I/O:       Process    Remaining I/O Time\n";

	if (isEmpty())
		cout << "              [empty]\n";

	for (unsigned int i = 0; i < processList.size(); i++)
	{
		cout << "              " << (*processList[i]).getProcessID()
			<< "         " << (*processList[i]).getNextBurst() << endl;
	}

	cout << "..................................................\n";
}

/********************************************************************************************
Name: decrementBursts
Description: Decrements the next burst times for all Process on the IO object's processList
*********************************************************************************************/
void IO::decrementBursts()
{
	for (unsigned int i = 0; i < processList.size(); i++)
		(*processList[i]).decrementBurst();
}