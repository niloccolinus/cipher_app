
#include <iostream>
#include "Crypto.h"
#include <windows.h>

using namespace std;


int main()
{
    // modifier la locale pour pouvoir afficher les caractères spéciaux (caractères français)
    SetConsoleOutputCP(CP_UTF8);
    locale::global(locale("fr_FR.UTF-8"));;
    Crypto crypto;

    /* Permet de rester dans le programme jusqu'à ce que l'on décide de le quitter */
    bool isRunning;

    do
    {
        isRunning = crypto.Init(); // lancement du programme qui renverra 'vrai' une fois terminé
    } while (!isRunning); // Tant que isRunning n'est pas 'vrai', on reste dans le programme


}
