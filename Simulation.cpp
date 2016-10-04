/********************************************************************************************
Name: Gavin Wolf		Z#: 15289719
Course: Computer Operating Systems - COP 4610
Professor: Dr. Borko Furht
Due Date: 10/22/2015
Programming Assignment - CPU Scheduler

Description: This program simulates CPU scheduling algorithms on a set of processes with
 specified CPU and I/O burst times.
*********************************************************************************************/

/********************************************************************************************
*********************************************************************************************

Name: Simulation.cpp
Description: The general methodology for this simulation is as follows:
	- Run a while loop that exits when all Processes are completed
	- In the body of the while loop, increment the current execution time and make all
	  necessary changes to the system, while keeping track of all relevant data
	- Output the state of the simulation at every context switch, i.e. every time the CPU
	  changes between Processes or between idle and a Process. Output shows where in the
	  system each Process is at the given time

*********************************************************************************************
*********************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "Process.h"
#include "ReadyQueue.h"
#include "IO.h"
#include "Completed.h"

using namespace std;

//Prototypes of simulation functions
void SimulateSingleReadyQueue(bool isSJF);
void SimulateMultiReadyQueue();

/********************************************************************************************
Name: main
Description: Prompts user to select which of the three algorithms to run and then calls the
 selected algorithm.
*********************************************************************************************/
int main()
{
	input:
	cout << "Enter the number corresponding to the scheduling algorithm you would like to run:\n\n"
		 << "1 - First Come First Serve (non-preemptive)\n"
		 << "2 - Shortest Job First (non-preemptive)\n"
		 << "3 - Multilevel Feedback Queue (preemptive - absolute priority in higher queues)\n"
		 << "    Queue 1 uses Round Robin scheduling with Time Quantum of 6\n"
		 << "    Queue 2 uses Round Robin scheduling with Time Quantum of 11\n"
		 << "    Queue 3 uses First Come First Serve\n\n";

	int algorithm;
	cin >> algorithm;

	if (algorithm == 1)
		SimulateSingleReadyQueue(false);
	else if (algorithm == 2)
		SimulateSingleReadyQueue(true);
	else if (algorithm == 3)
		SimulateMultiReadyQueue();
	else
		goto input;

	return 0;
}

//SETUP/OVERHEAD FOR SIMULATION FUNCTIONS:

//	Declaration of variables to track time
	int currentTime = 0; //current execution time
	int idleTime = 0; //time that no Process is in CPU

//  Prototypes of "helper" functions
	void AddProcessToCPU(Process & P, int currentTime);
	void SingleDisplay();
	void MultiDisplay();
	void MoveRQtoCPU(); //function to move a job from RQ to CPU

//  Creation of Process objects for each process with burst times ordered as follows: CPU, I/O, CPU, I/O, ... , CPU
	Process P1("P1", vector<int> { 4, 24, 5, 73, 3, 31, 5, 27, 4, 33, 6, 43, 4, 64, 5, 19, 2 });
	Process P2("P2", vector<int> { 18, 31, 19, 35, 11, 42, 18, 43, 19, 47, 18, 43, 17, 51, 19, 32, 10 });
	Process P3("P3", vector<int> { 6, 18, 4, 21, 7, 19, 4, 16, 5, 29, 7, 21, 8, 22, 6, 24, 5 });
	Process P4("P4", vector<int> { 17, 42, 19, 55, 20, 54, 17, 52, 15, 67, 12, 72, 15, 66, 14 });
	Process P5("P5", vector<int> { 5, 81, 4, 82, 5, 71, 3, 61, 5, 62, 4, 51, 3, 77, 4, 61, 3, 42, 5 });
	Process P6("P6", vector<int> { 10, 35, 12, 41, 14, 33, 11, 32, 15, 41, 13, 29, 11 });
	Process P7("P7", vector<int> { 21, 51, 23, 53, 24, 61, 22, 31, 21, 43, 20 });
	Process P8("P8", vector<int> { 11, 52, 14, 42, 15, 31, 17, 21, 16, 43, 12, 31, 13, 32, 15 });

//	Initialization of a pointer to a Process object called "ProcessInCPU". I use this variable
//	 to model the Process that is currently getting CPU time
	Process * ProcessInCPU = 0;

