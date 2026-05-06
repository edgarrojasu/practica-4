#include <iostream>
#include "Red.h"

using namespace std;

int main() {
    Red red;
    int opcion;

    do {
        cout << "\n--- MENU ---";
        cout << "\n1. Agregar router";
        cout << "\n2. Conectar routers";
        cout << "\n3. Eliminar router";
        cout << "\n4. Eliminar conexion";
        cout << "\n5. Mostrar red";
        cout << "\n6. Calcular camino";
        cout << "\n0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            cout << "ID del router: ";
            cin >> id;

            red.agregarRouter(id);
            red.actualizarTablas();
        }

        else if (opcion == 2) {
            int a, b, costo;
            cout << "Router 1: "; cin >> a;
            cout << "Router 2: "; cin >> b;
            cout << "Costo: "; cin >> costo;

            red.conectar(a, b, costo);
            red.actualizarTablas();
        }

        else if (opcion == 3) {
            int id;
            cout << "Router a eliminar: ";
            cin >> id;

            red.eliminarRouter(id);
            red.actualizarTablas();
        }

        else if (opcion == 4) {
            int a, b;
            cout << "Router 1: "; cin >> a;
            cout << "Router 2: "; cin >> b;

            red.eliminarConexion(a, b);
            red.actualizarTablas();
        }

        else if (opcion == 5) {
            red.mostrarRed();
        }

        else if (opcion == 6) {
            int origen, destino;
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;

            red.calcularCaminos(origen);
            imprimirCamino(red.obtenerRouter(destino));
        }

    } while (opcion != 0);

    return 0;
}
