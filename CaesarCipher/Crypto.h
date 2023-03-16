#ifndef CRYPTO_H
#define CRYPTO_H

#include <fstream>
using namespace std;

class Crypto
{
	char c;
	int x;

public:
	Crypto();
	void ChiffrerCesar(int);
	void DechiffrerCesar(int);	
	void ChiffrerVigenere(string);
	void DechiffrerVigenere(string);
	int AnalyserFrequence(string);
	string LireMessage(string);
	void EffacerMessage(string);
	bool Init();
	ofstream fichier_out;
	ifstream fichier_in;
	int key;
};


#endif
