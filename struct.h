#ifndef STRUCT_H
#define STRUCT_H

#include <string>
using namespace std;

const int FILAS = 15;
const int COLS = 60;
const int MAX_ENEMIGOS = 8;
const int MAX_ITEMS = 2;

struct personaje {
    string nombre;      
    int vida;
    int vidamax;
    int ataque;
    int defensa;
    int nivel;
    int experiencia;
    int chakra;         
    int pociones;       // nuevo
};

struct enemigo {
    string nombre;      
    int vida;
    int vidamax;
    int ataque;
    int defensa;
    int xp;
};     
    
        
extern char mapa[FILAS][COLS];

#endif
