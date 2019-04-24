#include <iostream>
#include <fstream>

using namespace std;

void FIFO(int data[100][3], int a);

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


}