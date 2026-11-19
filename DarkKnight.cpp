#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <cctype>

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
int jugadorX = 1;
int jugadorY = 1;

bool esPared(char c) {
    return c == '|' || c == '=';
}
//para la funcion dibujar mapa requeri ayuda de IA
void dibujarMapa() {
    cout << "\033[H";   // vuelve arriba sin parpadear
    for (int y = 0; y < FILAS; y++) {
        for (int x = 0; x < COLS - 1; x++) {   // COLS-1 para no imprimir el '\0'
            char c = mapa[y][x];
            if (x == jugadorX && y == jugadorY) cout << "\033[96m@\033[0m";
            else if (esPared(c)) cout << "\033[90m" << c << "\033[0m";
            else if (c == 'K')   cout << "\033[93mK\033[0m";
            else if (c == 'C')   cout << "\033[96mC\033[0m";
            else if (c == 'J')   cout << "\033[91mJ\033[0m";
            else                 cout << c;
        }
        cout << endl;
    }
    cout << "Mover: W A S D | Salir: Q" << endl;
}

char moverpersonaje(char tecla, int &x, int &y) {
    int nx = x, ny = y;

    switch (tecla) {
        case 'W': ny--; break;
        case 'S': ny++; break;
        case 'A': nx--; break;
        case 'D': nx++; break;
        default: return 'X';
    }

    if (nx < 0 || nx >= COLS - 1 || ny < 0 || ny >= FILAS) return '|';
    if (esPared(mapa[ny][nx])) return '|';

    x = nx;
    y = ny;
    return mapa[y][x];
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
char leerTecla()
 { return toupper(_getch());}

void explorar() {
    limpiar();
    while (true) {
        dibujarMapa();
        char tecla = leerTecla();
        if (tecla == 'Q') break;
        moverpersonaje(tecla, jugadorX, jugadorY);
    }
}