#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "DarkKnight.h"
using namespace std;

int main(){
    int opcion;

    mostrarMural();
    mostrarHistoria();


    menuPrincipal();
    cin>>opcion;

    switch(opcion){
        case 1:

        break;
        case 2:
            
        break;
        case 3:
            subMenu2();
            cin>>opcion;
            do{
                cout<<"==============INTEGRANTES=============="<<endl<<endl;
                cout<<"Alisson Melissa Ramirez Campos 00058026"<<endl;
                cout<<"    Jose Enrique Valladares 00078226   "<<endl;
            }while (opcion !=2);
        break;
        case 4:
            subMenu1();
            cin>>opcion;
        break;
        case 5:

        break;
        default:

        break;
    }
}