#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include <utility>

using namespace std;

class Router {
public:
    Router(int id);
    int idRouter;
    Router* previo;
    vector<pair<Router*, int>> vecinos; // Un vector de pares, guarda los vecinos y los costos al vecino
    int distancia;
    bool visitado;
    void nuevoVecino(Router* vecino, int costo);
    void confDistancia(int distancia);
    void reinicio();
};

void dijkstra(Router* fuente);
void imprimirCamino(Router* destino);


#endif // ROUTER_H
