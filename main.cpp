#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

int main() {
    FILE *file;
    file = fopen("sample-jobs.dat", "w+");

    int data[100][3];
    char c;

    while()
    {
        for(int i = 0; i < 100; i++)
        {
            fscanf(file, "%d%d%d", data[i][0], data[i][1], data[i][2]);
            cout << endl;
        }
    }

    return 0;
}