#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include <utility>
#include <map>

using namespace std;

class Router {
public:
    Router(int id);
    int idRouter;
    Router* previo;
    vector<pair<Router*, int>> vecinos;  // vecinos directos y sus costos
    map<int, int> tablaCostos;           // tabla de costos: destino -> costo minimo
    int distancia;                       // uso temporal de Dijkstra
    bool visitado;                       // uso temporal de Dijkstra

    void nuevoVecino(Router* vecino, int costo);
    void confDistancia(int distancia);
    void reinicio();
    void mostrarTabla(const map<int, Router*>& routers); // muestra la tabla de costos
};

void dijkstra(Router* fuente);
void imprimirCamino(Router* destino);

#endif // ROUTER_H
