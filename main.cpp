/**
 * @file main.cpp
 * 
 * @author Abraham Chalita Nuñez
 * @author Jesus Daniel Revas Nuño
 * @author Eduardo Angeles Guerrero
 * 
 * @brief Entregabke de actividad integradora 2
 * 
 * @version 0.1
 * @date 2022-10-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Funcion para obtener la matriz de entrada.
 * 
 * @param filename Nombre de archivo de texto de la matriz de adyacencia.
 * @return vector<vector<int>> mat
 */
vector<vector<int>> getMatrix (string filename) {

}

/**
 * @brief Punto 1 - Cableado optimo de las colonias
 * Se uso el algoritmo de Prim para encontrar un arbol de expansion minima cuya suma de sus arcos sea
 * la minima. De esta manera se puede optimizar el material usado para conectar a las colonias.
 */
class Solution_1 {
    private:
    // Checa si todos los nodos ya han sido visitados | O(n)
    bool all_visited (vector<bool> nodes) {
        for (bool visited : nodes) {
            if (!visited) return false;
        }
        return true;
    }
    
    // Algoritmo de Prim para arboles de expansion minima | O(n^2)
    void prim_algo (vector<vector<int>> &matrix, int n, int begin, vector<bool> &visited_nodes) {
        visited_nodes[begin] = true;

        // While not all nodes have been visited
        while (!all_visited(visited_nodes))
        {
            pair<int,int> edge;
            int best_distance = INT_MAX;
            // Looking through all the current nodes
            for (int start = 0; start < n; start++) {
                if (visited_nodes[start]) {
                    // Looking at the edges of participating nodes to get the best option
                    for (int end = 0; end < n; end++) {
                        // Considering edges if it does not cicles
                        if (!visited_nodes[end]) {
                            if (matrix[start][end] < best_distance) {
                                best_distance = matrix[start][end];
                                edge = pair(start, end);
                            }
                        }
                    }   
                }
            }
            cout << "Colonia " << edge.first+1 << " a Colonia " << edge.second+1 << " - Dist: " << best_distance << " km\n";
            visited_nodes[edge.second] = true;
        }
    }
    
    public:
    // Funcion de solucion para primer problema | O(n^2)
    void solution (vector<vector<int>> mat) {
        vector<vector<int>> matrix = mat;                       // O(1)
        int n = matrix.size();                                  // O(1)
        vector<bool> visited_nodes = vector<bool>(n, false);    // O(1)
        cout << "La conexion optima de la red es la siguiente:" << "\n";
        prim_algo(matrix, n, 0, visited_nodes);                 // O(n^2)
    }
};

/**
 * @brief Punto 2 - Ruta optima de visita
 * Se uso [...]
 */

/**
 * @brief Punto 3 - Flujo maximo de informacion
 * Se uso [...]
 */

/**
 * @brief Punto 4 - Nueva contratación optima
 * Se uso [...]
 */

int main(int argc, char const *argv[])
{
    cout << "¿Cuantas colonias hay?" << "\n";
    int n;   // Numero de colonias
    cout << "N: "; cin >> n; cout << "\n"; 

    vector<vector<int>> adyacencia_colonias = vector<vector<int>>(n, vector<int>(n));

    for (int col = 0; col < n; col++) {
        cout << "Introduzca adyacencias de colonia " << col + 1 << ": ";
        for (int i = 0; i < n; i++) {
            // TODO: Verificaciones de inputs
            int dist;
            cin >> dist;
            adyacencia_colonias[col][i] = dist;
        }
    }

    cout << "\n" << "PROBLEMA 1" << "\n";
    Solution_1 result; result.solution(adyacencia_colonias);

    return 0;
}
