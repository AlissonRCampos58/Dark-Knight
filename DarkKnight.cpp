#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>

#include "DarkKnight.h"

using namespace std;

char mapa[FILAS][COLS] = {
    "===========================================================",
    "|...................................|....|................|",
    "|........==..........==..............====.......==........|",
    "|.......|..|........|..|.......................|..|.......|",
    "|........==K.........==.C.......................==........|",
    "|.........................................................|",
    "|........==..........==.........................==........|",
    "|.......|..|........|..|.......................|..|.......|",
    "|........==..........==.........................==........|",
    "|.........................................................|",
    "|........==..........==.........................==........|",
    "|.......|..|........|..|.......................|..|.......|",
    "|........==....J.....==..............====.......==........|",
    "|...................................|....|................|",
    "==========================================================="
};

void limpiar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausa() {
    cout << "\nPresiona ENTER para continuar...";
    cin.get();
}

void mostrarMural() {
    ifstream archivo("mural.txt");
    string linea;
    while (getline(archivo, linea)) {   // while + archivo
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
void mostrarLogo() {
    ifstream archivo("Logo.txt");
    string linea;
    while (getline(archivo, linea)) {   // while + archivo
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
void mostrarCrow() {
    ifstream archivo("crow.txt");
    string linea;
    while (getline(archivo, linea)) {   // while + archivo
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}