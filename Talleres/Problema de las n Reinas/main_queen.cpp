#include <iostream>
#include <vector>

using namespace std;

bool esValido(vector<int>& tablero, int fila, int columna) {
    // Comprobar las filas anteriores
    for (int i = 0; i < fila; i++) {
        // Si hay otra reina en la misma columna o en diagonal, no es válido
        if (tablero[i] == columna || tablero[i] - columna == i - fila || tablero[i] - columna == fila - i) {
            return false;
        }
    }
    return true;
}

void resolverNReinas(vector<int>& tablero, int fila, int n, int& solucionesEncontradas) {
    if (fila == n) {
        // Se encontró una solución
        solucionesEncontradas++;
        cout << "Solucion " << solucionesEncontradas << ":" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tablero[i] == j) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    for (int columna = 0; columna < n; columna++) {
        if (esValido(tablero, fila, columna)) {
            tablero[fila] = columna;
            resolverNReinas(tablero, fila + 1, n, solucionesEncontradas);
        }
    }
}

void nReinas(int n) {
    vector<int> tablero(n, 0);
    int solucionesEncontradas = 0;
    resolverNReinas(tablero, 0, n, solucionesEncontradas);
    cout << "Total de soluciones encontradas: " << solucionesEncontradas << endl;
}

int main() {
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;
    nReinas(n);
    return 0;
}