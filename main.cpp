#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>

using namespace std;

void FIFO(int data[100][3], int a);
void SJF(int data[100][3], int a);
void BJF(int data[100][3], int a);
void STCF(int data[100][3], int a);
void RR(int data[100][3], int a, int QT);

int main() {
    ifstream file ("sample-jobs.dat");

    if(file.is_open()){
        cout << "File opened correctly." << endl;
    }
    else{
        cout << "Failed" << endl;
    }

    int data[100][3];
    int i = 0;
    cout << "JID" << "\t" << "AT" << "\t" << "DT" << endl;

    while(!file.eof()){
        file >> data[i][0] >> ws >> data[i][1] >> ws >>data[i][2];
        cout << data[i][0] << "\t" << data[i][1] << "\t" << data[i][2] << endl;

        if(i == 99){
            break;
        }
        i++;
    }

    int QT;
    cout << endl << "Please enter the Quantum time for Round Robin Scheduling: ";
    cin >> QT;

    int data1[i][3];
    int data2[i][3];
    int data3[i][3];
    int data4[i][3];

    //Clone data so functions don't interfere with original data.
    for(int j=0; j < i; j++){
        data1[j][0] = data[j][0]; data1[j][1] = data[j][1]; data1[j][2] = data[j][2];
        data2[j][0] = data[j][0]; data2[j][1] = data[j][1]; data2[j][2] = data[j][2];
        data3[j][0] = data[j][0]; data3[j][1] = data[j][1]; data3[j][2] = data[j][2];
        data4[j][0] = data[j][0]; data4[j][1] = data[j][1]; data4[j][2] = data[j][2];
    }

    FIFO(data, i);
    SJF(data1, i);
    BJF(data2, i);
    STCF(data3, i);
    RR(data4, i, QT);

    file.close();
    return 0;
}

void FIFO(int data[100][3], int n){
    cout << "\n" << "FIFO:" << endl;
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n-1; i++) {
            if (data[i][1] > data[i + 1][1]) {
                swap(data[i], data[i + 1]);
            }
        }
    }

    int CompletionTime = data[0][1];
    int TurnAroundTime = 0;
    int StartTime = 0;
    int ResponseTime = 0;

    for(int k = 0; k < n; k++){
        if(data[k][1] < CompletionTime){
            StartTime = CompletionTime;
            CompletionTime += data[k][2];
        }
        else{
            CompletionTime = (data[k][1] + data[k][2]);
            StartTime = data[k][1];
        }
        TurnAroundTime = CompletionTime - data[k][1];
        ResponseTime = StartTime - data[k][1];

        cout << "Job ID: " << data[k][0] << "\t Start Time = " << StartTime
             << ",\t Finish Time = " << TurnAroundTime << ", \t Total Time = "
             << CompletionTime << ", \t Response Time = "<< ResponseTime << endl;
    }
}

void SJF(int data[100][3], int n){
    cout << "\n" << "SJF:" << endl;
    //Sorts by arrival time and burst time
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n-1; i++) {
            if (data[i][1] > data[i + 1][1]) {
                swap(data[i], data[i + 1]);
            }
            else if(data[i][1] == data[i + 1][1] && data[i][2] > data[i + 1][2]){
                swap(data[i], data[i + 1]);
            }
        }
    }

    int Total = 0;
    int Current  = 0;

    int FinishTime = 0, StartTime = 0, ResponseTime = 0;

    for(int k = 0; k < n; k++){
        Total += data[k][2];
    }

    int Complete = 0;
    while(Current < Total){
        for(int k = Complete; k < n; k++) { //Remaining processes
            //Swap remaining based on burst time alone
            for(int i = Complete; i < n; i++){
                for(int j = Complete; j < n-1; j++){
                    if(data[j][2] > data[j+1][2] && data[j+1][1] <= Current){
                        swap(data[j], data[j+1]);
                    }
                }
            }

            if (data[k][1] <= Current) {
                StartTime = Current;

                Current = data[k][2] + Current; //Actual Code
                Complete++;                     //Rest is just Calculations within the for loop

                FinishTime = Current - StartTime;
                ResponseTime = StartTime - data[k][1];
                cout << "Job ID: " << data[k][0] << "\t Start Time = " << StartTime
                     << ",\t Finish Time = " << FinishTime << ", \t Total Time = "
                     << Current << ", \t Response Time = "<< ResponseTime << endl;
                continue;
            } else {
                Current++;
            }
        }
    }
}

