#pragma once
#include <iostream>

class Tablero
{
    private:
        char tablero[3][3];

    public:
        Tablero();
        void gatoGame();
        char mostrarCoord(int x,int y);
        void cambiarCoord(int x,int y,char signo);
        void cambiarCoord(int x,int y);
};