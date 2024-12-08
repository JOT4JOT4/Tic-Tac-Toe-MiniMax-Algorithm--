#include <string>
#include <vector>
#include <iostream>

using namespace std;

int score = 1;
bool player = true;
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

int winCheck(char tablero[3][3]) {

    if(player == true){
        for(int a=0;a<3;a++) {
        if(tablero[a][0]==tablero[a][1] && tablero[a][0]==tablero[a][2] || tablero[0][a]==tablero[1][a] && tablero[0][a]==tablero[2][a]){
            return -10;
        }
        }
        if(tablero[0][0]==tablero[1][1] && tablero[1][1]==tablero[2][2] || tablero[0][2]==tablero[1][1] && tablero[1][1]==tablero[2][0]){
           return -10;
        }
    }
    else {
        for(int a=0;a<3;a++) {
        if(tablero[a][0]==tablero[a][1] && tablero[a][0]==tablero[a][2] || tablero[0][a]==tablero[1][a] && tablero[0][a]==tablero[2][a]){
            return 10;
        }
        }
        if(tablero[0][0]==tablero[1][1] && tablero[1][1]==tablero[2][2] || tablero[0][2]==tablero[1][1] && tablero[1][1]==tablero[2][0]){
           return 10;
        }
    }

    if(moveCheck(tablero) == true){
        cout<< "No more moves" <<endl;  
        return 0;
    }
    
    return 1;
}

void movimiento(char tablero[3][3]) {

    string input = "";
    int position;
    bool positionValid = true;
    bool safe;
    do {
        positionValid = true;
        cout<< "Enter a number (1-9)" << endl;
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
            cout<< "Enter a correct number (1-9)" << endl;
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
        tablero[cordx][cordy] = 'X';
        player = false;
        gatoGame(tablero);
    }

    else {
        tablero[cordx][cordy] = 'O';
        player = true;
        gatoGame(tablero); 
    }
}

int minimax(char tablero[3][3], bool isPlayer, int alpha, int beta){

    int score = winCheck(tablero);

    if(score == 10) return score;

    if(score == -10) return score;

    if(moveCheck(tablero)==false) return 0;

    if(isPlayer){
        int puntajeMax = -1000;
        for(int i = 0;i<3;i++){
            for(int j = 0;j<3;j++){

                if(isSafe(i,j,tablero)){
                    tablero[i][j] = 'X';
                }
                puntajeMax = max(puntajeMax,minimax(tablero,!isPlayer,alpha,beta));
                alpha = max(alpha,puntajeMax);
                
                if(beta <= alpha) {
                break;
            }
            }
        }
        return puntajeMax;
    }
    else {
        int puntajeMin = 1000;

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){

                if(isSafe(i,j,tablero)){
                    tablero[i][j] = 'O';
                }
                puntajeMin = min(puntajeMin,minimax(tablero,!isPlayer,alpha,beta));
                beta = min(beta,puntajeMin);
                if(beta <= alpha) {
                    break;
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
    if(score == -10){
        cout<< "Player O Wins!!"<< endl;
    }
    else {
        cout<< "It a Draw!!"<< endl;
    }
}

int main() {

    char tablero[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

    gatoGame(tablero);
    while(winCheck(tablero)==1){
        movimiento(tablero);
        minimax(tablero,false,-999,999);
        winCheck(tablero);
    }

    whosWin(winCheck(tablero));
    cout<< "GAME OVER" <<endl;

    system("pause");

    return -1;
}