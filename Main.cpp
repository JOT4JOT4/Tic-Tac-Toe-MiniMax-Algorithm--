#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Tablero.cpp"

using namespace std;

int score = 1;
int cordx;
int cordy;

int main() {

    int opcion;
    Tablero tablero;

    do {
        
        cout << "Ingrese una opcion:" << endl;
        cout << "1) Jugador contra Jugador (JcJ)" << endl;
        cout << "2) Jugador contra IA (JcIA)" << endl;
        cout << "Opcion: ";
        
        cin >> opcion;

        if (opcion < 1 || opcion > 2) {
            cout << "Por favor, ingrese una opcion valida (1 o 2)." << endl;
        }
    } while (opcion < 1 || opcion > 2);

    switch (opcion) {
        case 1:
            tablero.multiplayer();
            break;
        case 2:
            tablero.singlePlayer();
            break;
        default:
            break;
    }

    system("pause");

    return -1;
}