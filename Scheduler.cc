#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class Process {
    public:
        int processID;
        int arrivalTime;
        int burstDuration;
        int priority;
};

void bubbleSortByArrivalTime(Process* processArray, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (processArray[j].arrivalTime > processArray[j + 1].arrivalTime) {
                // Swap the processes if they are out of order
                Process temp = processArray[j];
                processArray[j] = processArray[j + 1];
                processArray[j + 1] = temp;
            }
        }
    }
}





void priorityScheduling(Process* processArray, int lineCount) {
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    bool* isProcessDone = new bool[lineCount]();
    
    while (true) {
        int highestPriority = 32000000;
        int highestPriorityIndex = -1;

        // Find the highest priority process that has arrived
        for (int i = 0; i < lineCount; i++) {
            if (!isProcessDone[i] && processArray[i].arrivalTime <= currentTime && processArray[i].priority < highestPriority) {
                highestPriority = processArray[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            // No process with higher priority is available, find the next available process
            int nextProcessIndex = -1;
            for (int i = 0; i < lineCount; i++) {
                if (!isProcessDone[i] && processArray[i].arrivalTime > currentTime) {
                    nextProcessIndex = i;
                    break;
                }
            }

            if (nextProcessIndex == -1) {
                // No more processes are left to execute
                break;
            }

            // Wait for the next process to arrive
            currentTime = processArray[nextProcessIndex].arrivalTime;
            continue;
        }

        // Execute the highest priority process for one unit of time
        processArray[highestPriorityIndex].burstDuration--;

        // Update the waiting time for other processes
        for (int i = 0; i < lineCount; i++) {
            if (!isProcessDone[i] && i != highestPriorityIndex && processArray[i].arrivalTime <= currentTime) {
                totalWaitingTime++;
            }
        }

        // Check if the current process is done
        if (processArray[highestPriorityIndex].burstDuration == 0) {
            isProcessDone[highestPriorityIndex] = true;
            int turnaroundTime = currentTime - processArray[highestPriorityIndex].arrivalTime;
            totalTurnAroundTime += turnaroundTime;
        }
        
        // Update the current time
        currentTime++;
    }

    cout << "--- Preemptive Priority Scheduling ---" << endl;

    double averageTurnAroundTime = static_cast<double>(totalTurnAroundTime) / lineCount;
    cout << "Average turnaround time: " << averageTurnAroundTime << endl;

    // Calculate the average waiting time
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / lineCount;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    double averageThroughPut = lineCount / static_cast<double>(currentTime);
    cout << "Average ThroughPut: " << averageThroughPut << endl << endl;

    delete[] isProcessDone;
}






void FCFS(Process* processArray, int lineCount){
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    for (int i = 0; i < lineCount; i++) {
        // If the process has not arrived yet, wait for it to arrive
        if (processArray[i].arrivalTime > currentTime) {
            totalWaitingTime += (processArray[i].arrivalTime - currentTime);
            currentTime = processArray[i].arrivalTime;
        }

        // Calculate the waiting time for the current process
        int waitingTime = currentTime - processArray[i].arrivalTime;

        // Update the total waiting time
        totalWaitingTime += waitingTime;

        // Update the current time
        currentTime += processArray[i].burstDuration;

        // Calculate the turnaround time for the current process
        int turnaroundTime = currentTime - processArray[i].arrivalTime;

        // Update the total turnaround time
        totalTurnAroundTime += turnaroundTime;
    }

    cout << "--- FCFS ---" << endl;

    double averageTurnAroundTime = static_cast<double>(totalTurnAroundTime) / lineCount;
    cout << "Average turnaround time: " << averageTurnAroundTime << endl;

    // Calculate the average waiting time
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / lineCount;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    double averageThroughPut = lineCount / static_cast<double>(currentTime);
    cout << "Arerage ThroughPut: " << averageThroughPut << endl << endl;

}


void SJF(Process* processArray, int lineCount){
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    for (int i = 0; i < lineCount; i++) {
        // Find the index of the shortest job that has arrived
        int shortestJobIndex = -1;
        int shortestJobDuration = 32000000;

        for (int j = 0; j < lineCount; j++) {
            if (processArray[j].arrivalTime <= currentTime && processArray[j].burstDuration < shortestJobDuration) {
                shortestJobIndex = j;
                shortestJobDuration = processArray[j].burstDuration;
            }
        }

        if (shortestJobIndex == -1) {
            // No job has arrived yet, so wait for the next arrival
            currentTime = processArray[i].arrivalTime;
            i--;
            continue;
        }

        // Calculate the waiting time for the current process
        int waitingTime = currentTime - processArray[shortestJobIndex].arrivalTime;

        // Update the total waiting time
        totalWaitingTime += waitingTime;

        // Update the current time
        currentTime += processArray[shortestJobIndex].burstDuration;

        // Calculate the turnaround time for the current process
        int turnaroundTime = currentTime - processArray[shortestJobIndex].arrivalTime;

        // Update the total turnaround time
        totalTurnAroundTime += turnaroundTime;

        // Mark the job as processed
        processArray[shortestJobIndex].burstDuration = 32000000;
    }

    cout << "--- SJF ---" << endl;

    double averageTurnAroundTime = static_cast<double>(totalTurnAroundTime) / lineCount;
    cout << "Average turnaround time: " << averageTurnAroundTime << endl;

    // Calculate the average waiting time
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / lineCount;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    double averageThroughPut = lineCount / static_cast<double>(currentTime);
    cout << "Average ThroughPut: " << averageThroughPut << endl << endl;
}







int main(){
    

    ifstream fin("CS370-HW5-Input.csv");
    if(!fin.is_open()){
        cout << "Failed to open file";
        return 0;
    }

    string processID, arrivalTime, burstDuration, priority;
    string line;
    int lineCount = 0;

    while(getline(fin, line)){
        lineCount++;
    }

    Process* processArray = new Process[lineCount];

    fin.close();
    fin.open("CS370-HW5-Input.csv");
    
    int index = 0;

    while(getline(fin,line)){
        //<ProcessID>,<Arrival Time>, <Burst Duration>, <Priority>

        stringstream ss(line);
        getline(ss,processID,',');
        getline(ss,arrivalTime,',');
        getline(ss,burstDuration,',');
        getline(ss,priority,',');

        Process pro;
        pro.processID = stoi(processID);
        pro.arrivalTime = stoi(arrivalTime);
        pro.burstDuration = stoi(burstDuration);
        pro.priority = stoi(priority);

        processArray[index] = pro;
        index++;
    }


    fin.close();

    bubbleSortByArrivalTime(processArray, lineCount);
    FCFS(processArray, lineCount);
    SJF(processArray, lineCount);

    fin.close();
    fin.open("CS370-HW5-Input.csv");
    
    index = 0;
    Process* processArray2 = new Process[lineCount];

    while(getline(fin,line)){
        //<ProcessID>,<Arrival Time>, <Burst Duration>, <Priority>

        stringstream ss(line);
        getline(ss,processID,',');
        getline(ss,arrivalTime,',');
        getline(ss,burstDuration,',');
        getline(ss,priority,',');

        Process pro;
        pro.processID = stoi(processID);
        pro.arrivalTime = stoi(arrivalTime);
        pro.burstDuration = stoi(burstDuration);
        pro.priority = stoi(priority);

        processArray2[index] = pro;
        index++;
    }


    fin.close();


    priorityScheduling(processArray2, lineCount);
    delete[] processArray;
    delete[] processArray2;
}




