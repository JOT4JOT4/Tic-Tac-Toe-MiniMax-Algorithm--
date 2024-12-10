#pragma once
#include <iostream>
#include <string>

using namespace std;

class Tablero
{
    private:
        char tablero[3][3];

    public:
        Tablero();
        void gatoGame();
        char mostrarCoord(int x,int y);
        void cambiarCoord(int x,int y,char signo);
        void movimiento(bool player);
        int winCheck();
        bool isSafe(int x ,int y);
        bool is_number(string &s);
        bool moveCheck();
        int minimax(bool isPlayer, int alpha, int beta);
        void whosWin(int score);
        void bestMove();
        void singlePlayer();
        void multiplayer();
        
};