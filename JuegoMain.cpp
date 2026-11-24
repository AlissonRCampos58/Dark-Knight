#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DarkKnight.h"

using namespace std;

int main() {
    srand(time(0));

    Usuario usuarios[MAX_USUARIOS];
    int nUsuarios;
    cargarUsuarios(usuarios, nUsuarios);

    int sesion = iniciarSesion(usuarios, nUsuarios);
    if (sesion == -1) {
        limpiar();
        cout << "Demasiados intentos. La oscuridad te deja fuera..."<<endl;
        return 1;
    }

    Partida p;
    cargarPartida(p);

    menuPrincipal(p, usuarios, nUsuarios, sesion);

    return 0;
}
