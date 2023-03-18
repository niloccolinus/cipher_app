#include <iostream>
#include <string>
#include "Crypto.h"

// constructeur
Crypto::Crypto() {
	c = 'a';
	fileName = "";
}

string Crypto::LireMessage(string fileName) {
	string message = "";
	fichier_in.open(fileName);

	if (fichier_in.fail()) {
		cout << "Erreur a l'ouverture du fichier..." << endl;
		cout << "Veuillez vérifier que le fichier existe et qu'il est placé à la racine du projet." << endl;
	}
	else {
		string line;

		while (std::getline(fichier_in, line)) {
			message.append(line + "\n"); // on ajoute chaque ligne au message + un saut de ligne
		}
	}
	fichier_in.close();
	return message;
}

void Crypto::EffacerMessage(string fileName) {
	string output = "";
	fichier_out.open(fileName);
	if (fichier_out.fail()) {
		cout << "Erreur a l'ouverture du fichier..." << endl;
		cout << "Veuillez vérifier que le fichier existe et qu'il est placé à la racine du projet." << endl;
	}
	else {
		fichier_out << output;
	}
	fichier_out.close();
}

void Crypto::ChiffrerCesar(int key) {
	string origine = LireMessage(fileName);
	string output = "";

	// vérifier que le message n'est pas vide
	if (origine.length() == 0) {
		cout << "Le message d'origine est vide !" << endl;
		return; // s'il est vide on sort de la fonction, le reste ne s'exécute pas
	}

	for (int i = 0; i < origine.length(); i++)
	{
		// vérifier si le caractère est une lettre alphabétique...
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
		// ...sinon ajouter le caractère tel quel au message chiffré
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
			cout << "Veuillez vérifier que le fichier existe et qu'il est placé à la racine du projet." << endl;
		}
		else {
			fichier_out << output;
			// succès
			cout << "Le message a été chiffré avec succès." << endl;
			cout << "Vous trouverez le message dans le fichier 'message.txt'." << endl;
		}
		fichier_out.close();
	}


}

void Crypto::DechiffrerCesar(int key) {
	string message = LireMessage(fileName);
	string decodedMsg;

	if (message.length() == 0) {
		cout << "Le message d'origine est vide !" << endl;
		return;
	}
	else {
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

		cout << "Le message a été déchiffré avec succès." << endl;
		cout << "Voici le message déchiffré :\n" << endl;
		// imprimer le message décodé
		cout << decodedMsg << endl;
	}

}


void Crypto::ChiffrerVigenere(string key) {
	string origine = LireMessage(fileName);
	string output = "";
	int keyIndex = 0;
	int keyLength = key.length();

	// vérifier que le message n'est pas vide
	if (origine.length() == 0) {
		cout << "Le message d'origine est vide !" << endl;
		return;
	}

	for (int i = 0; i < origine.length(); i++) {
		if (isalpha(origine[i])) {
			char c = (origine[i]);

			// calculer le décalage correspondant pour chaque lettre de la clé
			int shift;
			if (isupper(c)) {
				shift = key[keyIndex] - 'A'; // majuscules
			}
			else {
				shift = key[keyIndex] - 'a'; // minuscules
			}

			// même chose que le chiffrement de Cesar
			c = ((c - 'a') + shift) % 26 + 'a';
			// on remet les majuscules
			if (isupper(origine[i])) {
				c = toupper(c);
			}

			output += c;

			keyIndex = (keyIndex + 1) % keyLength;
		}
		// ...sinon ajouter le caractère tel quel au message chiffré
		else {
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
			// succès
			cout << "Le message a été chiffré avec succès." << endl;
			cout << "Vous trouverez le message dans le fichier 'message.txt'." << endl;
		}
		fichier_out.close();
	}
}


void Crypto::DechiffrerVigenere(string key) {
	string message = LireMessage(fileName);
	string decodedMsg = "";
	int keyIndex = 0;
	int keyLength = key.length();

	if (message.length() == 0) {
		cout << "Le message à déchiffrer est vide !" << endl;
		return;
	}
	else {
		for (int i = 0; i < message.length(); i++) {
			if (isalpha(message[i])) {
				char c = (message[i]);

				// calculer le décalage correspondant pour chaque lettre de la clé
				int shift;
				if (isupper(c)) {
					shift = toupper(key[keyIndex]) - 'A'; // majuscules
					// même chose que le chiffrement de Cesar
					int index = ((c - 'A') - shift) % 26;
					if (index < 0) index += 26;
					c = index + 'A';
				}
				else {
					shift = tolower(key[keyIndex]) - 'a'; // minuscules
					int index = ((c - 'a') - shift) % 26;
					if (index < 0) index += 26;
					c = index + 'a';
				}


				// on remet les majuscules
				if (isupper(message[i])) {
					c = toupper(c);
				}

				decodedMsg += c;

				keyIndex = (keyIndex + 1) % keyLength;
			}
			// ...sinon ajouter le caractère tel quel au message chiffré
			else {
				decodedMsg += message[i];
			}
		}

		cout << "Le message a été déchiffré avec succès." << endl;
		cout << "Voici le message déchiffré :\n" << endl;
		// imprimer le message décodé
		cout << decodedMsg << endl;
	}
}


void Crypto::AnalyserFrequence() {
	string message = LireMessage(fileName);

	// définition d'un tableau de comptage de fréquence pour chaque lettre
	int frequence[26] = { 0 }; // initialisation à 0

	// parcours de chaque caractère du message
	for (char c : message) {
		// si le caractère est une lettre minuscule anglaise (code ascii)
		if (c >= 'a' && c <= 'z') {
			// incrémenter le compteur de fréquence correspondant
			// on convertit la lettre c en un indice dans le tableau frequence en soustrayant l'entier 
			// représentant la lettre 'a' (97) à l'entier représentant la lettre c. 
			// par exemple, si c est la lettre 'd', alors c - 'a' donne 3, qui est l'indice de la lettre 'd' dans le tableau frequence.
			frequence[c - 'a']++;
		}
	}

	// recherche de l'indice du compteur de fréquence le plus élevé
	int indiceMax = 0;
	// on boucle sur le tableau de fréquences
	// sizeof(frequence) / sizeof(int) permet de calculer la longueur du tableau en divisant 
	// la taille totale du tableau par la taille d'un élément du tableau
	for (int i = 0; i < sizeof(frequence) / sizeof(int); i++) {
		if (frequence[i] > frequence[indiceMax]) {
			indiceMax = i;
		}
	}

	// trouver la lettre correspondante à l'indice_max et calculer le décalage par rapport 
	// à la lettre 'e', lettre ayant le plus d'occurrences en anglais 
	int decalage = (('a' + indiceMax) - 'e') % 26;

	system("cls");
	cout << "Il semblerait que le décalage soit de " << decalage << "." << endl;
}

