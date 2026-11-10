#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
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
void mostrarHistoria() {
    cout<<"=== LA LEYENDA DEL CABALLERO OSCURO ==="<<endl;
    cout<<"Bajo el reino de Ceniza, el Santuario guarda a los que"<<endl;
    cout<<"juraron no volver a ver la luz. Tu eras uno de ellos."<<endl;
    cout<<"Esta noche el sello se rompio y solo queda un camino:"<<endl;
    cout<<"atravesar el corredor, recuperar la llave y escapar."<<endl;
    cout<<"Cada alma que absorba te acerca a la salida... o a la condena."<<endl<<endl;
    cout<<"Presiona Enter..."<<endl;
    cin.get();
}
void mostrarMural() {
    ifstream archivo("mural.txt");
    string linea;
    while (getline(archivo, linea)) {   // while + archivo
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
  
int main(){
     SetConsoleOutputCP(CP_UTF8);
    mostrarMural();
    return 0;
}
    
