#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

vector<vector<char>> tablero(3, vector<char>(3));

void inicializarTablero() {
    int numero = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = '0' + numero;
            numero++;
        }
    }
}

void imprimirTablero() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << tablero[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------\n";
    }
}

pair<int, int> convertirNumeroACoordenadas(int numero) {
    return {(numero - 1) / 3, (numero - 1) % 3};
}

bool verificarGanador(char jugador) {
    for (int i = 0; i < 3; i++) {
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) || 
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            return true;
        }
    }
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)) {
        return true;
    }
    return false;
}

bool tableroLleno() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

vector<pair<int, int>> obtenerMovimientos() {
    vector<pair<int, int>> movimientos;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                movimientos.push_back({i, j});
            }
        }
    }
    return movimientos;
}

int evaluar() {
    if (verificarGanador('O')) return 1;  // Gano la maquina
    if (verificarGanador('X')) return -1; // Gano el jugador
    return 0;  // Empate
}

int minimax(int profundidad, bool esMaximizador, int alfa, int beta) {
    int puntuacion = evaluar();

    if (puntuacion == 1 || puntuacion == -1) return puntuacion;
    if (tableroLleno()) return 0;

    if (esMaximizador) {
        int mejor = -INT_MAX;
        for (auto movimiento : obtenerMovimientos()) {
            tablero[movimiento.first][movimiento.second] = 'O';
            mejor = max(mejor, minimax(profundidad + 1, false, alfa, beta));
            tablero[movimiento.first][movimiento.second] = ' ';
            alfa = max(alfa, mejor);
            if (beta <= alfa) break;
        }
        return mejor;
    } else {
        int mejor = INT_MAX;
        for (auto movimiento : obtenerMovimientos()) {
            tablero[movimiento.first][movimiento.second] = 'X';
            mejor = min(mejor, minimax(profundidad + 1, true, alfa, beta));
            tablero[movimiento.first][movimiento.second] = ' ';
            beta = min(beta, mejor);
            if (beta <= alfa) break;
        }
        return mejor;
    }
}

pair<int, int> mejorMovimiento() {
    int mejorValor = -INT_MAX;
    pair<int, int> mejorMov = {-1, -1};

    for (auto movimiento : obtenerMovimientos()) {
        tablero[movimiento.first][movimiento.second] = 'O';
        int valorMovimiento = minimax(0, false, -INT_MAX, INT_MAX);
        tablero[movimiento.first][movimiento.second] = ' ';

        if (valorMovimiento > mejorValor) {
            mejorMov = movimiento;
            mejorValor = valorMovimiento;
        }
    }
    return mejorMov;
}

void jugarJCJ() {
    char jugador = 'X';
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        imprimirTablero();
        int numero;
        cout << "Jugador " << jugador << ", elija un numero del 1 al 9: ";
        cin >> numero;

        if (numero < 1 || numero > 9) {
            cout << "Movimiento invalido, intenta de nuevo.\n";
            continue;
        }

        pair<int, int> coordenadas = convertirNumeroACoordenadas(numero);

        if (tablero[coordenadas.first][coordenadas.second] == 'X' || tablero[coordenadas.first][coordenadas.second] == 'O') {
            cout << "La posicion ya esta ocupada, intenta de nuevo.\n";
            continue;
        }

        tablero[coordenadas.first][coordenadas.second] = jugador;

        if (verificarGanador(jugador)) {
            imprimirTablero();
            cout << "El jugador " << jugador << " ha ganado!" << endl;
            juegoTerminado = true;
        } else if (tableroLleno()) {
            imprimirTablero();
            cout << "Es un empate!" << endl;
            juegoTerminado = true;
        } else {
            jugador = (jugador == 'X') ? 'O' : 'X';
        }
    }
}

void jugarJCmaquina() {
    char jugador = 'X';
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        imprimirTablero();

        if (jugador == 'X') {
            int numero;
            cout << "Jugador " << jugador << ", elija un numero del 1 al 9: ";
            cin >> numero;

            if (numero < 1 || numero > 9) {
                cout << "Movimiento invalido, intenta de nuevo.\n";
                continue;
            }

            pair<int, int> coordenadas = convertirNumeroACoordenadas(numero);

            if (tablero[coordenadas.first][coordenadas.second] == 'X' || tablero[coordenadas.first][coordenadas.second] == 'O') {
                cout << "La posicion ya esta ocupada, intenta de nuevo.\n";
                continue;
            }

            tablero[coordenadas.first][coordenadas.second] = jugador;
        } else {
            cout << "Es el turno de la maquina (O).\n";
            pair<int, int> mov = mejorMovimiento();
            tablero[mov.first][mov.second] = 'O';
        }

        int numero = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                    tablero[i][j] = '0' + numero;
                }
                numero++;
            }
        }

        if (verificarGanador(jugador)) {
            imprimirTablero();
            if (jugador == 'X') cout << "El jugador ha ganado!" << endl;
            else cout << "La maquina ha ganado!" << endl;
            juegoTerminado = true;
        } else if (tableroLleno()) {
            imprimirTablero();
            cout << "Es un empate!" << endl;
            juegoTerminado = true;
        } else {
            jugador = (jugador == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    while (true) {
        int opcion;
        inicializarTablero();

        cout << "\nBienvenidos al Tic-Tac-Toe!\n";
        cout << "Seleccione una opcion:\n";
        cout << "1. Jugador contra Jugador (JCJ)\n";
        cout << "2. Jugador contra Maquina (JCmaquina)\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            jugarJCJ();
        } else if (opcion == 2) {
            jugarJCmaquina();
        } else if (opcion == 3) {
            cout << "Saliendo del programa. Gracias por jugar!\n";
            break;
        } else {
            cout << "Opcion invalida, intenta de nuevo.\n";
        }
    }
    return 0;
}