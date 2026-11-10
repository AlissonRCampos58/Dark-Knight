#ifndef STRUCT_H
#define STRUCT_H

#include <string>
using namespace std;

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
    





#endif
