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

#include "Process.h"

using namespace std;

/********************************************************************************************
Name: Process
Description: Constructor for a Process object that accepts a processName and a vector of
 burst times
*********************************************************************************************/
Process::Process(string processName, const vector<int> & bursts)
{
	processID = processName;
	responseTime = 0;
	burstTimes = bursts;
	for (unsigned int i = 0; i < burstTimes.size(); i++)
		totalBurstTimes += burstTimes[i];
	hasNotBeenInCPU = true;
	queueLevel = 1; //default to 1st queue
	currentTimeInCPU = 0;
	timeCompleted = 0;
}

/********************************************************************************************
Name: getNextBurst
Description: Returns the first burst time from the vector burstTimes
*********************************************************************************************/
int Process::getNextBurst()
{
	return burstTimes[0];
}

/********************************************************************************************
Name: removeNextBurst
Description: Removes the first burst time from the vector burstTimes
*********************************************************************************************/
void Process::removeNextBurst()
{
	burstTimes.erase(burstTimes.begin());
}

/********************************************************************************************
Name: decrementBurst
Description: Decrements the first burst time in the vector burstTimes
*********************************************************************************************/
void Process::decrementBurst()
{
	burstTimes[0]--;
}

/********************************************************************************************
Name: remainingBursts
Description: Returns the number of bursts remaining in the vector burstTimes
*********************************************************************************************/
int Process::remainingBursts()
{
	return burstTimes.size();
}

/********************************************************************************************
Name: isCompletedProcess
Description: Returns true when no burst times are remaining in the vector burstTimes
*********************************************************************************************/
bool Process::isCompletedProcess()
{
	//checks if no bursts remaining
	return burstTimes.size() == 0;
}

/********************************************************************************************
Name: getProcessID
Description: Accessor for processID
*********************************************************************************************/
string Process::getProcessID() const
{
	return processID;
}

/********************************************************************************************
Name: getResponseTime
Description: Accessor for responseTime
*********************************************************************************************/
int Process::getResponseTime() const
{
	return responseTime;
}

/********************************************************************************************
Name: getTotalBurstTimes
Description: Accessor for totalBurstTimes
*********************************************************************************************/
int Process::getTotalBurstTimes() const
{
	return totalBurstTimes;
}

/********************************************************************************************
Name: getHasNotBeenInCPU
Description: Accessor for hasNotBeenInCPU
*********************************************************************************************/
int Process::getHasNotBeenInCPU() const
{
	return hasNotBeenInCPU;
}

/********************************************************************************************
Name: getQueueLevel
Description: Accessor for queueLevel
*********************************************************************************************/
int Process::getQueueLevel() const
{
	return queueLevel;
}

/********************************************************************************************
Name: getCurrentTimeInCPU
Description: Accessor for currentTimeInCPU
*********************************************************************************************/
int Process::getCurrentTimeInCPU() const
{
	return currentTimeInCPU;
}

/********************************************************************************************
Name: getTimeCompleted
Description: Accessor for timeCompleted
*********************************************************************************************/
int Process::getTimeCompleted() const
{
	return timeCompleted;
}

/********************************************************************************************
Name: hasBeenInCPU
Description: Changes value of hasNotBeenInCPU to false, indicating that the process has been
 in the CPU
*********************************************************************************************/
void Process::hasBeenInCPU()
{
	hasNotBeenInCPU = false;
}

/********************************************************************************************
Name: setResponseTime
Description: Sets the value of responseTime to the value of the parameter "time"
*********************************************************************************************/
void Process::setResponseTime(const int time)
{
	responseTime = time;
}

/********************************************************************************************
Name: setQueueLevel
Description: Sets the value of queueLevel to the value of the parameter "level"
*********************************************************************************************/
void Process::setQueueLevel(const int level)
{
	queueLevel = level;
}

/********************************************************************************************
Name: resetCurrentTimeInCPU
Description: Sets the value of currentTimeInCPU to 0
*********************************************************************************************/
void Process::resetCurrentTimeInCPU()
{
	currentTimeInCPU = 0;
}

/********************************************************************************************
Name: setCurrentTimeInCPU
Description: Sets the value of currentTimeInCPU to the value of the parameter "time"
*********************************************************************************************/
void Process::setCurrentTimeInCPU(const int time)
{
	currentTimeInCPU = time;
}

/********************************************************************************************
Name: setTimeCompleted
Description: Sets the value of timeCompleted to the value of the parameter "time"
*********************************************************************************************/
void Process::setTimeCompleted(const int time)
{
	timeCompleted = time;
}

/********************************************************************************************
Name: incrementCurrentTimeInCPU
Description: Increments the value of currentTimeInCPU
*********************************************************************************************/
void Process::incrementCurrentTimeInCPU()
{
	currentTimeInCPU++;
}