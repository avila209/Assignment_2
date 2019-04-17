#include <iostream>
#include <fstream>
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

    int data[100][3];

    while(!file.eof())
    {
        for(int i = 0; i < 100; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                file >> data[i][j];
                cout << data[i][j];
            }
            cout << endl;
        }
    }

    file.close();
    return 0;
}