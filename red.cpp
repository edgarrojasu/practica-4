#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <cctype>

using namespace std;

// ── Validacion interna ────────────────────────────────────────────────────────

int Red::letraAIndice(const string& token, bool desdeArchivo, int numLinea)
{
    if (token.size() != 1 || !isalpha((unsigned char)token[0]))
    {
        if (desdeArchivo)
        {
            throw runtime_error(
                "Linea " + to_string(numLinea) +
                ": identificador de router invalido '" + token +
                "'. Se esperaba una sola letra (a-z / A-Z)."
            );
        }
        else
        {
            cout << "Error: el identificador debe ser una sola letra (a-z). "
                 << "Volviendo al menu." << endl;
            return -1;
        }
    }
    return tolower((unsigned char)token[0]) - 'a';
}

// ── Metodos publicos ──────────────────────────────────────────────────────────

void Red::agregarRouter(const string& letra)
{
    int id = letraAIndice(letra);
    if (id == -1) return;

    if (routers.count(id) == 0)
        routers[id] = new Router(id);
}

void Red::conectar(const string& letra1, const string& letra2, int costo)
{
    int id1 = letraAIndice(letra1);
    if (id1 == -1) return;
    int id2 = letraAIndice(letra2);
    if (id2 == -1) return;

    Router* r1 = obtenerRouter(id1);
    Router* r2 = obtenerRouter(id2);

    if (r1 && r2)
    {
        // Eliminar conexion previa si existia
        auto& vecinos1 = r1->vecinos;
        for (auto it = vecinos1.begin(); it != vecinos1.end(); )
        {
            if (it->first->idRouter == id2) it = vecinos1.erase(it);
            else ++it;
        }

        auto& vecinos2 = r2->vecinos;
        for (auto it = vecinos2.begin(); it != vecinos2.end(); )
        {
            if (it->first->idRouter == id1) it = vecinos2.erase(it);
            else ++it;
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
        par.second->mostrarTabla(routers);
}

void Red::eliminarConexion(const string& letra1, const string& letra2)
{
    int id1 = letraAIndice(letra1);
    if (id1 == -1) return;
    int id2 = letraAIndice(letra2);
    if (id2 == -1) return;

    Router* router1 = obtenerRouter(id1);
    Router* router2 = obtenerRouter(id2);

    if (router1 == nullptr || router2 == nullptr) return;

    auto& vecinos1 = router1->vecinos;
    for (auto it = vecinos1.begin(); it != vecinos1.end(); )
    {
        if (it->first->idRouter == id2) it = vecinos1.erase(it);
        else ++it;
    }

    auto& vecinos2 = router2->vecinos;
    for (auto it = vecinos2.begin(); it != vecinos2.end(); )
    {
        if (it->first->idRouter == id1) it = vecinos2.erase(it);
        else ++it;
    }
}

void Red::limpiarVecinos(int id)
{
    for (auto& par : routers)
    {
        auto& vecinos = par.second->vecinos;
        for (auto it = vecinos.begin(); it != vecinos.end(); )
        {
            if (it->first->idRouter == id) it = vecinos.erase(it);
            else ++it;
        }
    }
}

void Red::eliminarRouter(const string& letra)
{
    int id = letraAIndice(letra);
    if (id == -1) return;

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
        par.second->reinicio();

    dijkstra(obtenerRouter(origen));

    Router* routerOrigen = obtenerRouter(origen);
    if (routerOrigen == nullptr) return;

    routerOrigen->tablaCostos.clear();
    for (auto& par : routers)
        routerOrigen->tablaCostos[par.first] = par.second->distancia;
}

void Red::actualizarTablas()
{
    cout << "\n=== Actualizando tablas de enrutamiento ===" << endl;
    for (auto& par : routers)
        calcularCaminos(par.first);
    cout << "Tablas actualizadas correctamente." << endl;
}

void Red::cargarDesdeArchivo(const string& archivo)
{
    ifstream f(archivo);
    if (!f.is_open())
        throw runtime_error("No se pudo abrir el archivo '" + archivo + "'");

    string linea;
    int numLinea = 0;

    while (getline(f, linea))
    {
        ++numLinea;
        if (linea.empty() || linea[0] == '#') continue;

        istringstream ss(linea);
        string tipo;
        ss >> tipo;

        if (tipo == "router")
        {
            string token;
            if (!(ss >> token))
                throw runtime_error(
                    "Linea " + to_string(numLinea) +
                    ": falta el identificador del router."
                );
            int id = letraAIndice(token, true, numLinea);
            routers.count(id) == 0 && (routers[id] = new Router(id));
        }
        else if (tipo == "enlace")
        {
            string t1, t2;
            int costo;
            if (!(ss >> t1 >> t2 >> costo))
                throw runtime_error(
                    "Linea " + to_string(numLinea) +
                    ": formato invalido. Se esperaba: enlace <letra> <letra> <costo>."
                );
            int id1 = letraAIndice(t1, true, numLinea);
            int id2 = letraAIndice(t2, true, numLinea);

            Router* r1 = obtenerRouter(id1);
            Router* r2 = obtenerRouter(id2);
            if (r1 && r2)
            {
                auto& v1 = r1->vecinos;
                for (auto it = v1.begin(); it != v1.end(); )
                {
                    if (it->first->idRouter == id2) it = v1.erase(it);
                    else ++it;
                }
                auto& v2 = r2->vecinos;
                for (auto it = v2.begin(); it != v2.end(); )
                {
                    if (it->first->idRouter == id1) it = v2.erase(it);
                    else ++it;
                }
                r1->nuevoVecino(r2, costo);
                r2->nuevoVecino(r1, costo);
            }
        }
    }

    f.close();
    actualizarTablas();
    cout << "Red cargada desde '" << archivo << "'" << endl;
}

void Red::calcularCaminos(const string& letra)
{
    int id = letraAIndice(letra);
    if (id == -1) return;
    calcularCaminos(id);
}

Router* Red::obtenerRouter(const string& letra)
{
    int id = letraAIndice(letra);
    if (id == -1) return nullptr;
    return obtenerRouter(id);
}
