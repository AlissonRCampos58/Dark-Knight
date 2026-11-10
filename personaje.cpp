#include <iostream>
#include <string>
using namespace std;

//Estructura del personaje
struct personaje{
    string Crow;
    int vida;
    int vidamax;
    int ataque;
    int defensa;
    int nivel;
    int experiencia;
};
int main(){
    personaje jugador;
    jugador.Crow= "Crow";
    jugador.vida=50;
    jugador.vidamax=50;
    jugador.ataque=10;
    jugador.defensa=5;
    jugador.nivel=1;
    jugador.experiencia=0;
    cout<<"Crow:"<<jugador.Crow<<endl;
    

    return 0;
}