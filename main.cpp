/**
 * @file main.cpp
 * 
 * @author Abraham Chalita Nuñez
 * @author Jesus Daniel Revas Nuño
 * @author Eduardo Angeles Guerrero
 * 
 * @brief Entregable de actividad integradora 2
 * 
 * @version 0.1
 * @date 2022-10-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

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
class Line {
    public:
    bool vertical = false;
    double m, b, x;
    pair<int,int>* left = nullptr;
    pair<int,int>* right = nullptr;

    Line(int m, int b) {
        this->m = m;
        this->b = b;
    }

    Line(double x) {
        vertical = true;
        this->x = x;
    }
};

class Point {
    public:
    double x, y;
    vector<Line*> lineas;
    
    Point(pair<int,int> coord) {
        this->x = coord.first;
        this->y = coord.second;
    }

    void addLine(Line* linea) {
        lineas.push_back(linea);
    }
};

class Solution_4_Voronoi{
    private:

    public:
    void solution (vector<pair<double,double>> coordenadas) {
        // Convirtiendo input a formato de puntos
        vector<Point> puntos;
        for (pair<double,double> coord : coordenadas) {
            puntos.push_back(Point(coord));
        }

        // Obteniendo las lineas de mediatriz entre los puntos
        for (int p1 = 0; p1 < puntos.size()-1; p1++) {
            for (int p2 = p1 + 1; p2 < puntos.size(); p2++) {

                double x_mid = (puntos[p1].x + puntos[p2].x) / 2;
                double y_mid = (puntos[p1].y + puntos[p2].y) / 2;

                double delta_y = puntos[p2].y - puntos[p1].y;
                double delta_x = puntos[p2].x - puntos[p1].x;

                // m = delta_y / delta_x => m_inv = -1/m
                if (delta_y != 0) {
                    double m_inv = -delta_x / delta_y;
                    double b = y_mid - m_inv * x_mid;

                    cout << "Linea entre ";
                    cout << "(" << puntos[p1].x << "," << puntos[p1].y << ")";
                    cout << " y ";
                    cout << "(" << puntos[p2].x << "," << puntos[p2].y << ")";
                    cout << "\n";
                    cout << "y = " << m_inv << "x + " << b << "\n";

                    Line l = Line(m_inv, b);

                    puntos[p1].addLine(&l);
                    puntos[p2].addLine(&l);
                }
                else {
                    cout << "Linea entre " << "\n";
                    cout << "x = " << x_mid << "\n";

                    Line l = Line(x_mid);

                    puntos[p1].addLine(&l);
                    puntos[p2].addLine(&l);
                }
            }
        }

    }    
};

class Solution_4_connection{
    // Given a set of points and a point x, find minimum distance between x and points in the set.
    private:
    public:
        void minDistance(vector<Point> puntos, Point x) {
            double min_dist = INT_MAX;
            Point min_point = puntos[0];
            for (Point p : puntos) {
                double dist = sqrt(pow(p.x - x.x, 2) + pow(p.y - x.y, 2));
                if (dist < min_dist) {
                    min_point = p;
                    min_dist = dist;
                }
            }
            
            // print points and minimum distance
            cout << "El punto (" << x.x << "," << x.y << ") esta a una distancia minima de " << min_dist << " del punto: " << min_point.x << "," << min_point.y << "\n";
        }
};

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

    cout << "\n" << "PROBLEMA 2" << "\n";

    cout << "\n" << "PROBLEMA 3" << "\n";

    cout << "\n" << "PROBLEMA 4 : CERCANIA A CENTRALES ELECTRICAS" << "\n";
    vector<pair<double,double>> coordenadas;
    string input_x, input_y;
    for (int i = 0; i < n; i++) {
        while (true)
        {
            cout << "Coordenada de Central " << i + 1 << " [x y]: ";
            cin >> input_x >> input_y;
            try
            {
                double x = stod(input_x);
                double y = stod(input_y);
                coordenadas.push_back(pair<double,double>(x,y));
                break;
            }
            catch(const std::exception& e)
            {
                cout << "Formato incorrecto. Ingrese un numero valido." << '\n';
                //something went wrong, we reset the buffer's state to good
                cin.clear();
                //and empty it
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
    }

    Solution_4_Voronoi a; a.solution(coordenadas);

    return 0;
}
