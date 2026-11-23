#include <iostream>
#include <string>
#include <fstream>
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

void mostrarcrow(){
ifstream archivo("crow.txt");
string linea;
while(getline (archivo, linea)){
    cout<<linea<<endl;
}
archivo.close();
cout<<"presiona Enter para continuar..."<<endl;
cin.get();
}
int main() {
    personaje jugador;
    jugador.Crow= "Crow";
    jugador.vida=50;
    jugador.vidamax=50;
    jugador.ataque=10;
    jugador.defensa=5;
    jugador.nivel=1;
    jugador.experiencia=0;
    cout<<"Crow:"<<jugador.Crow<<endl;
    
    mostrarcrow();
    return 0;
}
