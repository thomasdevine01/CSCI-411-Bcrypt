#include "bcrypt.h"

/**
 * https://www.geeksforgeeks.org/how-to-create-a-random-alpha-numeric-string-in-cpp/
*/
string generateSalt(int size) {
    string salt;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 255);

    for (int i = 0; i < size; ++i) {
        salt += static_cast<char>(dist(gen));
    }
    return salt;
}

/**
 * eksBlowfishSetup is the core function used in the bcrypt algorithm.
 * It sets the blowfish cipher 2^n times and alternates the order in which
 * it is done
*/
void eksBlowfishSetup(Blowfish &bf, const string &password, const string &salt, int rounds) {
    bf.SetKey(reinterpret_cast<const unsigned char *>(&salt), salt.size());
    for (int i = 0; i < pow(2, rounds); ++i) {
        bf.SetKey(reinterpret_cast<const unsigned char *>(password.data()), password.size());
        bf.SetKey(reinterpret_cast<const unsigned char *>(salt.data()), salt.size());
    }
}

/**
 * The blowfish cipher library uses unsigned char*
 * this was a very weird to do, but I found this
 * forum article that was very helpful by JLBorges
 * https://cplusplus.com/forum/beginner/139231/
*/
string bcryptHash(Blowfish &bf, const string &constant) {
    string text = constant;
    for (int i = 0; i < 2; i++) {
        bf.Encrypt(reinterpret_cast<unsigned char *>(text.data()),
                   reinterpret_cast<const unsigned char *>(text.data()), text.size());
    }
    return text;
}

/**
 * bcrypt algorithm to generate a salt, encode in base64, truncate the salt to
 * 22 characters, run the eksBlowfishSetup and output the salt
**/
string bcrypt(const string &password, string &bcryptSalt, int rounds) {
    string rawSalt = generateSalt(BCRYPT_SALT_SIZE);
    string base64Salt = base64_encode(rawSalt);
    //cut the salt to 22 char, defined in the Bcrypt standard
    bcryptSalt = string(base64Salt.begin(), base64Salt.begin() + 22);

    string bcryptSaltFormatted = "$2a$" + to_string(rounds) + "$" + bcryptSalt;

    Blowfish bf;
    eksBlowfishSetup(bf, password, bcryptSalt, rounds);

    string rawHash = bcryptHash(bf, BCRYPT_CONSTANT);
    string hash = base64_encode(rawHash);

    return bcryptSaltFormatted + "$" + hash;
}

// input a string to test if the implementation is consistant with itself
string bcrypt(const string &password, const string &salt, string &bcryptSalt, int rounds) {
    bcryptSalt = string(salt.begin(), salt.begin() + 22);

    string bcryptSaltFormatted = "$2a$" + to_string(rounds) + "$" + bcryptSalt;

    Blowfish bf;
    eksBlowfishSetup(bf, password, bcryptSalt, rounds);

    string rawHash = bcryptHash(bf, BCRYPT_CONSTANT);
    string hash = base64_encode(rawHash);

    return bcryptSaltFormatted + "$" + hash;
}