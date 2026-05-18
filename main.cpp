#include <iostream>
#include <string>
#include "Red.h"
#include "menu.h"

using namespace std;

// Lee una letra de router desde cin.
// Devuelve el indice (a=0, b=1, ...) o -1 si la entrada es invalida.
int leerLetraRouter(const string& prompt)
{
    string entrada;
    cout << prompt;
    cin >> entrada;

    if (entrada.size() != 1 || !isalpha((unsigned char)entrada[0]))
    {
        cout << "Error: el identificador de router debe ser una sola letra (a-z / A-Z)." << endl;
        return -1;
    }

    return tolower((unsigned char)entrada[0]) - 'a';
}

int main()
{
    Red red;
    int opcion;

    try
    {

        do
        {

            opcion = menu();

            switch (opcion)
            {
                case 1:
                {
<<<<<<< HEAD
                    int id = leerLetraRouter("Letra del router (a, b, c, ...): ");
                    if (id == -1) break;
                    red.agregarRouter(id);
=======
                    string letra;
                    cout << "Letra del router (a, b, c, ...): ";
                    cin >> letra;
                    red.agregarRouter(letra);
>>>>>>> extratemporal
                    red.actualizarTablas();
                    break;
                }
                case 2:
                {
<<<<<<< HEAD
                    int a = leerLetraRouter("Router 1 (letra): ");
                    if (a == -1) break;
                    int b = leerLetraRouter("Router 2 (letra): ");
                    if (b == -1) break;
                    int costo;
                    cout << "Costo: ";
                    if (!(cin >> costo))
                    {
                        cout << "Error: costo invalido." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        break;
                    }
=======
                    string a, b;
                    int costo;
                    cout << "Router 1 (letra): "; cin >> a;
                    cout << "Router 2 (letra): "; cin >> b;
                    cout << "Costo: ";            cin >> costo;
>>>>>>> extratemporal
                    red.conectar(a, b, costo);
                    red.actualizarTablas();
                    break;
                }
                case 3:
                {
<<<<<<< HEAD
                    int id = leerLetraRouter("Letra del router a eliminar: ");
                    if (id == -1) break;
                    red.eliminarRouter(id);
=======
                    string letra;
                    cout << "Router a eliminar (letra): ";
                    cin >> letra;
                    red.eliminarRouter(letra);
>>>>>>> extratemporal
                    red.actualizarTablas();
                    break;
                }
                case 4:
                {
<<<<<<< HEAD
                    int a = leerLetraRouter("Router 1 (letra): ");
                    if (a == -1) break;
                    int b = leerLetraRouter("Router 2 (letra): ");
                    if (b == -1) break;
=======
                    string a, b;
                    cout << "Router 1 (letra): "; cin >> a;
                    cout << "Router 2 (letra): "; cin >> b;
>>>>>>> extratemporal
                    red.eliminarConexion(a, b);
                    red.actualizarTablas();
                    break;
                }
                case 5:
                {
                    red.mostrarRed();
                    break;
                }
                case 6:
                {
<<<<<<< HEAD
                    int origen = leerLetraRouter("Origen (letra): ");
                    if (origen == -1) break;
                    int destino = leerLetraRouter("Destino (letra): ");
                    if (destino == -1) break;
=======
                    string origen, destino;
                    cout << "Origen (letra): ";  cin >> origen;
                    cout << "Destino (letra): "; cin >> destino;
>>>>>>> extratemporal
                    red.calcularCaminos(origen);
                    imprimirCamino(red.obtenerRouter(destino));
                    break;
                }
                case 7:
                {
                    string archivo;
                    archivo = "conexiones.txt";
                    red.cargarDesdeArchivo(archivo);
                    break;
                }
                case 0:
                {
                    cout << "Saliendo..." << endl;
                    break;
                }
                default:
                {
                    cout << "Opcion invalida. Intente de nuevo." << endl;
                    break;
                }
            }

        } while (opcion != 0);

    }
    catch (const runtime_error& e)
    {
        cerr << "Error de ejecucion: " << e.what() << endl;
        return 1;
    }
    catch (const exception& e)
    {
        cerr << "Error inesperado: " << e.what() << endl;
        return 1;
    }

    return 0;
}