//	Creation of Lists for First Come First Serve and Shortest Job First algorithms.
//   Because there is only one ready queue needed for these algorithms, I named the objects
//	 "Single" followed by the type of list
	ReadyQueue SingleRQ; //ReadyQueue object
	IO SingleIO; //IO object
	Completed SingleCompleted; //Completed object

//	Creation of Lists for Multilevel Feedback Queue algorithm.
// 	 Because multiple ready queues are needed for this algorithm, I named the objects
//	 "Multi" followed by the type of the list
	ReadyQueue MultiRQ1; //ReadyQueue object: level 1 of ready queue - Round Robin, Tq = 6
	ReadyQueue MultiRQ2; //ReadyQueue object: level 2 of ready queue - Round Robin, Tq = 11
	ReadyQueue MultiRQ3; //ReadyQueue object: level 3 of ready queue - First Come First Serve
	IO MultiIO; //IO object
	Completed MultiCompleted; //Completed bbject

/********************************************************************************************
Name: SimulateSingleReadyQueue
Description: Simulates an algorithm requiring a "single" ready queue. Accepts a boolean
 parameter "isSJF". When isSJF is true, the algorithm simulated is Shortest Job First. When
 isSJF is false, the algorithm simulated is First Come First Serve
*********************************************************************************************/
void SimulateSingleReadyQueue(bool isSJF)
{
	//Add all Process objects to the ready queue
	SingleRQ.addProcess(P1);
	SingleRQ.addProcess(P2);
	SingleRQ.addProcess(P3);
	SingleRQ.addProcess(P4);
	SingleRQ.addProcess(P5);
	SingleRQ.addProcess(P6);
	SingleRQ.addProcess(P7);
	SingleRQ.addProcess(P8);

	//Sort the ready queue if Shortest Job First is selected
	if (isSJF) 
		SingleRQ.sortAscending();

	//Start simulation by moving first Process to CPU
	AddProcessToCPU(SingleRQ.removeProcess(), currentTime);
	SingleDisplay(); //Context switch --> display state of simulation

	//While loop runs until all Processes have been moved to the Completed list. This happens when 
	// the ready queue, IO list and CPU are all empty
	while (!(SingleRQ.isEmpty() && SingleIO.isEmpty() && ProcessInCPU == 0))
	{
		currentTime++; //Increment current execution time

		//Decrement remaining burst time of Process in CPU (if any)
		if (!(ProcessInCPU == 0))
			(*ProcessInCPU).decrementBurst();
		//Decrement remaining burst times of all Processes in IO (if any)
		if (!(SingleIO.isEmpty()))
			SingleIO.decrementBursts();

		//If there are Processes in IO that just completed their bursts --> move them to RQ
		// While loop accounts for multiple IO bursts finishing at the same time
		while (!(SingleIO.isEmpty()) && SingleIO.nextBurst() == 0) 
		{
			//Remove "completed" burst
			SingleIO.removeNextBurst();

			//Move process to ready queue
			SingleRQ.addProcess(SingleIO.removeProcess());

			//If Shortest Job First is selected, sort the ready queue so that the shortest next burst is at the front 
			// of the ready queue
			if (isSJF)
				SingleRQ.sortAscending();
		}

		if (ProcessInCPU == 0) //If no Process is in the CPU
		{
			idleTime++; //CPU was idle --> increment idleTime
	
			if (!(SingleRQ.isEmpty())) //If there is a Process in RQ --> move it to CPU
			{
				AddProcessToCPU(SingleRQ.removeProcess(), currentTime);
				SingleDisplay(); //CPU switches context --> so display state of simulation
			}
		}
		else //There is a Process in the CPU
		{
			if ((*ProcessInCPU).getNextBurst() == 0) //If the Process's CPU burst was just completed
			{
				(*ProcessInCPU).removeNextBurst();
				if ((*ProcessInCPU).isCompletedProcess()) //If Process completed, move it to Completed list
				{
					(*ProcessInCPU).setTimeCompleted(currentTime); //set completed time
					SingleCompleted.addProcess((*ProcessInCPU));
					ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
				}
				else //If Process still has bursts remaining --> move to IO
				{
					SingleIO.addProcess((*ProcessInCPU));
					ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
				}

				//If there is a Process in the ready queue --> move it to CPU
				if (!(SingleRQ.isEmpty()))
				{
					AddProcessToCPU(SingleRQ.removeProcess(), currentTime);
				}

				//The CPU just finished a burst --> context switch --> display state of the simulation
				SingleDisplay();
			}
		}
	}

	//Calculate and display end-of-simulation statistics
	double CPUUtilization = ((currentTime - idleTime) / (double)currentTime) * 100;
	
	cout << "::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		<< "Finished\n\n"
		 << "Total Time:         " << currentTime << "\n"
		 << "CPU Utilization:    " << setprecision(2) << fixed << CPUUtilization << "%\n\n"
		 << "Waiting Times       P1   P2   P3   P4   P5   P6   P7   P8   \n"
		 << "                    "; 
	SingleCompleted.displayWaitingTimes();
	cout << "Average Wait:       " << SingleCompleted.averageWaitingTime() << "\n\n";
	cout << "Turnaround Times    P1   P2   P3   P4   P5   P6   P7   P8   \n"
		<< "                    ";
	SingleCompleted.displayTurnaroundTimes();
	cout << "Average Turnaround: " << SingleCompleted.averageTurnaroundTime() << "\n\n";
	cout << "Response Times      P1   P2   P3   P4   P5   P6   P7   P8   \n"
		<< "                    ";
	SingleCompleted.displayResponseTimes();
	cout << "Average Response:   " << SingleCompleted.averageResponseTime() << "\n\n";
}

