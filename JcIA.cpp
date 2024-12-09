#pragma once
#include <iostream>
#include "JcIA.hpp"

using namespace std;

JcIA::JcIA(){
    Tablero tablero;
    int cordx;
    int cordy;
    bool player = true;
}
void mostrarTablero(Tablero tablero){
    tablero.gatoGame();

}
bool JcIA::isSafe(int x,int y,Tablero tablero){
    char contenido = tablero.mostrarCoord(x,y);

    if(contenido != 'X' && contenido != 'O') return true;

    return false;
}
bool JcIA::is_number(string& s){
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
void JcIA::movimiento(Tablero tablero) {

    string input = "";
    int position;
    bool positionValid = true;
    bool safe;
    do {
        positionValid = true;
        cout<< "Ingresa una Coordenada (1-9)" << endl;
        cin>>input;
    
    position = (is_number(input) ? stoi(input) : -1);

    switch (position)
    {
        case 1:
            cordx = 0;
            cordy = 0;
            break;
        case 2:
            cordx = 0;
            cordy = 1;
            break;
        case 3:
            cordx = 0;
            cordy = 2;
            break;
        case 4:
            cordx = 1;
            cordy = 0;
            break;
        case 5:
            cordx = 1;
            cordy = 1;
            break;
        case 6:
            cordx = 1;
            cordy = 2;
            break;
        case 7:
            cordx = 2;
            cordy = 0;
            break;
        case 8:
            cordx = 2;
            cordy = 1;
            break;
        case 9:
            cordx = 2;
            cordy = 2;
            break;
        default:
            cout<< "Ingresa una Coordenada correcta (1-9)" << endl;
            positionValid = false;
            break;
    }
    
    if (positionValid) {
        safe = isSafe(cordx, cordy,tablero);
        cout << (!safe ? " Coordenada ya ocupada " : "") << endl;
        positionValid = safe;
    }  

    }while (!positionValid);

    if(player == true) {
        tablero.cambiarCoord(cordx,cordy,'X');
        player = false;
        mostrarTablero(tablero);
    }

    else {
        tablero.cambiarCoord(cordx,cordy,'O');
        player = true;
        mostrarTablero(tablero);
    }
}
int minimax(Tablero tablero, bool isPlayer){

    int score = winCheck(tablero,isPlayer);

    if(score == 10) return score;

    if(score == -10) return score;

    if(moveCheck(tablero)==false) return 0;

    if(isPlayer){
        int puntajeMax = -1000;
        for(int i = 0;i<3;i++){
            for(int j = 0;j<3;j++){
                puntajeMax = max(puntajeMax,minimax(tablero,!isPlayer));
            }
        }
        return puntajeMax;
    }
    else {
        int puntajeMin = 1000;

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                puntajeMin = min(puntajeMin,minimax(tablero,!isPlayer));
            }
        }
        return puntajeMin;
    }

}
bool moveCheck(Tablero tablero) {
    char coord;
    for(int i=0;i<3;i++){
         for(int j=0;j<3;j++){
            coord = tablero.mostrarCoord(i,j);
            if(coord != 'X' && coord != 'O'){
                return false;
            }
        }
    }
    return true;
}
int winCheck(Tablero tablero,bool player) {
 
    if(player == true){
        for(int a=0;a<3;a++) {
            
        if(tablero.mostrarCoord(a,0)==tablero.mostrarCoord(a,1) && tablero.mostrarCoord(a,0)==tablero.mostrarCoord(a,2) || tablero.mostrarCoord(0,a)==tablero.mostrarCoord(1,a) && tablero.mostrarCoord(0,a)==tablero.mostrarCoord(2,a)){
            return -10;
        }
        }
        if(tablero.mostrarCoord(0,0)==tablero.mostrarCoord(1,1) && tablero.mostrarCoord(1,1)==tablero.mostrarCoord(2,2) || tablero.mostrarCoord(0,2)==tablero.mostrarCoord(1,1) && tablero.mostrarCoord(1,1)==tablero.mostrarCoord(2,0)){
           return -10;
        }
    }
    else {
        for(int a=0;a<3;a++) {
        if(tablero.mostrarCoord(a,0)==tablero.mostrarCoord(a,1) && tablero.mostrarCoord(a,0)==tablero.mostrarCoord(a,2) || tablero.mostrarCoord(0,a)==tablero.mostrarCoord(1,a) && tablero.mostrarCoord(0,a)==tablero.mostrarCoord(2,a)){
            return 10;
        }
        }
        if(tablero.mostrarCoord(0,0)==tablero.mostrarCoord(1,1) && tablero.mostrarCoord(1,1)==tablero.mostrarCoord(2,2) || tablero.mostrarCoord(0,2)==tablero.mostrarCoord(1,1) && tablero.mostrarCoord(1,1)==tablero.mostrarCoord(2,0)){
           return 10;
        }
    }

    if(moveCheck(tablero) == true){
        cout<< "No hay más movimientos, EMPATE" <<endl;  
        return 0;
    }
    
    return 1;
}