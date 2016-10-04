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

#ifndef Process_H
#define Process_H

/********************************************************************************************
Name: Process class
Description: The Process class, similar to a process control block, keeps track of all the
 pertinent data for a Process as it moves through the system
*********************************************************************************************/
class Process
{
public:
	Process(string Process, const vector<int> & bTimes); //constructor
	int getNextBurst();
	void removeNextBurst();
	void decrementBurst(); //used to decrement burst time
	int remainingBursts(); //returns the number of bursts remaining
	void hasBeenInCPU(); //mutator for isNoTimeInCPU
	void setResponseTime(const int time);
	void setQueueLevel(const int level);
	void resetCurrentTimeInCPU();
	void setCurrentTimeInCPU(const int time);
	void incrementCurrentTimeInCPU();
	void setTimeCompleted(const int time);
	bool isCompletedProcess();

	//accessors
	string getProcessID() const;
	int getTotalBurstTimes() const;
	int getResponseTime() const;
	int getHasNotBeenInCPU() const;
	int getQueueLevel() const;
	int getCurrentTimeInCPU() const;
	int getTimeCompleted() const;

private:
	string processID; //process name: P1, P2, P3, etc.
	vector<int> burstTimes; //array of burst times
	int totalBurstTimes; //sum of all burst times
	int responseTime; //time until first CPU time
	bool hasNotBeenInCPU; //flag that be used when calculating responseTime
	int queueLevel; //for Multilevel Feedback Queue
	int currentTimeInCPU; //for Round Robin to compare to Time Quantum
	int timeCompleted; //current time when process completes execution
};

/********************************************************************************************
Name: shorterNextBurst struct
Description: Enables sorting based on next burst
*********************************************************************************************/
struct shorterNextBurst
{
	inline bool operator() (Process * ProcessA, Process * ProcessB)
	{
		return ((*ProcessA).getNextBurst() < (*ProcessB).getNextBurst());
	}
};

/********************************************************************************************
Name: lowerProcessNumber struct
Description: Enables sorting by ProcessID
*********************************************************************************************/
struct lowerProcessNumber
{
	inline bool operator() (Process * ProcessA, Process * ProcessB)
	{
		return ((*ProcessA).getProcessID() < (*ProcessB).getProcessID());
	}
};

#endif