/********************************************************************************************
Name: AddProcessToCPU
Description: "Helper" function to add a Process to the CPU. Accepts a reference to a Process
 object and currentTime.
*********************************************************************************************/
void AddProcessToCPU(Process & P, int currentTime)
{
	ProcessInCPU = &P;
	if ((*ProcessInCPU).getHasNotBeenInCPU()) //If first time Process has been in the CPU...											
	{
		(*ProcessInCPU).setResponseTime(currentTime); //Set responseTime to currentTime
		(*ProcessInCPU).hasBeenInCPU(); //Indicate that the Process has been in the CPU
	}
}

/********************************************************************************************
Name: SingleDisplay
Description: "Helper" function for SimulateSingleReadyQueue to display the state of the 
 simulation after a context switch
*********************************************************************************************/
void SingleDisplay()
{
	cout << "::::::::::::::::::::::::::::::::::::::::::::::::::\n";

	string runningP = "Now running:  ";
	if (ProcessInCPU == 0)
		runningP += "[idle]\n";
	else
		runningP += (*ProcessInCPU).getProcessID()
		+ " (" + to_string((*ProcessInCPU).getNextBurst()) + " time units remaining)\n";

	cout << "Current time: " << currentTime << "\n" << runningP
		 << "..................................................\n";
	
	cout << "Ready Queue:  ";
	SingleRQ.display();
	SingleIO.display();
	SingleCompleted.display();
}

