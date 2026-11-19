#ifndef JUEGO_H
#define JUEGO_H

#include "struct.h"

void limpiar();
void pausa();

void mostrarHistoria();
void mostrarcrow();
void mostrarMural();

void menuPrincipal();

void cargarPartida(Partida &p);
void guardarPartida(Partida p);

void subMenu1();
void subMenu2();

void inicializarEnemigos(enemigo e[], int &n);
void inicializarItems(Item it[], int &n);

bool esMuro(int f, int c);
int buscarEnemigo(enemigo e[], int n, int f, int c);

void dibujarMapa(personaje j, enemigo e[], int nE, Item it[], int nI);
void dibujarHUD(personaje j);

void combate(personaje &j, enemigo &e);

void moverpersonaje(char tecla,int &x,int &y);

void jugar(Partida &p);
void nuevoJuego(Partida &p);
    
#endif