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
	void EffacerMessage(string);
	bool Init();
	ofstream fichier_out;
	ifstream fichier_in;
};


#endif
