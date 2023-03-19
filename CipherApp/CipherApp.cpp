
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
	// modifier la locale pour pouvoir afficher les caract�res sp�ciaux (caract�res fran�ais)
	SetConsoleOutputCP(CP_UTF8);
	locale::global(locale(""));
	Crypto crypto;

	char action;
	char method;
	int key = 0;
	string vigKey = "";
	int essais = 0; // initialisation � 0 des essais effectu�s
	int essaisMax = 1; // nombre d'essais maximum pour d�chiffrer 

	bool isRunning = true;

	do {
		system("cls");
		cout << "Que voulez vous faire ?" << endl;
		cout << "Pour chiffrer un message : tapez (c) " << endl;
		cout << "Pour d�chiffrer un message : tapez (d) " << endl;
		cout << "Pour faire une analyse fr�quentielle : tapez (a) " << endl;
		cout << "Pour quitter le programme : tapez (q ou Q) " << endl;
		cout << "Saisissez votre choix : ";

		cin >> action;
		cin.clear();

		switch (action)
		{
		case 'c': // Chiffrement

			system("cls");
			cout << "Choisissez une m�thode de chiffrement." << endl;
			cout << "Pour C�sar : tapez (c) " << endl;
			cout << "Pour Vigen�re : tapez (v) " << endl;
			cout << "Saisissez votre choix : ";

			cin >> method;
			cin.clear();

			if (action)
				switch (method)
				{
				case 'c': // C�sar
					system("cls");
					cout << "Choisissez une cl� entre 1 et 25 qui permettra de chiffrer le message." << endl;
					do {
						cout << "Saisissez la cl� : ";
						cin >> key;

						// v�rifier que la cl� est un chiffre entre 1 et 25
						if (isValidKey(key)) {
							cin.clear();
							system("cls");
							cout << "Cl� saisie avec succ�s. Ne l'oubliez pas." << endl;

						}
						else {
							cin.clear();
							system("cls");
							cout << "La cl� saisie n'est pas un chiffre entre 1 et 25." << endl;
							cout << "Veuillez recommencer." << endl;
							system("pause");
							cin.ignore();
							key = 0;
						}
					} while (key == 0);

					cout << "Veuillez entrer le nom du fichier � chiffrer (avec l'extension .txt) : ";
					cin >> crypto.fileInput;
					cout << "Veuillez donner un nom au fichier de sortie (avec l'extension .txt) : ";
					cin >> crypto.fileOutput;

					crypto.ChiffrerCesar(key);
					system("pause"); // attendre que l'utilisateur apppuie sur une touche pour passer � la suite
					break;

				case 'v': // Vigen�re
					system("cls");
					cout << "Entrez une cha�ne de caract�re qui permettra de chiffrer le message." << endl;
					do {
						cout << "Saisissez la cl� : ";
						cin >> vigKey;
						//tolower(key); // 

						// v�rifier que la cl� est une cha�ne de caract�re valide de a � z
						if (containsOnlyLetters(vigKey)) {
							cin.clear();
							system("cls");
							cout << "Cl� saisie avec succ�s. Ne l'oubliez pas." << endl;
						}
						else {
							cin.clear();
							system("cls");
							cout << "La cl� saisie n'est pas une cha�ne de caract�re valide." << endl;
							cout << "Veuillez entrer uniquement des lettres de l'alphabet en minuscules." << endl;
							system("pause");
							cin.ignore();
							vigKey = "";
						}
					} while (vigKey == "");

					cout << "Veuillez entrer le nom du fichier � chiffrer (avec l'extension .txt) : ";
					cin >> crypto.fileInput;
					cout << "Veuillez donner un nom au fichier de sortie (avec l'extension .txt) : ";
					cin >> crypto.fileOutput;

					crypto.ChiffrerVigenere(vigKey);
					system("pause"); // attendre que l'utilisateur apppuie sur une touche pour passer � la suite
					break;

				default:
					cout << "Erreur de saisie. Veuillez recommencer. \n" << endl;
					cin.ignore();
				}

		case 'd': // D�chiffrement

			system("cls");
			cout << "Choisissez une m�thode de d�chiffrement." << endl;
			cout << "Pour C�sar : tapez (c) " << endl;
			cout << "Pour Vigen�re : tapez (v) " << endl;
			cout << "Saisissez votre choix : ";

			cin >> method;
			cin.clear();

			switch (method)
			{
			case 'c': // C�sar
				system("cls");
				do {
					cout << "Veuillez saisir la cl� secr�te :" << endl;
					cin >> key;

					if (isValidKey(key)) {
						cin.clear();
						system("cls");
						cout << "Cl� saisie avec succ�s." << endl;
						cout << "Veuillez entrer le nom du fichier � d�chiffrer (avec l'extension .txt) : ";
						cin >> crypto.fileInput;
						cout << "Veuillez donner un nom au fichier de sortie (avec l'extension .txt) : ";
						cin >> crypto.fileOutput;

						crypto.DechiffrerCesar(key);
						essais++;
					}
					else {
						cin.clear();
						system("cls");
						cout << "La cl� saisie n'est pas un chiffre entre 1 et 25." << endl;
						cout << "Veuillez recommencer." << endl;
						system("pause");
						cin.ignore();
						key = 0;
					}

				} while (essais < essaisMax || key == 0);

				cout << "Nombre d'essais max atteint. Le message va �tre d�truit." << endl;
				crypto.EffacerMessage(crypto.fileInput); // effacer le message pour ajouter une s�curit�
				system("pause"); // attendre que l'utilisateur apppuie sur une touche pour passer � la suite
				break;


			case 'v': // Vigen�re
				system("cls");
				do {
					cout << "Veuillez saisir la cl� secr�te :" << endl;
					cin >> vigKey;

					if (containsOnlyLetters(vigKey)) {
						cin.clear();
						system("cls");
						cout << "Cl� saisie avec succ�s." << endl;

						cout << "Veuillez entrer le nom du fichier � d�chiffrer (avec l'extension .txt) : ";
						cin >> crypto.fileInput;
						cout << "Veuillez donner un nom au fichier de sortie (avec l'extension .txt) : ";
						cin >> crypto.fileOutput;

						crypto.DechiffrerVigenere(vigKey);
						essais++;
					}
					else {
						cin.clear();
						system("cls");
						cout << "La cl� saisie n'est pas un chiffre entre 1 et 25." << endl;
						cout << "Veuillez recommencer." << endl;
						system("pause");
						cin.ignore();
						vigKey = "";
					}

				} while (essais < essaisMax || vigKey == "");

				cout << "Nombre d'essais max atteint. Le message va �tre d�truit." << endl;
				crypto.EffacerMessage(crypto.fileInput);
				system("pause"); // attendre que l'utilisateur apppuie sur une touche pour passer � la suite
				break;

			case 'r': // retour en arri�re
				break;

			default:
				cout << "Erreur de saisie. Veuillez recommencer. \n" << endl;
				cin.ignore();
			}
			break;

		case 'a': // Analyse fr�quentielle
			system("cls");
			cout << "Veuillez entrer le nom du fichier � analyser : ";
			cin >> crypto.fileInput;

			crypto.AnalyserFrequence();
			break;

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
