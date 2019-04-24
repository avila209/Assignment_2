#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {

    ifstream file ("sample-jobs.dat");

    if(file.is_open())
    {
        cout << "file opened correctly" << endl;
    }
    else{
        cout << "Failed" << endl;
    }
    string ss;


    int data[100][3];

    while(!file.eof())
    {
        for(int i = 0; i < 100; i++)
        {
            file >> data[i][0] >> ws >> data[i][1] >> ws >>data[i][2];
            cout << data[i][0] << " " << data[i][1] << " " << data[i][2] << endl;
        }
    }

    file.close();
    return 0;
}