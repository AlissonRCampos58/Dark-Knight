#ifndef JUEGO_H
#define JUEGO_H

#include "struct.h"

void limpiar();
void pausa();

void cargarUsuarios(Usuario u[], int &n);
void registrarUsuario(Usuario u[], int &n);
int iniciarSesion(Usuario u[], int &n);
void menuAdmin(Partida &p, Usuario u[], int n);
void listarUsuarios(Usuario u[], int n);
void reporteResultados(Usuario u[], int n, Partida p);
void mostrarAyuda();
void mostrarIntegrantes();



void mostrarHistoria();
void mostrarcrow();
void mostrarMural();

void menuPrincipal(Partida &p, Usuario u[], int n, int sesion);

void cargarPartida(Partida &p);
void guardarPartida(Partida p);

void subMenu1();
void subMenu2();

bool esPared(char c);

char leerTecla();

void cargarEnemigos();
int enemigoEn(int x, int y);
int enemigosVivos();
void atacar(personaje &p, int dx, int dy);
void moverEnemigos(personaje &p, int tick);

void dibujarMapa(personaje &p);
void explorar();

char moverpersonaje(char tecla, int &x, int &y);

void jugar(Partida &p);
void nuevoJuego(Partida &p);
    
#endif