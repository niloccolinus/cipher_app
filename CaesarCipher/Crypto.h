#ifndef CRYPTO_H
#define CRYPTO_H

#include <fstream>
using namespace std;

class Crypto
{
	char c;

public:
	Crypto();
	void ChiffrerCesar(int);
	void DechiffrerCesar(int);	
	void ChiffrerVigenere(string);
	void DechiffrerVigenere(string);
	void AnalyserFrequence();
	string LireMessage(string);
	void EffacerMessage(string);
	ofstream fichier_out;
	ifstream fichier_in;
	string fileName;
};


#endif
