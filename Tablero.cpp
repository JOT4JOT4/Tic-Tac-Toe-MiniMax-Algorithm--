#include <iostream>
#include "Tablero.hpp"

using namespace std;

Tablero::Tablero(){
    char valor = '1';
    for(int i =0;i<3;i++){
        for(int j=0;j < 3;j++){
            tablero[i][j] =valor++;
        }
    }
    int cordx;
    int cordy;
    bool player = true;
}
void Tablero::gatoGame(){

    cout<< "    |    |    \n";
    cout<< " "<<tablero[0][0]<<"  | " <<tablero[0][1]<<"  | "<<tablero[0][2]<<"  \n";
    cout<< "____|____|____\n";
    cout<< "    |    |    \n";
    cout<< " "<<tablero[1][0]<<"  | " <<tablero[1][1]<<"  | "<<tablero[1][2]<<"  \n";
    cout<< "____|____|____\n";
    cout<< "    |    |    \n";
    cout<< " "<<tablero[2][0]<<"  | " <<tablero[2][1]<<"  | "<<tablero[2][2]<<"  \n";
    cout<< "    |    |    \n";
}

char Tablero::mostrarCoord(int x,int y){

    return tablero[x][y];
}
void Tablero::cambiarCoord(int x,int y,char signo){

    tablero[x][y]=signo;
}