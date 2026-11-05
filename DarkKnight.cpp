#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void menuPrincipal(){
    string nombres[] = {"Nueva Partida","Cargar partida","Opciones","Salir"};
    cout<<"=========DARK KNIGHT==========."<<endl<<endl;
    for( int i=0; i<4;i++){
        cout<<"-------"<<i+1<<"."<<nombres[i]<<"-------"<<endl;
    }
    cout<<"==============================="<<endl<<endl;
}