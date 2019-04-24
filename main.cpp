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
    int i = 0;

    while(!file.eof())
    {
        file >> data[i][0] >> ws >> data[i][1] >> ws >>data[i][2];
        cout << data[i][0] << " " << data[i][1] << " " << data[i][2] << endl;

        if(i == 99){
            break;
        }
        else{
            i++;
        }
    }

    file.close();
    return 0;
}