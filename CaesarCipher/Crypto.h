#ifndef CRYPTO_H
#define CRYPTO_H

#include <fstream>
using namespace std;

class Crypto
{
	char c;

public:
	Crypto();
	void Chiffrer(int);
	void Dechiffrer(int);
	string LireMessage(string);
	ofstream fichier_out;
	ifstream fichier_in;
};


#endif