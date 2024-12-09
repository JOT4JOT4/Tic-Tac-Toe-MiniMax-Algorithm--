#include <string>
#include <vector>
#include <iostream>

using namespace std;

int score = 1;
int cordx;
int cordy;

void gatoGame(char tablero[3][3]){
    
    cout<< "    |    |    \n";
    cout<< " "<<tablero[0][0]<<"  | " <<tablero[0][1]<<"  | "<<tablero[0][2]<<"  \n";
    cout<< "____|____|____\n";
    cout<< "    |    |    \n";
    cout<< " "<<tablero[1][0]<<"  | " <<tablero[1][1]<<"  | "<<tablero[1][2]<<"  \n";
    cout<< "____|____|____\n";
    cout<< "    |    |    \n";
    cout<< " "<<tablero[2][0]<<"  | " <<tablero[2][1]<<"  | "<<tablero[2][2]<<"  \n";
    cout<< "    |    |    \n";

    return;
}

bool is_number(string& s){
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool isSafe(int x, int y,char tablero[3][3]) {

    if(tablero[x][y] != 'X' && tablero[x][y] != 'O') return true;

    return false;
}

bool moveCheck(char tablero[3][3]) {
    for(int i=0;i<3;i++){
         for(int j=0;j<3;j++){
            if(tablero[i][j] != 'X' && tablero[i][j] != 'O'){
                return false;
            }
        }
    }
    return true;
}

int winCheck(char b[3][3]) {
     // Checking for Rows for X or O victory. 
    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]=='X') 
                return +10; 
            else if (b[row][0]== 'O') 
                return -10; 
        } 
    } 
  
    // Checking for Columns for X or O victory. 
    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]=='X') 
                return +10; 
  
            else if (b[0][col]== 'O') 
                return -10; 
        } 
    } 
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]=='X') 
            return +10; 
        else if (b[0][0]== 'O') 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]=='X') 
            return +10; 
        else if (b[0][2]== 'O') 
            return -10; 
    } 
  
    return 0; 
}

void movimiento(char tablero[3][3], bool player) {
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

    // Coloca el coso
    if (player == true) {
        tablero[cordx][cordy] = 'X';
    } else {
        tablero[cordx][cordy] = 'O';
    }
    gatoGame(tablero);
}

int minimax(char tablero[3][3], bool isPlayer, int alpha, int beta) {
    
    int score = winCheck(tablero);

    if (score == 10){
        return score;    // X gana
    }
    if (score == -10){
        return score;   // O gana
    }
    // Empate
    if (moveCheck(tablero) == true) return 0;

    if (isPlayer) {
        // X
        int puntajeMax = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                
                if (isSafe(i, j, tablero)) {

                    char aux = tablero[i][j];
                    tablero[i][j] = 'X';

                    int valor = minimax(tablero, !isPlayer, alpha, beta);

                    tablero[i][j] = aux;

                    if (valor > puntajeMax) puntajeMax = valor;
                    if (valor > alpha) alpha = valor;
                    if (beta <= alpha) break;
                }
            }
        }
        return puntajeMax;
    } else {
        // O
        int puntajeMin = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isSafe(i, j, tablero)) {
                    char aux = tablero[i][j];
                    tablero[i][j] = 'O';

                    int valor = minimax(tablero, !isPlayer, alpha, beta);

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


void whosWin(int score) {
    if(score == 10){
        cout<< "Player X Wins!!"<< endl;
    }
    else if(score == -10){
        cout<< "Player(IA) O Wins!!"<< endl;
    }
    else {
        cout<< "It a Draw!!"<< endl;
    }
}

char tableroAuxiliar(char tablero[3][3],char tableroAux[3][3]) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tableroAux[i][j] = tablero[i][j];
        }
    }
    return tableroAux[3][3];
}

void bestMove(char tablero[3][3]) {
    int best = 9999; 
    int x = -1;
    int y = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (isSafe(i, j, tablero)) {
                char aux = tablero[i][j];
                tablero[i][j] = 'O';

                int move = minimax(tablero, true, -9999, 9999);

                tablero[i][j] = aux;

                if (move < best) {
                    best = move;
                    x = i;
                    y = j;
                }
            }
        }
    }

    if (x != -1 && y != -1) {
        tablero[x][y] = 'O';
        cout << "La IA (O) realiza su movimiento:\n";
        gatoGame(tablero);
    }
}

void singlePlayer(char tablero[3][3]) {
    // X = humano (maximizador), O = IA (minimizadorr)
    // Empieza el (X)
    while (true) {
        int w = winCheck(tablero);
        if (w == 10 || w == -10 || moveCheck(tablero)) {
            // Alguien ganó o no hay más movimientos
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        // Movimiento X
        movimiento(tablero, true);
        w = winCheck(tablero);
        if (w == 10 || w == -10 || moveCheck(tablero)) {
            // Alguien ganó o empate
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }

        // Movimiento IA O
        bestMove(tablero);
        w = winCheck(tablero);
        if (w == 10 || w == -10 || moveCheck(tablero)) {
            whosWin(w);
            cout << "GAME OVER" << endl;
            break;
        }
    }
}

void multiplayer(char tablero[3][3]) {

        gatoGame(tablero);
        while(winCheck(tablero)==1){
            movimiento(tablero,true);
            minimax(tablero,false,-999,999);
            winCheck(tablero);
        }
}

int main() {

    char tablero[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

    singlePlayer(tablero);

    system("pause");

    return -1;
}