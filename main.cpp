#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

void FIFO(int data[100][3], int a);
void SJF(int data[100][3], int a);
void BJF(int data[100][3], int a);
void STCF(int data[100][3], int n);

int main() {
    ifstream file ("sample-jobs.dat");

    if(file.is_open())
    {
        cout << "File opened correctly" << endl;
    }
    else{
        cout << "Failed" << endl;
    }

    int data[100][3];
    int i = 0;
    cout << "JID" << "\t" << "AT" << "\t" << "DT" << endl;

    while(!file.eof())
    {
        file >> data[i][0] >> ws >> data[i][1] >> ws >>data[i][2];
        cout << data[i][0] << "\t" << data[i][1] << "\t" << data[i][2] << endl;

        if(i == 99){
            break;
        }
        else{
            i++;
        }
    }

    FIFO(data, i);
    SJF(data, i);
    BJF(data, i);
    STCF(data, i);


    file.close();
    return 0;
}

void FIFO(int data[100][3], int a){
    cout << "\n" << "FIFO:" << endl;
    cout << "JID" << "\t" << "AT" << "\t" << "DT" << endl;
    for(int j = 0; j < a; j++){
        for(int i = 0; i < a-1; i++) {
            if (data[i][1] > data[i + 1][1]) {
                swap(data[i], data[i + 1]);
            }
        }
    }
    for(int i = 0; i < a; i++){
        cout << data[i][0] << "\t" << data[i][1] << "\t" << data[i][2] << endl;
    }

    int CompletionTime = data[0][1];
    int TurnAroundTime = 0;
    int StartTime = 0;
    int ResponseTime = 0;

    for(int k = 0; k < a; k++){
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

void SJF(int data[100][3], int a){
    cout << "\n" << "SJF:" << endl;
    cout << "JID" << "\t" << "AT" << "\t" << "DT" << endl;
    for(int j = 0; j < a; j++){
        for(int i = 0; i < a-1; i++) {
            if (data[i][1] > data[i + 1][1]) {
                swap(data[i], data[i + 1]);
            }
            else if(data[i][1] == data[i + 1][1] && data[i][2] > data[i + 1][2]){
                swap(data[i], data[i + 1]);
            }
        }
    }
    for(int i = 0; i < a; i++){
        cout << data[i][0] << "\t" << data[i][1] << "\t" << data[i][2] << endl;
    }

    int CompletionTime = data[0][1];
    int TurnAroundTime = 0;
    int StartTime = 0;
    int ResponseTime = 0;

    for(int k = 0; k < a; k++){
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


void BJF(int data[100][3], int a){
    cout << "\n" << "BJF:" << endl;
    cout << "JID" << "\t" << "AT" << "\t" << "DT" << endl;
    for(int j = 0; j < a; j++){
        for(int i = 0; i < a-1; i++) {
            if (data[i][1] > data[i + 1][1]) {
                swap(data[i], data[i + 1]);
            }
            else if(data[i][1] == data[i + 1][1] && data[i][2] < data[i + 1][2]){
                swap(data[i], data[i + 1]);
            }
        }
    }
    for(int i = 0; i < a; i++){
        cout << data[i][0] << "\t" << data[i][1] << "\t" << data[i][2] << endl;
    }

    int CompletionTime = data[0][1];
    int TurnAroundTime = 0;
    int StartTime = 0;
    int ResponseTime = 0;

    for(int k = 0; k < a; k++){
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


void STCF(int data[100][3], int n)
{
    int StartTime[n];
    int FinishTime[n];
    int ResponseTime[n];
    int TotalTime[n];

    int big = 999;
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

    //Wait time
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

        if (pdone == false) { //Job is completed, no new jobs during this time period. Increment time.
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
            FinishTime[shortest] = finish_time - data[shortest][1]; //Completion time - Arrival time
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
