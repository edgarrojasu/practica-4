#include <iostream>
#include "Red.h"
#include "menu.h"

using namespace std;

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
                    int id;
                    cout << "ID del router (0=A, 1=B, ...): ";
                    cin >> id;
                    red.agregarRouter(id);
                    red.actualizarTablas();
                    break;
                }
                case 2:
                {
                    int a, b, costo;
                    cout << "Router 1 (ID): "; cin >> a;
                    cout << "Router 2 (ID): "; cin >> b;
                    cout << "Costo: ";         cin >> costo;
                    red.conectar(a, b, costo);
                    red.actualizarTablas();
                    break;
                }
                case 3:
                {
                    int id;
                    cout << "Router a eliminar (ID): ";
                    cin >> id;
                    red.eliminarRouter(id);
                    red.actualizarTablas();
                    break;
                }
                case 4:
                {
                    int a, b;
                    cout << "Router 1 (ID): "; cin >> a;
                    cout << "Router 2 (ID): "; cin >> b;
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
                    int origen, destino;
                    cout << "Origen (ID): ";  cin >> origen;
                    cout << "Destino (ID): "; cin >> destino;
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
