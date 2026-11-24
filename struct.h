#ifndef STRUCT_H
#define STRUCT_H

#include <string>
using namespace std;

const int FILAS = 15;
const int COLS = 60;
const int MAX_ENEMIGOS = 5;
const int MAX_ITEMS = 5;
const int MAX_USUARIOS = 10;

struct Usuario {
    string nombre;
    string clave;
    char rol;      //  de Admin y Jugadores
    bool activo;
};

struct personaje {
    string nombre;
    int fila, col;      
    int vida;
    int vidamax;
    int ataque;
    int defensa;
    int nivel;
    int experiencia; 
    int pociones;   
    int chakra;  // nuevo
};

struct enemigo {
    string nombre;
    int fila, col;     
    int vida;
    int vidamax;
    int ataque;
    int defensa;
    int xp;
    int x;
    int y;
    bool esJefe;
    int cooldown;
};     

struct Item {
    int fila, col;
    char tipo;// 'P' pocion
    bool activo;
};

struct Partida {
    int nivel;
    bool jefeMuerto;
    bool terminada;
};
        
extern char mapa[FILAS][COLS];

#endif
