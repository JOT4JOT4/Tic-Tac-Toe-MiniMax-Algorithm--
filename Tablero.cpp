#include <iostream>
#include <string>
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
/*
*@def: Muestra el tablero
*@param:
*@return:
*/
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
/*Funcion no usada
*@def: Muestra las cordenadas especificadas
*@param: int x,int y
*@return: retorna el char del tablero[x][y]
*/
char Tablero::mostrarCoord(int x,int y){
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        throw std::out_of_range("Coordenadas fuera de rango");
    }
    return tablero[x][y];
}
/*Funcion no usada
*@def: cambia el char de las cordenadas especificadas
*@param: int x,int y,char signo
*@return:
*/
void Tablero::cambiarCoord(int x,int y,char signo){
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        throw std::out_of_range("Coordenadas fuera de rango");
    }
    tablero[x][y]=signo;
}
/*
*@def: comprueba si el valor ingresado por pantalla es un valor valido
*@param: string s
*@return: retorna bool false si no lo es y true en caso de que si
*/
bool Tablero::is_number(string &s) {
    for (char c : s) {
        if (!isdigit((unsigned char)c)) return false;
    }
    return !s.empty();
}
/*
*@def: comprueba si el movimiento en el tablero es valido, si es que se puede colocar una ficha en el lugar
*@param: int x, int y (coordenadas).
*@return: retorna bool false si es que ya está ocupado con una ficha, y true en caso contrario.
*/
bool Tablero::isSafe(int x, int y) {
    if (tablero[x][y] != 'X' && tablero[x][y] != 'O') return true;
    return false;
}
/*
*@def: comprueba si es que aún existe espacio en el tablero para colocar una ficha
*@param:
*@return: retorna bool false si es que aún existe espacio y bool true si es que no encuentra ninguno
*/
bool Tablero::moveCheck() {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}
/*
*@def: función que pregunta y realiza los movimientos en el tablero, funciona en ambos casos (multiplayer y simgleplayer)
*@param:bool player
*@return: no retorna
*/
void Tablero::movimiento(bool player) {
    string input = "";
    int position;
    bool positionValid = true;
    bool safe;
    int cordx;
    int cordy;

    do {
        positionValid = true;
        cout << "Jugador X, ingresa un numero (1-9): ";
        cin >> input;

        position = (is_number(input) ? stoi(input) : -1);

        switch (position) {
            case 1: cordx = 0; cordy = 0; 
            break;
            case 2: cordx = 0; cordy = 1; break;
            case 3: cordx = 0; cordy = 2; break;
            case 4: cordx = 1; cordy = 0; break;
            case 5: cordx = 1; cordy = 1; break;
            case 6: cordx = 1; cordy = 2; break;
            case 7: cordx = 2; cordy = 0; break;
            case 8: cordx = 2; cordy = 1; break;
            case 9: cordx = 2; cordy = 2; break;
            default:
                cout << "Ingrese un numero valido (1-9)." << endl;
                positionValid = false;
                break;
        }

        if (positionValid) {
            safe = isSafe(cordx, cordy);
            if (!safe) {
                cout << "La posicion ya esta ocupada. Intenta de nuevo.\n";
                positionValid = false;
            }
        }

    } while (!positionValid);

    
    if (player == true) {
        tablero[cordx][cordy]='X';
    } else {
        tablero[cordx][cordy]='O';
    }
    gatoGame();
}
/*
*@def: comprueba si es que existen 3 token en fila, para comprobar que ya se ha ganado el juego
*@param:
*@return: retorna puntaje int, 10 en caso de ganar el jugador X, -10 en caso de ganar el jugador O,
    0 en caso de que todavía no exista ganador o empate.
*/
int Tablero::winCheck() {
    
    for (int fila = 0; fila < 3; fila++) {
        if (tablero[fila][0] == tablero[fila][1] && tablero[fila][1]== tablero[fila][2]) {
            if (tablero[fila][0] == 'X')
                return +10;
            else if (tablero[fila][0] == 'O')
                return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (tablero[0][col]== tablero[1][col]&& tablero[1][col] == tablero[2][col]) {
            if (tablero[0][col]== 'X')
                return +10;
            else if (tablero[0][col]== 'O')
                return -10;
        }
    }

    if (tablero[0][0]== tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        if (tablero[0][0]== 'X')
            return +10;
        else if (tablero[0][0] == 'O')
            return -10;
    }

    if (tablero[0][2] == tablero[1][1] && tablero[1][1]== tablero[2][0]) {
        if (tablero[0][2]== 'X')
            return +10;
        else if (tablero[0][2]== 'O')
            return -10;
    }

    return 0;
}
/*
*@def: función minimax poda Alpha Beta
*@param:bool player, int alpha, int beta (en este caso no es necesario un depth)
*@return: retorna el valor int de el estado del arbol actual (10,-10-0)
*/
int Tablero::minimax(bool isPlayer, int alpha, int beta) {


    int score = winCheck();


    if (score == 10) return score;    
    if (score == -10) return score;   

    if (moveCheck() == true) return 0;

    if (isPlayer) {
        int puntajeMax = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isSafe(i, j)) {
                    char aux = tablero[i][j];
                    tablero[i][j]='X';;

                    int valor = minimax(!isPlayer, alpha, beta);

                    tablero[i][j]=aux;

                    if (valor > puntajeMax) puntajeMax = valor;
                    if (valor > alpha) alpha = valor;
                    if (beta <= alpha) break;
                }
            }
        }
        return puntajeMax;
    } else {
        int puntajeMin = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isSafe(i, j)) {
                    char aux = tablero[i][j];
                    tablero[i][j] ='O';

                    int valor = minimax(!isPlayer, alpha, beta);

                    tablero[i][j] = aux;

                    if (valor < puntajeMin) puntajeMin = valor;
                    if (valor < beta) beta = valor;
                    if (beta <= alpha) break;
                }
            }
        }
        return puntajeMin;
    }
}
/*
*@def: función que imprime por pantalla el ganador de la ronda, si es X, Y o Empate
*@param: int Score (puntaje de el estado actual del tablero)
*@return: no retorna
*/
void Tablero::whosWin(int score) {
    if (score == 10) {
        cout << "¡Gana el jugador X!" << endl;
    } else if (score == -10) {
        cout << "¡Gana el jugador O (IA)!" << endl;
    } else {
        cout << "¡Empate!" << endl;
    }
}
/*
*@def: función que usa minmax para determinar el mejor movimiento posible para la IA
*@param:
*@return: no retorna
*/
void Tablero::bestMove() {
    int best = 1000; 
    int x = -1, y = -1;



    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (isSafe(i, j)) {
                char aux = tablero[i][j];
                tablero[i][j]='O';

                int move = minimax(true, -9999, 9999);

                tablero[i][j]=aux;

                if (move < best) {
                    best = move;
                    x = i;
                    y = j;
                }
            }
        }
    }

    if (x != -1 && y != -1) {
        tablero[x][y]='O';
        cout << "La IA (O) realiza su movimiento:\n";
        gatoGame();
    }
}
/*
*@def: función que inicializa el juego contra la IA
*@param:
*@return: no retorna
*/
void Tablero::singlePlayer() {

    while (true) {
        int w = winCheck();
        if (w == 10 || w == -10 || moveCheck()) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        movimiento(true);
        w = winCheck();
        if (w == 10 || w == -10 || moveCheck()) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        bestMove();
        w = winCheck();
        if (w == 10 || w == -10 || moveCheck()) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }
    }
}
/*
*@def: función que inicializa el juego de jugador contra jugador
*@param:
*@return: no retorna
*/
void Tablero::multiplayer() {
    bool player = true; 
    int w = 0; 

    gatoGame();

    while (true) {
        w = winCheck();
        if (w == 10 || w == -10 || moveCheck()) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        if (player) {
            cout << "Turno de Jugador X\n";
        } else {
            cout << "Turno de Jugador O\n";
        }
        movimiento(player);

        player = !player;
    }
}