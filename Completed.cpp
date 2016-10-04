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
#include "Completed.h"

using namespace std;

/********************************************************************************************
Name: addProcess
Description: Accepts a reference to a Process object and adds the object to the Completed 
 object's processList in order, sorted by processID
*********************************************************************************************/
void Completed::addProcess(Process & P)
{
	processList.push_back(&P);
	sort(processList.begin(), processList.end(), lowerProcessNumber());
}

/********************************************************************************************
Name: display
Description: Displays the processID for all Processes on the Completed object's processList
*********************************************************************************************/
void Completed::display()
{
	cout << "Completed:    ";

	if (isEmpty())
		cout << "[empty]";

	for (unsigned int i = 0; i < processList.size(); i++)
	{
		cout << (*processList[i]).getProcessID() << "  ";
	}
	cout << "\n";
}

/********************************************************************************************
Name: averageWaitingTime
Description: Calculates and returns the average waiting time of all Processes on the
 Completed object's processList
*********************************************************************************************/
double Completed::averageWaitingTime()
{
	int sum = 0;

	for (unsigned int i = 0; i < processList.size(); i++)
	{
		sum += ((*processList[i]).getTimeCompleted() - (*processList[i]).getTotalBurstTimes());
	}

	return sum / (double)processList.size();
}

/********************************************************************************************
Name: displayWaitingTimes
Description: Calculates and outputs average waiting time for all Processes on the Completed 
 object's processList
*********************************************************************************************/
void Completed::displayWaitingTimes()
{
	for (unsigned int i = 0; i < processList.size(); i++)
		cout << (*processList[i]).getTimeCompleted() - (*processList[i]).getTotalBurstTimes() <<
		((*processList[i]).getTimeCompleted() - (*processList[i]).getTotalBurstTimes() < 100 ? " " : "") << "  ";

	cout << endl;
}

/********************************************************************************************
Name: averageTurnaroundTime
Description: Calculates and returns average turnaround time for all Processes on the Completed
 object's processList
*********************************************************************************************/
double Completed::averageTurnaroundTime()
{
	int sum = 0;

	for (unsigned int i = 0; i < processList.size(); i++)
		sum += (*processList[i]).getTimeCompleted();

	return sum / (double)processList.size();
}

/********************************************************************************************
Name: displayTurnaroundTimes
Description: Calculates and displays the turnaround time for all Processes on the Completed
 object's processList. Note: because the simulation assumes that all jobs arrive at time 0,
 the turnaround time is equal to timeCompleted
*********************************************************************************************/
void Completed::displayTurnaroundTimes()
{
	for (unsigned int i = 0; i < processList.size(); i++)
		cout << (*processList[i]).getTimeCompleted() << "  ";

	cout << endl;
}

/********************************************************************************************
Name: averageResponseTime
Description: Calculates and returns the average response time of all Processes on the 
 Completed object's processList.
*********************************************************************************************/
double Completed::averageResponseTime()
{
	int sum = 0;

	for (unsigned int i = 0; i < processList.size(); i++)
		sum += (*processList[i]).getResponseTime();

	return sum / (double)processList.size();
}

/********************************************************************************************
Name: averageResponseTime
Description: Displays the response times for all Processes on the Completed object's 
 processList.
*********************************************************************************************/
void Completed::displayResponseTimes()
{
	for (unsigned int i = 0; i < processList.size(); i++)
		cout << (*processList[i]).getResponseTime() << ((*processList[i]).getResponseTime() < 10 ? " " : "") << "   ";

	cout << endl;
}