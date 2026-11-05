#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void menuPrincipal(){
    string nombres[] = {"Nueva Partida","Cargar partida","Opciones","Ayuda","Salir"};
    cout<<"=========DARK KNIGHT==========="<<endl<<endl;
    for( int i=0; i<5;i++){
        cout<<"    "<<i+1<<"."<<nombres[i]<<"    "<<endl;
    }
    cout<<"==============================="<<endl<<endl;
}
void subMenu1(){
    string nombres[] = {"Como jugar?","Controles","Objetivo","Salir"};
    cout<<"============AYUDA=============="<<endl<<endl;
    for( int i=0; i<4;i++){
        cout<<"    "<<i+1<<"."<<nombres[i]<<"    "<<endl;
    }
    cout<<"==============================="<<endl<<endl;
}
void subMenu2(){
    string nombres[] = {"Dificultad de Juego","Integrantes","Salir"};
    cout<<"===========OPCIONES============"<<endl<<endl;
    for( int i=0; i<3;i++){
        cout<<"    "<<i+1<<"."<<nombres[i]<<"    "<<endl;
    }
    cout<<"==============================="<<endl<<endl;
}

