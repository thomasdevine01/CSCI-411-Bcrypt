/**
 * CSCI 411 Final Project
 * Thomas Devine
 * 
 * This is an implementation of the Bcrypt algorithm.
 * It is not the true algorithm because Bcrypt uses a
 * slightly modified implementation of base64 where 
 * some characters are swapped
*/

#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
#include "blowfish.h"
#include "base64.h"
#include "bcrypt.h"

using namespace std;

int main(int argc, char **argv){
    if (argc < 2) {
        cout << "Usage: ./bcrypt_demo <password> <salt>" << endl;
        return 1;
    }

    string password,
           hash,
           salt,
           bcryptSalt;

    if(argc == 3){
        password = argv[1],
        salt = argv[2];
        hash = bcrypt(password, salt, bcryptSalt);
    }
    else{
        hash = bcrypt(password, bcryptSalt);
    }

    cout << "Salt: " << bcryptSalt << endl;
    cout << "Hash: " << hash << endl;

    return 0;
}