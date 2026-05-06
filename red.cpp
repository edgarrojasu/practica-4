#include "red.h"
#include <iostream>

using namespace std;

void Red::agregarRouter(int id)
{
    if (routers.count(id) == 0)
    {
        routers[id] = new Router(id);
    }
}

void Red::conectar(int id1, int id2, int costo)
{
    Router* r1 = obtenerRouter(id1);
    Router* r2 = obtenerRouter(id2);

    if (r1 && r2)
    {
        r1->nuevoVecino(r2, costo);
        r2->nuevoVecino(r1, costo);
    }
}

Router* Red::obtenerRouter(int id)
{
    if (routers.count(id))
        return routers[id];
    return nullptr;
}

void Red::mostrarRed()
{
    for (auto& par : routers)
    {
        cout << "Router " << char('A' + par.first) << ": ";

        for (auto& vecino : par.second->vecinos)
        {
            cout << char('A' + vecino.first->idRouter)
            << "(" << vecino.second << ") ";
        }

        cout << endl;
    }
}

void Red::eliminarConexion(int id1, int id2)
{
    Router* router1 = obtenerRouter(id1);
    Router* router2 = obtenerRouter(id2);

    if (router1 == nullptr || router2 == nullptr) return;

    auto& vecinos1 = router1->vecinos;
    for (auto it = vecinos1.begin(); it != vecinos1.end(); )
    {
        if (it->first->idRouter == id2)
            it = vecinos1.erase(it);
        else
            ++it;
    }

    auto& vecinos2 = router2->vecinos;
    for (auto it = vecinos2.begin(); it != vecinos2.end(); )
    {
        if (it->first->idRouter == id1)
            it = vecinos2.erase(it);
        else
            ++it;
    }
}

void Red::limpiarVecinos(int id)
{
    for (auto& par : routers)
    {
        auto& vecinos = par.second->vecinos;

        for (auto it = vecinos.begin(); it != vecinos.end(); )
        {
            if (it->first->idRouter == id)
                it = vecinos.erase(it);
            else
                ++it;
        }
    }
}

void Red::eliminarRouter(int id)
{
    if (routers.count(id))
    {
        limpiarVecinos(id);
        delete routers[id];
        routers.erase(id);
    }
}

void Red::calcularCaminos(int origen)
{
    for (auto& par : routers)
    {
        par.second->reinicio();
        par.second->previo = nullptr;
    }

    dijkstra(obtenerRouter(origen));
}

void Red::actualizarTablas()
{
    for (auto& par : routers)
    {
        calcularCaminos(par.first);

        cout << "Router " << char('A' + par.first) << endl;

        for (auto& destino : routers)
        {
            cout << " -> "
            << char('A' + destino.first)
            << " costo: "
            << destino.second->distancia
            << endl;
        }
        cout << endl;
    }
}