void BJF(int data[100][3], int n){
    cout << "\n" << "BJF:" << endl;
    //Sorts by arrival time and burst time
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n-1; i++) {
            if (data[i][1] > data[i + 1][1]) {
                swap(data[i], data[i + 1]);
            }
            else if(data[i][1] == data[i + 1][1] && data[i][2] < data[i + 1][2]){
                swap(data[i], data[i + 1]);
            }
        }
    }

    int Total = 0;
    int Current  = 0;

    int FinishTime = 0, StartTime = 0, ResponseTime = 0;

    for(int k = 0; k < n; k++){
        Total += data[k][2];
    }

    //Need to add sort by completion time if arrival is less than Current
    int Complete = 0;
    while(Current < Total){
        for(int k = Complete; k < n; k++) { //Remaining processes
            //Swap remaining based on burst time alone
            for(int i = Complete; i < n; i++){
                for(int j = Complete; j < n-1; j++){
                    if(data[j][2] < data[j+1][2] && data[j+1][1] <= Current){
                        swap(data[j], data[j+1]);
                    }
                }
            }

            if (data[k][1] <= Current) {
                StartTime = Current;

                Current = data[k][2] + Current; //Actual Code
                Complete++;                     //Rest is just Calculations within the for loop

                FinishTime = Current - StartTime;
                ResponseTime = StartTime - data[k][1];
                cout << "Job ID: " << data[k][0] << "\t Start Time = " << StartTime
                     << ",\t Finish Time = " << FinishTime << ", \t Total Time = "
                     << Current << ", \t Response Time = "<< ResponseTime << endl;
                continue;
            } else {
                Current++;
            }
        }
    }
}

void STCF(int data[100][3], int n){
    int StartTime[n];
    int FinishTime[n];
    int ResponseTime[n];
    int TotalTime[n];

    int big = 999999;
    int RemainingTime[n]; //Remaining time for each process starting with the burst times.

    for (int i = 0; i < n; i++){
        RemainingTime[i] = data[i][2]; //Inserting burst time data as initial remaining time.
        StartTime[i] = -1;
    }

    int complete = 0;
    int time = 0;
    int min = big;
    int shortest = 0, finish_time;
    bool pdone = false;

    cout << "\n" << "STCF:" << endl;

    while (complete != n) {

        for (int j = 0; j < n; j++) { //Check for the shortest runtime process, at or before the current time period which is not yet completed.
            if ((data[j][1] <= time) && (RemainingTime[j] < min) && RemainingTime[j] > 0) {
                min = RemainingTime[j];
                shortest = j;
                pdone = true;

                if(StartTime[j] == -1) { //Start time of each process, using -1 as a filled/not filled signal.
                    StartTime[j] = time;
                }
            }
        }

        if (!pdone) { //Job is completed, no new jobs during this time period. Increment time.
            time++;
            continue;
        }

        RemainingTime[shortest]--; //Job has ran for one clock cycle, decrement remaining time.
        min = RemainingTime[shortest];

        if (min == 0) {  //If min is zero, the process is done, reset value for next process
            min = big;
        }

        if (RemainingTime[shortest] == 0) { //Process complete, move to next process, reset process done flag
            complete++;
            pdone = false;

            finish_time = time + 1;

            TotalTime[shortest] = finish_time; //Total time = Completion time
            FinishTime[shortest] = finish_time - data[shortest][1]; //Finish time = Completion time - Arrival time
        }
        time++; //Increment time
    }

    //Response time
    for (int i = 0; i < n; i++) {
        ResponseTime[i] = StartTime[i] - data[i][1]; //Response time = Start time - Arrival time
    }

    //Print
    for(int k = 0; k < n; k++){
        cout << "Job ID: " << data[k][0] << "\t Start Time = " << StartTime[k]
             << ",\t Finish Time = " << FinishTime[k] << ", \t Total Time = "
             << TotalTime[k] << ", \t Response Time = "<< ResponseTime[k] << endl;
    }
}

void RR(int data[100][3], int n, int QT){
    cout << "\n" << "RR:" << endl;
    //Sorts by arrival time
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n-1; i++) {
            if (data[i][1] > data[i + 1][1]) {
                swap(data[i], data[i + 1]);
            }
        }
    }

    int Total = 0;
    int Current  = 0;

    int FinishTime[n];
    int StartTime[n];
    int TotalTime[n];
    int ResponseTime[n];

    int Remaining[n];

    for(int k = 0; k < n; k++){
        Total += data[k][2];
        Remaining[k] = data[k][2];
        StartTime[k] = -1;
        ResponseTime[k] = -1;
    }

    int Complete = 0;
    while(Current < Total){
        for(int k = 0; k < n; k++){ //Cycle through all processes
            if(StartTime[k] == -1){
                StartTime[k] = Current;
                ResponseTime[k] = Current - data[k][1]; //Start time - Arrival time
            }

            if(Remaining[k] <= QT && Remaining[k] > 0){ //If can be done within QT and not already complete
                Current = Remaining[k] + Current; //Current = Current time + burst time of process
                Remaining[k] = 0;

                TotalTime[k] = Current; //Completion time
                FinishTime[k] = Current - data[k][1]; //Completion time - Arrival time

                Complete++; //Process complete
            }
            else if(Remaining[k] > QT){
                Remaining[k] = Remaining[k] - QT;
                Current += QT;
            }
        }
    }

    //Print
    for(int k = 0; k < n; k++){
        cout << "Job ID: " << data[k][0] << "\t Start Time = " << StartTime[k]
             << ",\t Finish Time = " << FinishTime[k] << ", \t Total Time = "
             << TotalTime[k] << ", \t Response Time = "<< ResponseTime[k] << endl;
    }
}