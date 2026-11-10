#include <iostream>
using namespace std;
void moverpersonaje(char tecla,int &x,int &y){ //mover personaje por mapa
    switch(tecla){
    case 'W': y--; break; 
    case 'S': y++; break;  
    case 'A': x--;break;
    case 'D': x++;break;
   default:
   cout<<"tecla invalida usa A,W,S,D "<<endl;
   break;
}
}