
#include <iostream>
#include <windows.h>
#include "Crypto.h"

using namespace std;

bool containsOnlyLetters(string str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == string::npos;
}

bool isValidKey(int key) {
	return !isalpha(key) && key >= 1 && key <= 25;
}

int main()
{
	// modifier la locale pour pouvoir afficher les caractères spéciaux (caractères français)
	SetConsoleOutputCP(CP_UTF8);
	locale::global(locale("fr-FR.UTF-8"));
	Crypto crypto;

	char action;
	char method;
	int key = 0;
	string vigKey = "";
	int essais = 0; // initialisation à 0 des essais effectués
	int essaisMax = 1; // nombre d'essais maximum pour déchiffrer 

	bool isRunning = true;

	do {
		system("cls");
		cout << "Que voulez vous faire ?" << endl;
		cout << "Pour chiffrer un message : tapez (c) " << endl;
		cout << "Pour déchiffrer un message : tapez (d) " << endl;
		cout << "Pour faire une analyse fréquentielle : tapez (a) " << endl;
		cout << "Pour quitter le programme : tapez (q ou Q) " << endl;
		cout << "Saisissez votre choix : ";

		cin >> action;
		cin.clear();

		switch (action)
		{
		case 'c': // Chiffrement

			system("cls");
			cout << "Choisissez une méthode de chiffrement." << endl;
			cout << "Pour César : tapez (c) " << endl;
			cout << "Pour Vigenère : tapez (v) " << endl;
			cout << "Saisissez votre choix : ";

			cin >> method;
			cin.clear();

			switch (method)
			{
			case 'c': // César
				system("cls");
				cout << "Choisissez une clé entre 1 et 25 qui permettra de chiffrer le message." << endl;
				do {
					cout << "Saisissez la clé : ";
					cin >> key;

					// vérifier que la clé est un chiffre entre 1 et 25
					if (isValidKey(key)) {
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

				cout << "Veuillez entrer le nom du fichier à chiffrer : ";
				cin >> crypto.fileName;


				crypto.ChiffrerCesar(key);
				system("pause"); // attendre que l'utilisateur apppuie sur une touche pour passer à la suite
				break;

			case 'v': // Vigenère
				system("cls");
				cout << "Entrez une chaîne de caractère qui permettra de chiffrer le message." << endl;
				do {
					cout << "Saisissez la clé : ";
					cin >> vigKey;
					//tolower(key); // 

					// vérifier que la clé est une chaîne de caractère valide de a à z
					if (containsOnlyLetters(vigKey)) {
						cin.clear();
						system("cls");
						cout << "Clé saisie avec succès. Ne l'oubliez pas." << endl;
					}
					else {
						cin.clear();
						system("cls");
						cout << "La clé saisie n'est pas une chaîne de caractère valide." << endl;
						cout << "Veuillez entrer uniquement des lettres de l'alphabet en minuscules." << endl;
						vigKey = "";
						cin.ignore();
					}
				} while (vigKey == "");

				cout << "Veuillez entrer le nom du fichier à chiffrer : ";
				cin >> crypto.fileName;

				crypto.ChiffrerVigenere(vigKey);
				system("pause"); // attendre que l'utilisateur apppuie sur une touche pour passer à la suite
				break;

			default:
				cout << "Erreur de saisie. Veuillez recommencer. \n" << endl;
				cin.ignore();
			}

		case 'd': // Déchiffrement

			system("cls");
			cout << "Choisissez une méthode de déchiffrement." << endl;
			cout << "Pour César : tapez (c) " << endl;
			cout << "Pour Vigenère : tapez (v) " << endl;
			cout << "Saisissez votre choix : ";

			cin >> method;
			cin.clear();

			switch (method)
			{
			case 'c': // César
				system("cls");
				do {
					cout << "Veuillez saisir la clé secrète :" << endl;
					cin >> key;

					if (isValidKey(key)) {
						cin.clear();
						system("cls");
						cout << "Clé saisie avec succès." << endl;
						cout << "Veuillez entrer le nom du fichier à déchiffrer : ";
						cin >> crypto.fileName;

						crypto.DechiffrerCesar(key);
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
				crypto.EffacerMessage(crypto.fileName); // effacer le message pour ajouter une sécurité
				break;


			case 'v': // Vigenère
				system("cls");
				do {
					cout << "Veuillez saisir la clé secrète :" << endl;
					cin >> vigKey;

					if (containsOnlyLetters(vigKey)) {
						cin.clear();
						system("cls");
						cout << "Clé saisie avec succès." << endl;

						cout << "Veuillez entrer le nom du fichier à déchiffrer : ";
						cin >> crypto.fileName;

						crypto.DechiffrerVigenere(vigKey);
						essais++;
					}
					else {
						cin.clear();
						system("cls");
						cout << "La clé saisie n'est pas un chiffre entre 1 et 25." << endl;
						cout << "Veuillez recommencer." << endl;
						vigKey = "";
						cin.ignore();
					}

				} while (essais < essaisMax || vigKey == "");

				cout << "Nombre d'essais max atteint. Le message va être détruit." << endl;
				crypto.EffacerMessage(crypto.fileName);
				break;



			default:
				cout << "Erreur de saisie. Veuillez recommencer. \n" << endl;
				cin.ignore();
			}

		case 'a': // Analyse fréquentielle
			system("cls");
			cout << "Veuillez entrer le nom du fichier à déchiffrer : ";
			cin >> crypto.fileName;

			crypto.AnalyserFrequence();


		case 'Q':
		case 'q': // Quitter le programme
			cout << "Fermeture du programme.\n" << endl;
			isRunning = false;
			break;

		default: // si l'utilisateur se trompe dans la saisie
			cout << "Erreur de saisie. Veuillez recommencer. \n" << endl;
			cin.ignore();
		}

	} while (isRunning);

	return 1;
}
