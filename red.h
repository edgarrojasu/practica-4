#ifndef RED_H
#define RED_H

#include "Router.h"
#include <map>

class Red {
private:
    map<int, Router*> routers;

public:
    void agregarRouter(int id);
    void conectar(int id1, int id2, int costo);
    Router* obtenerRouter(int id);
    void mostrarRed();
    void eliminarRouter(int id);
    void eliminarConexion(int id1, int id2);
    void limpiarVecinos(int id);
    void calcularCaminos(int origen);
    void actualizarTablas();
};

#endif
