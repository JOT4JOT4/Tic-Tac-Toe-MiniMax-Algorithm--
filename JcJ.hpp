#pragma once
#include <iostream>
#include "Tablero.hpp"
#include <string>

using namespace std;

class JcJ
{
   private:
        Tablero tablero;
        int cordx;
        int cordy;
        bool player;
    public:
        JcJ();
        void mostrarTablero(Tablero tablero);
        bool isSafe(int x,int y,Tablero tablero);
        bool is_number(string& s);
        void movimiento(Tablero tablero);
        bool movecheck(Tablero tablero);
        int wincheck(char cord);
};