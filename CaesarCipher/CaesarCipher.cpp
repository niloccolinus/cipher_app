
#include <iostream>
#include "Crypto.h"
#include <windows.h>

using namespace std;


int main()
{
    // modifier la locale pour pouvoir afficher les caractères spéciaux (caractères français)
    SetConsoleOutputCP(CP_UTF8);
    locale::global(locale("fr-FR.UTF-8"));
    Crypto crypto;

    //bool isRunning;

    //do
    //{
    //    isRunning = crypto.Init(); 
    //} while (!isRunning); // tant que isRunning n'est pas 'vrai', on reste dans le programme

    //crypto.key = crypto.AnalyserFrequence("message-intercepte.txt");

    crypto.ChiffrerVigenere("pouet");
    crypto.DechiffrerVigenere("pouet");
}
