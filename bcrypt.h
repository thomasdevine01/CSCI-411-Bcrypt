#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
#include <random>
#include "blowfish.h"
#include "base64.h"

using namespace std;

const string BCRYPT_CONSTANT = "OrpheanBeholderScryDoubt";
const string FILENAME = "cpp_output.txt";
const string CSV = "cpp_output.csv";
const int BCRYPT_SALT_SIZE = 16;
const int BCRYPT_ROUNDS = 12;

string generateSalt(int size);
void eksBlowfishSetup(Blowfish &bf, const string &password, const string &salt, int rounds);
string bcryptHash(Blowfish &bf, const string &constant);
string bcrypt(const string &password, string &bcryptSalt, int rounds = BCRYPT_ROUNDS);
string bcrypt(const string &password, const string &salt, string &bcryptSalt, int rounds = BCRYPT_ROUNDS);
