#include <fstream>
#include "bcrypt.h"

using namespace std;
int main(){

    cout << "Init Tests" << endl;
    
    fstream file("tests/passwords.txt", fstream::in);

    int testnum = 1,
        testsPassed = 0,
        testsFailed = 0;

    string test,
           hash,
           originalSalt;

    string linebreak = "---------------------------------------";

    if(!file.is_open()){
        return -1;
    }
    while(getline(file, test)){
        string salt;
        cout << linebreak << endl;
        cout << "Test #" << testnum << endl;
        
        hash = bcrypt(test, salt);

        cout << "Salt: " << salt << endl;
        cout << "Hash: " << hash << endl;

        cout << endl;

        originalSalt = salt;

        hash = bcrypt(test, originalSalt, salt);

        cout << "Salt: " << salt << endl;
        cout << "Hash: " << hash << endl;

        if(originalSalt == salt){
            cout << "Test passed" << endl;
            testsPassed++;
        }
        else{
            cout << "Test failed" << endl;
            testsFailed++;
        }
        testnum++;
    }

    return 0;
}