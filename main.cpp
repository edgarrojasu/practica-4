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
                    string letra;
                    cout << "Letra del router (a, b, c, ...): ";
                    cin >> letra;
                    red.agregarRouter(letra);
                    red.actualizarTablas();
                    break;
                }
                case 2:
                {
                    string a, b;
                    int costo;
                    cout << "Router 1 (letra): "; cin >> a;
                    cout << "Router 2 (letra): "; cin >> b;
                    cout << "Costo: ";            cin >> costo;
                    red.conectar(a, b, costo);
                    red.actualizarTablas();
                    break;
                }
                case 3:
                {
                    string letra;
                    cout << "Router a eliminar (letra): ";
                    cin >> letra;
                    red.eliminarRouter(letra);
                    red.actualizarTablas();
                    break;
                }
                case 4:
                {
                    string a, b;
                    cout << "Router 1 (letra): "; cin >> a;
                    cout << "Router 2 (letra): "; cin >> b;
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
                    string origen, destino;
                    cout << "Origen (letra): ";  cin >> origen;
                    cout << "Destino (letra): "; cin >> destino;
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
