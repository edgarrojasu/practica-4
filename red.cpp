#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

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
        auto& vecinos1 = r1->vecinos;
        for (auto it = vecinos1.begin(); it != vecinos1.end(); )
        {
            if (it->first->idRouter == id2)
                it = vecinos1.erase(it);
            else
                ++it;
        }

        auto& vecinos2 = r2->vecinos;
        for (auto it = vecinos2.begin(); it != vecinos2.end(); )
        {
            if (it->first->idRouter == id1)
                it = vecinos2.erase(it);
            else
                ++it;
        }

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
    cout << "\n=== Topologia de la red ===" << endl;
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
    cout << endl;

    for (auto& par : routers)
    {
        par.second->mostrarTabla(routers);
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
    for (auto& par : routers) {
        par.second->reinicio();
    }

    dijkstra(obtenerRouter(origen));

    Router* routerOrigen = obtenerRouter(origen);
    if (routerOrigen == nullptr) return;

    routerOrigen->tablaCostos.clear();
    for (auto& par : routers)
    {
        routerOrigen->tablaCostos[par.first] = par.second->distancia;
    }
}

void Red::actualizarTablas()
{
    cout << "\n=== Actualizando tablas de enrutamiento ===" << endl;
    for (auto& par : routers)
    {
        calcularCaminos(par.first);
    }
    cout << "Tablas actualizadas correctamente." << endl;
}

void Red::cargarDesdeArchivo(const string& archivo)
{
    ifstream f(archivo);
    if (!f.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo");
    }

    string linea;
    while (getline(f, linea))
    {
        if (linea.empty() || linea[0] == '#') continue;

        istringstream ss(linea);
        string tipo;
        ss >> tipo;

        if (tipo == "router")
        {
            int id;
            ss >> id;
            agregarRouter(id);
        }
        else if (tipo == "enlace")
        {
            int id1, id2, costo;
            ss >> id1 >> id2 >> costo;
            conectar(id1, id2, costo);
        }
    }

    f.close();
    actualizarTablas();
    cout << "Red cargada desde '" << archivo << "'" << endl;
}