/********************************************************************************************
Name: SimulateMultiReadyQueue
Description: Simulates an algorithm requiring "multi"/multiple ready queues
*********************************************************************************************/
void SimulateMultiReadyQueue()
{
	//Add all Process objects to the first ready queue
	MultiRQ1.addProcess(P1);
	MultiRQ1.addProcess(P2);
	MultiRQ1.addProcess(P3);
	MultiRQ1.addProcess(P4);
	MultiRQ1.addProcess(P5);
	MultiRQ1.addProcess(P6);
	MultiRQ1.addProcess(P7);
	MultiRQ1.addProcess(P8);

	//Set time quantum for Round Robin queue level 1
	MultiRQ1.setTimeQuantum(6);

	//Set time quantum for Round Robin queue level 2
	MultiRQ2.setTimeQuantum(11);

	//Start simulation by moving first process to CPU
	AddProcessToCPU(MultiRQ1.removeProcess(), currentTime);
	MultiDisplay(); //Context switch --> display state of simulation

	//While loop runs until all Processes have been moved to the Completed list. This happens when 
	// the ready queues, IO list and CPU are all empty
	while (!(MultiRQ1.isEmpty() && MultiRQ2.isEmpty() && MultiRQ3.isEmpty() && 
			 MultiIO.isEmpty() && ProcessInCPU == 0))
	{
		currentTime++; //Increment current execution time

		//Decrement remaining burst time and increment current time in CPU of Process in CPU (if any)
		if (!(ProcessInCPU == 0))
		{
			(*ProcessInCPU).decrementBurst();
			(*ProcessInCPU).incrementCurrentTimeInCPU(); //will be used to compare to Time Quantum
		}
		//Decrement remaining burst times of all Processes in IO (if any)
		if (!(MultiIO.isEmpty()))
			MultiIO.decrementBursts();

		//If there are Processes in IO that just completed their bursts --> move them to the RQ
		// they came to IO from. While loop accounts for multiple IO bursts finishing at the 
		// same time
		while (!(MultiIO.isEmpty()) && MultiIO.nextBurst() == 0)
		{
			//Remove "completed" burst
			MultiIO.removeNextBurst();

			//Move Process to RQ it came from
			Process & P = MultiIO.removeProcess();
			if (P.getQueueLevel() == 1)
				MultiRQ1.addProcess(P);
			else if (P.getQueueLevel() == 2)
				MultiRQ2.addProcess(P);
			else
				MultiRQ3.addProcess(P);
		}

		if (ProcessInCPU == 0) //If no Process in CPU
		{
			idleTime++; //CPU was idle --> increment idleTime

			//If there is a Process in one of the RQ levels --> move the highest priority process to CPU
			if (!(MultiRQ1.isEmpty() && MultiRQ2.isEmpty() && MultiRQ3.isEmpty())) 
			{
				MoveRQtoCPU(); //"Helper" function to move a Process from RQ to CPU
				MultiDisplay(); //Process added to CPU --> context switch --> display state of simulation
			}
		}
		else //Process is in CPU
		{	
			//3 Cases to Consider:
			//  - Case 1:   Burst is complete
			//  - Case 2A:  Running Process came from RQ2 and another Process was just added to RQ1 --> preemption!
			//  - Case 2B:  Running Process came from RQ3 and another Process was just added to RQ1--> preemption!
			//  - Case 3:	Time Quantum expired

			//Case 1: Burst is complete
			if ((*ProcessInCPU).getNextBurst() == 0)
			{
				(*ProcessInCPU).removeNextBurst(); //Remove "completed" burst
				if ((*ProcessInCPU).isCompletedProcess()) //If Process is completed, move to Completed list
				{
					(*ProcessInCPU).setTimeCompleted(currentTime); //Set time completed
					MultiCompleted.addProcess((*ProcessInCPU));
					ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
				}
				else //If process still has bursts remaining --> move to IO
				{
					(*ProcessInCPU).resetCurrentTimeInCPU(); //Reset counter for next compare with Time Quantum
					MultiIO.addProcess((*ProcessInCPU));
					ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
				}

				//If there is a process in RQ --> move it to CPU
				if (!(MultiRQ1.isEmpty() && MultiRQ2.isEmpty() && MultiRQ3.isEmpty()))
				{
					MoveRQtoCPU(); //"Helper" function to move a Process from RQ to CPU
				}

				//CPU just finished a burst --> context switch --> display state of the simulation
				MultiDisplay();
			}
			//Case 2A: Running Process came from RQ2 and another Process was just added to RQ1 --> preemption!
			else if ((*ProcessInCPU).getQueueLevel() == 2 && !(MultiRQ1.isEmpty()))
			{
				(*ProcessInCPU).resetCurrentTimeInCPU();
				MultiRQ2.addProcess((*ProcessInCPU));
				ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
				MoveRQtoCPU(); //Add the higher-priority Process to CPU
				MultiDisplay(); //Context switch --> display state of simulation
			}
			//Case 2B: Running Process came from RQ3 and another Process was just added to RQ1
			// or RQ2 --> preemption!
			else if ((*ProcessInCPU).getQueueLevel() == 3 && (!(MultiRQ1.isEmpty()) || !(MultiRQ2.isEmpty())))
			{
				(*ProcessInCPU).resetCurrentTimeInCPU();
				MultiRQ3.addProcess((*ProcessInCPU)); //Take Process out of CPU, put it in front of RQ3
				ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
				MoveRQtoCPU(); //Add higher-priority Process to CPU
				MultiDisplay(); //Context switch --> display state of simulation
			}
			//Case 3: Time Quantum expired
			else
			{
				//If process came from RQ1 and its time slice has expired
				if ((*ProcessInCPU).getQueueLevel() == 1 && (*ProcessInCPU).getCurrentTimeInCPU() == MultiRQ1.getTimeQuantum())
				{
					(*ProcessInCPU).resetCurrentTimeInCPU(); //Reset current time in CPU to 0
					(*ProcessInCPU).setQueueLevel(2); //Change its queue level to 2
					MultiRQ2.addProcess((*ProcessInCPU)); //Move it to queue 2
					ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
					MoveRQtoCPU(); //Load next process (if any) into CPU
					MultiDisplay(); //Context switch --> display state of simulation
				}

				//If process came from RQ2 and its time slice has expired
				if ((*ProcessInCPU).getQueueLevel() == 2 && (*ProcessInCPU).getCurrentTimeInCPU() == MultiRQ2.getTimeQuantum())
				{
					(*ProcessInCPU).resetCurrentTimeInCPU(); //Reset current time in CPU to 0
					(*ProcessInCPU).setQueueLevel(3); //Change its queue level to 3
					MultiRQ3.addProcess((*ProcessInCPU)); //Move it to queue 3
					ProcessInCPU = 0; //Removed Process from CPU so ProcessInCPU pointer = 0
					MoveRQtoCPU(); //Load next process (if any) into CPU
					MultiDisplay(); //Context switch --> display state of simulation
				}
			}
		}
	}

	//Calculate and display end-of-simulation statistics
	double CPUUtilization = ((currentTime - idleTime) / (double)currentTime) * 100;

	cout << "::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		<< "Finished\n\n"
		<< "Total Time:         " << currentTime << "\n"
		<< "CPU Utilization:    " << setprecision(2) << fixed << CPUUtilization << "%\n\n"
		<< "Waiting Times       P1   P2   P3   P4   P5   P6   P7   P8   \n"
		<< "                    ";
	MultiCompleted.displayWaitingTimes();
	cout << "Average Wait:       " << MultiCompleted.averageWaitingTime() << "\n\n";
	cout << "Turnaround Times    P1   P2   P3   P4   P5   P6   P7   P8   \n"
		<< "                    ";
	MultiCompleted.displayTurnaroundTimes();
	cout << "Average Turnaround: " << MultiCompleted.averageTurnaroundTime() << "\n\n";
	cout << "Response Times      P1   P2   P3   P4   P5   P6   P7   P8   \n"
		<< "                    ";
	MultiCompleted.displayResponseTimes();
	cout << "Average Response:   " << MultiCompleted.averageResponseTime() << "\n\n";
}

