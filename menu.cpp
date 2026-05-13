#include "menu.h"
#include <iostream>

using namespace std;


int menu()
{
    int selected;
    while (true)
    {
        cout << "\n--- MENU ---";
        cout << "\n1. Agregar router";
        cout << "\n2. Conectar routers";
        cout << "\n3. Eliminar router";
        cout << "\n4. Eliminar conexion";
        cout << "\n5. Mostrar red y tablas de costos";
        cout << "\n6. Calcular camino entre dos routers";
        cout << "\n7. Cargar red desde archivo";
        cout << "\n0. Salir\n";
        cout << "Opcion: ";

        if (cin >> selected)
        {
            return selected;
        }
        else
        {
            cout << endl << "Ingrese una opcion valida." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}
