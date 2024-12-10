#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Tablero.cpp"

using namespace std;

int score = 1;
int cordx;
int cordy;

bool is_number(string &s) {
    for (char c : s) {
        if (!isdigit((unsigned char)c)) return false;
    }
    return !s.empty();
}

bool isSafe(int x, int y, Tablero& tablero) {
    //tablero.gatoGame();
    if (tablero.mostrarCoord(x,y) != 'X' && tablero.mostrarCoord(x,y) != 'O') return true;
    return false;
}

bool moveCheck(Tablero& tablero) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero.mostrarCoord(i,j) != 'X' && tablero.mostrarCoord(i,j) != 'O') {
                return false;
            }
        }
    }
    return true;
}

int winCheck(Tablero& tablero) {
    
    for (int fila = 0; fila < 3; fila++) {
        if (tablero.mostrarCoord(fila,0) == tablero.mostrarCoord(fila,1) && tablero.mostrarCoord(fila,1)== tablero.mostrarCoord(fila,2)) {
            if (tablero.mostrarCoord(fila,0) == 'X')
                return +10;
            else if (tablero.mostrarCoord(fila,0) == 'O')
                return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (tablero.mostrarCoord(0,col)== tablero.mostrarCoord(1,col)&& tablero.mostrarCoord(1,col) == tablero.mostrarCoord(2,col)) {
            if (tablero.mostrarCoord(0,col)== 'X')
                return +10;
            else if (tablero.mostrarCoord(0,col)== 'O')
                return -10;
        }
    }

    if (tablero.mostrarCoord(0,0)== tablero.mostrarCoord(1,1) && tablero.mostrarCoord(1,1) == tablero.mostrarCoord(2,2)) {
        if (tablero.mostrarCoord(0,0)== 'X')
            return +10;
        else if (tablero.mostrarCoord(0,0) == 'O')
            return -10;
    }

    if (tablero.mostrarCoord(0,2) == tablero.mostrarCoord(1,1) && tablero.mostrarCoord(1,1)== tablero.mostrarCoord(2,0)) {
        if (tablero.mostrarCoord(0,2)== 'X')
            return +10;
        else if (tablero.mostrarCoord(0,2)== 'O')
            return -10;
    }

    return 0;
}

void movimiento(Tablero& tablero, bool player) {
    string input = "";
    int position;
    bool positionValid = true;
    bool safe;

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
                cout << "Ingrese un número válido (1-9)." << endl;
                positionValid = false;
                break;
        }

        if (positionValid) {
            safe = isSafe(cordx, cordy, tablero);
            if (!safe) {
                cout << "La posición ya está ocupada. Intenta de nuevo.\n";
                positionValid = false;
            }
        }

    } while (!positionValid);

    
    if (player == true) {
        tablero.cambiarCoord(cordx,cordy,'X');
    } else {
        tablero.cambiarCoord(cordx,cordy,'O');
    }
    tablero.gatoGame();
}

int minimax(Tablero& tablero, bool isPlayer, int alpha, int beta) {


    int score = winCheck(tablero);


    if (score == 10) return score;    
    if (score == -10) return score;   

    if (moveCheck(tablero) == true) return 0;

    if (isPlayer) {
        int puntajeMax = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isSafe(i, j, tablero)) {
                    char aux = tablero.mostrarCoord(i,j);
                    tablero.cambiarCoord(i,j,'X');;

                    int valor = minimax(tablero, !isPlayer, alpha, beta);

                    tablero.cambiarCoord(i,j,aux);

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
                if (isSafe(i, j, tablero)) {
                    char aux = tablero.mostrarCoord(i,j);
                    tablero.cambiarCoord(i,j,'O');

                    int valor = minimax(tablero, !isPlayer, alpha, beta);

                    tablero.cambiarCoord(i,j,aux);

                    if (valor < puntajeMin) puntajeMin = valor;
                    if (valor < beta) beta = valor;
                    if (beta <= alpha) break;
                }
            }
        }
        return puntajeMin;
    }
}

void whosWin(int score) {
    if (score == 10) {
        cout << "¡Gana el jugador X!" << endl;
    } else if (score == -10) {
        cout << "¡Gana el jugador O (IA)!" << endl;
    } else {
        cout << "¡Empate!" << endl;
    }
}

void bestMove(Tablero& tablero) {
    int best = 1000; 
    int x = -1, y = -1;



    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (isSafe(i, j, tablero)) {
                char aux = tablero.mostrarCoord(i,j);
                tablero.cambiarCoord(i,j,'O');

                int move = minimax(tablero, true, -9999, 9999);

                tablero.cambiarCoord(i,j,aux);

                if (move < best) {
                    best = move;
                    x = i;
                    y = j;
                }
            }
        }
    }

    if (x != -1 && y != -1) {
        tablero.cambiarCoord(x,y,'O');
        cout << "La IA (O) realiza su movimiento:\n";
        tablero.gatoGame();
    }
}

void singlePlayer(Tablero& tablero) {

    while (true) {
        int w = winCheck(tablero);
        if (w == 10 || w == -10 || moveCheck(tablero)) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        movimiento(tablero, true);
        w = winCheck(tablero);
        if (w == 10 || w == -10 || moveCheck(tablero)) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        bestMove(tablero);
        w = winCheck(tablero);
        if (w == 10 || w == -10 || moveCheck(tablero)) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }
    }
} 

void multiplayer(Tablero tablero) {
    bool player = true; 
    int w = 0; 

    tablero.gatoGame();

    while (true) {
        w = winCheck(tablero);
        if (w == 10 || w == -10 || moveCheck(tablero)) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        if (player) {
            cout << "Turno de Jugador X\n";
        } else {
            cout << "Turno de Jugador O\n";
        }
        movimiento(tablero, player);

        player = !player;
    }
}

int main() {

    int opcion;
    Tablero tablero;

    do {
        
        cout << "Ingrese una opción:" << endl;
        cout << "1) Jugador contra Jugador (JcJ)" << endl;
        cout << "2) Jugador contra IA (JcIA)" << endl;
        cout << "Opción: ";
        
        cin >> opcion;

        if (opcion < 1 || opcion > 2) {
            cout << "Por favor, ingrese una opción válida (1 o 2)." << endl;
        }
    } while (opcion < 1 || opcion > 2);

    switch (opcion) {
        case 1:
            multiplayer(tablero);
            break;
        case 2:
            singlePlayer(tablero);
            break;
        default:
            break;
    }

    system("pause");

    return -1;
}