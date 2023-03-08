#include <iostream>
#include <string>
#include "Crypto.h"


Crypto::Crypto() {
	c = 'a'; 
}

string Crypto::LireMessage(string fileName) {
	string message = "";
	fichier_in.open(fileName);

	if (fichier_in.fail()) {
		cout << "Erreur a l'ouverture du fichier..." << endl;
	}
	else {
		string line;

		while (std::getline(fichier_in, line) {
			message.append(line + "\n"); // on ajoute chaque ligne au message + un saut de ligne
		}
	}
	fichier_in.close();
	return message;
}

void Crypto::Chiffrer(int key) {
	string origine = LireMessage("origine.txt");
	string output = "";


	for (int i = 0; i < origine.length(); i++)
	{
		// vérifier si la lettre est une lettre alphabétique...
		if (isalpha(origine[i]))
		{
			c = origine[i];

			if (isupper(c)) {
				// décaler la lettre :
				// on utilise le code ASCII du caractère pour effectuer des opérations arithmétiques
				// c - 'A' est l'index dans l'alphabet de la lettre à l'index i (ex : 'I' - 'A' = 73 - 65 = 8)
				// on ajoute le décalage key
				// le modulo 26 permet d'assurer que l'index sera un index valide de l'alphabet
				// ex pour décaler Z de 3 : (25 + 3) % 26 = 2 ce qui correspond à C
				// on rajoute 'A' pour obtenir le code ASCII de la lettre chiffrée
				c = ((c - 'A') + key) % 26 + 'A';
			}
			else {
				// même chose pour lettres minuscules
				c = ((c - 'a') + key) % 26 + 'a';
			}
			output += c;

		}
		// ...sinon ajouter la lettre telle quelle au message chiffré
		else
		{
			output += origine[i];
		}
	}

	// enregistrer dans le fichier message.txt
	if (output.length() != 0) {
		fichier_out.open("message.txt");
		if (fichier_out.fail()) {
			cout << "Erreur a l'ouverture du fichier..." << endl;
		}
		else {
			fichier_out << output;
		}
		fichier_out.close();
	}
}

void Crypto::Dechiffrer(int key) {
	string message = LireMessage("message.txt");
	string decodedMsg;

	for (int i = 0; i < message.length(); i++)
	{

		if (isalpha(message[i]))
		{
			c = message[i];

			if (isupper(c)) {
				// algorithme semblable à celui de Chiffrer mais on enlève key au lieu de l'ajouter
				int index = ((c - 'A') - key) % 26;
				if (index < 0) index += 26; // ajustement pour les index négatifs
				c = index + 'A';
			}
			else {
				int index = ((c - 'a') - key) % 26;
				if (index < 0) index += 26;
				c = index + 'a';
			}

			decodedMsg += c;
		}
		else
		{
			decodedMsg += message[i];
		}
	}

	// imprimer le message décodé
	cout << decodedMsg << endl;
}