/********************************************************************************************
Name: MoveRQtoCPU
Description: "Helper" function for SimulateMultiReadyQueue to move a a Process from one of 
 the ready queues to the CPU
*********************************************************************************************/
void MoveRQtoCPU()
{
	if (!(MultiRQ1.isEmpty())) //If there is a Process in RQ1
		AddProcessToCPU(MultiRQ1.removeProcess(), currentTime); //Add Process to CPU
	else if (!(MultiRQ2.isEmpty())) //If no Process in RQ1, Process in RQ2
		AddProcessToCPU(MultiRQ2.removeProcess(), currentTime); //Add Process to CPU
	else if (!(MultiRQ3.isEmpty()))//If no Process in RQ1, no Process in RQ2, Process in RQ3
		AddProcessToCPU(MultiRQ3.removeProcess(), currentTime); //Add Process to CPU
}

/********************************************************************************************
Name: MultiDisplay
Description: "Helper" function for SimulateMultiReadyQueue to display the state of the
simulation after a context switch
*********************************************************************************************/
void MultiDisplay()
{
	cout << "::::::::::::::::::::::::::::::::::::::::::::::::::\n";

	string runningP = "Now running:  ";
	if (ProcessInCPU == 0)
		runningP += "[idle]\n";
	else
		runningP += (*ProcessInCPU).getProcessID()
		+ " (" + to_string((*ProcessInCPU).getNextBurst()) + " time units remaining, Level = " 
		+ to_string((*ProcessInCPU).getQueueLevel()) + ")\n";

	cout << "Current time: " << currentTime << "\n" << runningP
		<< "..................................................\n";

	cout << "Ready Queue1: ";
	MultiRQ1.display();
	cout << "Ready Queue2: ";
	MultiRQ2.display();
	cout << "Ready Queue3: ";
	MultiRQ3.display();
	MultiIO.display();
	MultiCompleted.display();
}