#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool player = true;
char tablero[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
int cordx;
int cordy;

void gatoGame(){
    
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

bool isSafe(int x, int y) {

    if(tablero[x][y] != 'X' && tablero[x][y] != 'O') return true;

    return false;
}

bool mateCheck() {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(tablero[i][j] != 'X' && tablero[i][j] != 'O'){
                return false;
            }
        }
    }
    return true;
}

bool winCheck() {
    for(int a=0;a<3;a++) {
        if(tablero[a][0]==tablero[a][1] && tablero[a][0]==tablero[a][2] || tablero[0][a]==tablero[1][a] && tablero[0][a]==tablero[2][a]){
            return true;
        }
    }
    if(tablero[0][0]==tablero[1][1] && tablero[1][1]==tablero[2][2] || tablero[0][2]==tablero[1][1] && tablero[1][1]==tablero[2][0]){
        return true;
    }
    return false;
}

void movimiento() {

    int position;
    bool positionValid = true;
    do {
        positionValid = true;
        cout<< "Ingresa una Coordenada (1-9)" << endl;
        cin>>position;
    

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
            cout<< "Ingresa una Coordenada válida (1-9)" << endl;
            positionValid = false;
            break;
    }
    }while (!positionValid);

    if(player == true && isSafe(cordx,cordy)) {
        tablero[cordx][cordy] = 'X';
        player = false;
        gatoGame();
    }

    if(player == false && isSafe(cordx,cordy)) {
        tablero[cordx][cordy] = 'O';
        player = true;
        gatoGame();
    }

}

int main() {

    while(!winCheck()){
        movimiento();
        winCheck();
    }

    if(winCheck()){
        cout<< "Fin de la partida" <<endl;
    }

    else if(mateCheck()){
        cout<< "Nadie gana la partida, suerte a la proxima" << endl;
    }

    system("pause");

    return -1;
}