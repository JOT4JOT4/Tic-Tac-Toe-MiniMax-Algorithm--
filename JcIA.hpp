#pragma once
#include <iostream>
#include "Tablero.hpp"
#include <string>

using namespace std;

class JcIA
{
   private:
        Tablero tablero;
        int cordx;
        int cordy;
        bool player;
    public:
        JcIA();
        void mostrarTablero(Tablero tablero);
        bool isSafe(int x,int y,Tablero tablero);
        bool is_number(string& s);
        void movimiento(Tablero tablero);
        int minimax(char chara,bool isPlayer);
};