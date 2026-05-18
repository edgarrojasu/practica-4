#ifndef RED_H
#define RED_H

#include "Router.h"
#include <map>
#include <string>

class Red {
private:
    map<int, Router*> routers;

    // Convierte una letra a indice (a/A=0, b/B=1, ...).
    // desdeArchivo=false: imprime error y devuelve -1 si es invalida.
    // desdeArchivo=true:  lanza runtime_error con numero de linea.
    int letraAIndice(const string& token, bool desdeArchivo = false, int numLinea = 0);

public:
    void agregarRouter(const string& letra);
    void conectar(const string& letra1, const string& letra2, int costo);
    Router* obtenerRouter(int id);
    Router* obtenerRouter(const string& letra);
    void mostrarRed();
    void eliminarRouter(const string& letra);
    void eliminarConexion(const string& letra1, const string& letra2);
    void limpiarVecinos(int id);
    void calcularCaminos(int origen);
    void calcularCaminos(const string& letra);
    void actualizarTablas();
    void cargarDesdeArchivo(const string& archivo);
};

#endif
