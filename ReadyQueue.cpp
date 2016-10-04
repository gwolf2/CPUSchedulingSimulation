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

#include "Process.h"
#include "ReadyQueue.h"

using namespace std;

/********************************************************************************************
Name: display
Description: Displays the name and next burst time for all Processes on the ReadyQueue
object's processList
*********************************************************************************************/
void ReadyQueue::display()
{
	//"Ready Queue:  Process    Burst\n"
	cout << "Process    Burst\n";

	if (isEmpty())
		cout << "              [empty]\n";

	for (unsigned int i = 0; i < processList.size(); i++)
	{
		cout << "              " << (*processList[i]).getProcessID()
			 << "         " << (*processList[i]).getNextBurst() << endl;
	}

	cout << "..................................................\n";
}