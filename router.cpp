#include <iostream>
#include "Router.h"
#include <queue>
#include <climits>
#include <algorithm>

Router::Router(int id) : idRouter(id), distancia(INT_MAX), visitado(false), previo(nullptr) {}

void Router::nuevoVecino(Router* vecino, int costo)
{
    vecinos.emplace_back(vecino, costo);
}

void Router::confDistancia(int dist)
{
    distancia = dist;
}

void Router::reinicio()
{
    distancia = INT_MAX;
    visitado = false;
    previo = nullptr;
}

void Router::mostrarTabla(const map<int, Router*>& routers)
{
    cout << "Tabla de costos del Router " << char('A' + idRouter) << ":" << endl;
    cout << "  Destino | Costo" << endl;
    cout << "  --------|------" << endl;
    for (auto& par : routers)
    {
        int destId = par.first;
        int costo = -1;
        if (tablaCostos.count(destId))
            costo = tablaCostos.at(destId);

        cout << "     " << char('A' + destId) << "    |  ";
        if (costo == INT_MAX || costo == -1)
            cout << "inf" << endl;
        else
            cout << costo << endl;
    }
    cout << endl;
}

void dijkstra(Router* fuente)
{
    fuente->confDistancia(0);

    priority_queue<pair<int, Router*>> pq;
    pq.push({0, fuente});

    while (!pq.empty())
    {
        Router* actual = pq.top().second;
        pq.pop();

        if (actual->visitado) continue;
        actual->visitado = true;

        for (auto& vec : actual->vecinos)
        {
            Router* sigRouter = vec.first;
            int costoBorde = vec.second;

            int nuevaDistancia = actual->distancia + costoBorde;
            if (nuevaDistancia < sigRouter->distancia) {
                sigRouter->confDistancia(nuevaDistancia);
                sigRouter->previo = actual;
                pq.push({-nuevaDistancia, sigRouter});
            }
        }
    }
}

void imprimirCamino(Router* destino)
{
    if (destino == nullptr)
    {
        cout << "Router destino no encontrado." << endl;
        return;
    }
    if (destino->distancia == INT_MAX)
    {
        cout << "No hay camino al destino " << char('A' + destino->idRouter) << endl;
        return;
    }

    vector<Router*> camino;
    for (Router* r = destino; r != nullptr; r = r->previo)
    {
        camino.push_back(r);
    }
    reverse(camino.begin(), camino.end());

    cout << "Camino mas corto: ";
    for (size_t i = 0; i < camino.size(); ++i)
    {
        cout << char('A' + camino[i]->idRouter);
        if (i != camino.size() - 1)
            cout << " -> ";
    }
    cout << " | Costo: " << destino->distancia << endl;
}
