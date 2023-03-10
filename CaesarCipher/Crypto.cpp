#include <iostream>
#include <string>
#include "Crypto.h"

// constructeur
Crypto::Crypto() {
	
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

void Crypto::Chiffrer(int key) {
	string origine = LireMessage("origine.txt");
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

void Crypto::Dechiffrer(int key) {
	string message = LireMessage("message.txt");
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

bool Crypto::Init() {
	Crypto crypto;

	char choix; // choix de l'utilisateur, soit chiffrer, soit déchiffrer, soit quitter
	int key = 0; // clé rentrée par l'utilisateur
	int essais = 0; // initialisation à 0 des essais effectués
	int essaisMax = 1; // nombre d'essais maximum pour déchiffrer 

	system("cls");
	cout << "Faites votre choix : " << endl;
	cout << "Pour chiffrer un message : tapez (c) " << endl;
	cout << "Pour déchiffrer un message : tapez (d) " << endl;
	cout << "Pour quitter le programme : tapez (q ou Q) " << endl;
	cout << "Saisissez votre choix : ";

	cin >> choix;
	cin.clear();


	switch (choix)
	{
	case 'c': // Chiffrement

		system("cls");
		cout << "Vous avez choisi de chiffrer un message." << endl;
		cout << "Choisissez une clé entre 1 et 25 qui permettra de chiffrer et déchiffrer le message." << endl;

		/* Début saisie clé */
		// L'utilisateur saisit la clé qui va permettre de chiffrer le message.

		do {
			cout << "Saisissez la clé :" << endl;
			cin >> key;

			// vérifier que la clé est un chiffre entre 1 et 25
			if (!isalpha(key) && key >= 1 && key <= 25) {
				cin.clear();
				system("cls");
				cout << "Clé saisie avec succès. Ne l'oubliez pas." << endl;

			}
			else {
				cin.clear();
				system("cls");
				cout << "La clé saisie n'est pas un chiffre entre 1 et 25." << endl;
				cout << "Veuillez recommencer." << endl;
				key = 0;
				cin.ignore();
			}
		} while (key == 0);

		/* Fin saisie clé */

		crypto.Chiffrer(key); // lance la fonction chiffrer
		system("pause"); // attendre que l'utilisateur apppuie sur une touche pour passer à la suite
		return false;
		break;

	case 'd': // Déchiffrement

		system("cls");
		cout << "Vous avez choisi de déchiffrer un message." << endl;

		/* Saisir clé */

		do {
			cout << "Veuillez saisir la clé secrète :" << endl;
			cin >> key;

			// vérifier que la clé est un chiffre entre 1 et 25
			if (!isalpha(key) && key >= 1 && key <= 25) {
				cin.clear();
				system("cls");
				cout << "Clé saisie avec succès." << endl;

				crypto.Dechiffrer(key); // lance la fonction dechiffrer
				essais++;
			}
			else {
				cin.clear();
				system("cls");
				cout << "La clé saisie n'est pas un chiffre entre 1 et 25." << endl;
				cout << "Veuillez recommencer." << endl;
				key = 0;
				cin.ignore();
			}

		} while (essais < essaisMax || key == 0);

		cout << "Nombre d'essais max atteint. Le message va être détruit." << endl;
		EffacerMessage("message.txt"); // effacer le message pour ajouter une sécurité
		break;

	case 'Q':
	case 'q': // Quitter le programme
		cout << "Fermeture du programme.\n" << endl;
		return true; // va stopper la boucle dans main()
		break;
	default: // si l'utilisateur se trompe dans la saisie
		cout << "Erreur de saisie. Veuillez recommencer. \n" << endl;
		cin.ignore();
		return false;
	}

	return true;

}
