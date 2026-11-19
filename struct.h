#ifndef STRUCT_H
#define STRUCT_H

#include <string>
using namespace std;

const int FILAS = 15;
const int COLS = 60;
const int MAX_ENEMIGOS = 8;
const int MAX_ITEMS = 2;

struct personaje{
    string Crow;
    int vida;
    int vidamax;
    int ataque;
    int defensa;
    int nivel;
    int experiencia;
};
struct enemigo {
    string goblin;
    int vida;
    int vidamax;
    int ataque;
    int defensa;
    int xp;
}
    //arreglo con enemigos
        enemigo []={"goblin",20,10,8,2};
    




        
extern char mapa[FILAS][COLS];

#endif
