/**
 * @file main.cpp
 * 
 * @author Abraham Chalita Nuñez        A0165
 * @author Jesus Daniel Revas Nuño      A0165
 * @author Eduardo Angeles Guerrero     A0165
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
#include <fstream>
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
#include "dijkstra.h"

/**
 * @brief Punto 2 - Ruta optima de visita
 * Se uso [...]
 */
 #include "travelSM.h"

/**
 * @brief Punto 3 - Flujo maximo de informacion
 * Se uso [...]
 */
#include "flow.h"

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
    
    Point(pair<double,double> coord) {
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
            int num = 1;
            int min_num = 1;
            for (Point p : puntos) {
                double dist = sqrt(pow(p.x - x.x, 2) + pow(p.y - x.y, 2));
                if (dist < min_dist) {
                    min_point = p;
                    min_dist = dist;
                    min_num = num;
                }
                num++;
            }
            
            // print points and minimum distance
            cout << " (" << x.x << "," << x.y << ") esta mas cerca de la Central " << min_num << " (" << min_point.x  << "," << min_point.y << ")" << " a una distancia minima de " << min_dist << " km\n";
        }
};

int get_int (string message)
{
    double res;
    while (true)
    {
        cout << message << ": ";
        try
        {
            cin >> res;
            if (res <= 0) {
                cout << "\nERROR: Introduzca un numero positivo." << "\n";
            }
        }
        catch(const std::exception& e)
        {
            cout << "\nERROR: Introduzca un numero vali." << "\n";
        }
    }
}

int main(int argc, char const *argv[])
{
    cout << "###########################\n";
    cout << "# ACTIVIDAD INTEGRADORA 2 #\n";
    cout << "###########################\n\n";

    // Leyendo archivo de entrada.
    bool correct_file, empty_file, proceed_1, proceed_2, proceed_3;
    ifstream file;
    string current_line;
    try
    {
        file.open("test.txt");
        empty_file = file.peek() == ifstream::traits_type::eof();
        correct_file = true; proceed_1 = true; proceed_2 = true; proceed_3 = true;
    }
    catch(const std::exception& e)
    {
        correct_file = false; proceed_1 = false; proceed_2 = false; proceed_3 = false;
        cout << "\nERROR: El archivo test.txt no se reconoce en el directorio actual.\n\n";
    }

    if (empty_file)
    {
        correct_file = false; proceed_1 = false; proceed_2 = false; proceed_3 = false;
        cout << "\nERROR: El archivo test.txt esta vacio.\n\n";
    }

    int n;
    if (correct_file)
    {
        try
        {
            getline(file, current_line);
            n = stoi(current_line);
            cout << "No. Lineas: " << n << "\n";
        }
        catch(const std::exception& e)
        {
            correct_file = false; proceed_1 = false; proceed_2 = false; proceed_3 = false;
            cout << "\nERROR: La primera linea del archivo no pudo convertirse en un numero entero.\n";
            cout << "       Por favor, verifique el archivo de entrada.\n\n";
        }
    }

    vector<vector<double>> adyacencia_colonias = vector<vector<double>>(n, vector<double>(n));
    cout << "LEYENDO MATRIZ DE ADYACENCIA\n\n";
    if (correct_file) {
        string input;
        bool proceed = true;
        try
        {
            for (int i = 0; i < n; i++)
            {
                if (file.peek() == ifstream::traits_type::eof()) throw exception();
                getline(file, current_line);
                if (!proceed) break;
                for (int j = 0; j < n; j++)
                {
                    file >> input;
                    cout << input << " ";
                    try
                    {
                        adyacencia_colonias[i][j] = stod(input);
                        if (i == j && adyacencia_colonias[i][j] != 0) {
                            cout << "\nERROR: En la matriz de adyacencia un nodo no puede conectarse con si mismo.\n";
                            cout << "       El valor debe ser 0 en la diagonal. Por favor verifique el archivo.\n\n";
                            correct_file = false; proceed = false; proceed_1 = false; proceed_2 = false; proceed_3 = false;
                            break;
                        }
                        else if (adyacencia_colonias[i][j] < 0) {
                            cout << "\nERROR: Un valor en la matriz de adyacencia es negativo.\n";
                            cout << "       Por favor verifique el archivo.\n\n";
                            correct_file = false; proceed = false; proceed_1 = false; proceed_2 = false; proceed_3 = false;
                            break;
                        }
                    }
                    catch(const std::exception& e)
                    {
                        cout << "\nERROR: Un valor en la matriz de adyacencia no se puede interpretar como numero entero.\n\n";
                        correct_file = false; proceed = false; proceed_1 = false; proceed_2 = false; proceed_3 = false;
                        break;
                    }
                }
                cout << "\n";
            }
        }
        catch(const std::exception& e)
        {
            cout << "\nERROR: El archivo se acabo antes de realizar las lecturas.\n";
            cout << "       Por favor asegurese que el archivo este completo.\n\n";
            correct_file = false; proceed_1 = false; proceed_2 = false; proceed_3 = false;
        }
    }
    
    vector<vector<double>> flujo_colonias = vector<vector<double>>(n, vector<double>(n));
    cout << "LEYENDO MATRIZ DE FLUJO\n\n";
    if (correct_file) {
        string input;
        bool proceed = true;
        try
        {
            for (int i = 0; i < n; i++)
            {
                if (file.peek() == ifstream::traits_type::eof()) throw exception();
                getline(file, current_line);
                if (!proceed) break;
                for (int j = 0; j < n; j++)
                {
                    file >> input;
                    cout << input << " ";
                    try
                    {
                        flujo_colonias[i][j] = stod(input);
                        if (i == j && flujo_colonias[i][j] != 0) {
                            cout << "\nERROR: En la matriz de flujo un nodo no puede tener flujo a si mismo.\n";
                            cout << "       El valor debe ser 0 en la diagonal. Por favor verifique el archivo.\n\n";
                            correct_file = false; proceed = false; proceed_3 = false;
                            break;
                        }
                        else if (flujo_colonias[i][j] != 0 && adyacencia_colonias[i][j] == 0) {
                            cout << "\nERROR: No puede existir flujo cuando no estan conectadas las colonias.\n";
                            cout << "       Por favor verifique el archivo.\n\n";
                            correct_file = false; proceed = false; proceed_3 = false;
                            break;
                        }
                    }
                    catch(const std::exception& e)
                    {
                        cout << "\nERROR: Un valor en la matriz de adyacencia no se puede interpretar como numero entero.\n\n";
                        correct_file = false; proceed = false; proceed_3 = false;
                        break;
                    }
                }
                cout << "\n";
            }
        }
        catch(const std::exception& e)
        {
            cout << "\nERROR: El archivo se acabo antes de realizar las lecturas.\n";
            cout << "       Por favor asegurese que el archivo este completo.\n\n";
            correct_file = false; proceed_3 = false;
        }
    }

    cout << "\n";
    cout << "#####################################\n";
    cout << "# PROBLEMA 1: CONEXIONES EFICIENTES #\n";
    cout << "#####################################\n\n";
    if (proceed_1)
    {
        dijkstra_result(adyacencia_colonias);
    }
    else
    {
        cout << "No se puede realizar el problema 1 por falla de input\n";
    }

    cout << "\n";
    cout << "################################\n";
    cout << "# PROBLEMA 2: VIAJERO VENDEDOR #\n";
    cout << "################################\n\n";

    if (proceed_2)
    {
        salesman(adyacencia_colonias, 0);
    }
    else
    {
        cout << "No se puede realizar el problema 2 por falla de input\n";
    }

    cout << "\n";
    cout << "###########################################\n";
    cout << "# PROBLEMA 3: MAXIMO FLUJO DE INFORMACION #\n";
    cout << "###########################################\n\n";

    if (proceed_3)
    {
        cout << "Resultado\n";
        cout << "El flujo máximo posible entre inicio y fin es: " << fordFulkerson(flujo_colonias, 0, flujo_colonias.size()-1) << endl;

    }
    else
    {
        cout << "No se puede realizar el problema 3 por falla de input\n";
    }

    cout << "\n";
    cout << "################################################\n";
    cout << "# PROBLEMA 4 : CERCANIA A CENTRALES ELECTRICAS #\n";
    cout << "################################################\n\n";

    int n_centrales, n_nuevas_contrataciones;
    vector<Point> centrales, contrataciones;
    double x, y;
    string input;

    while (true)
    {
        try
        {
            cout << "¿Cuantas centrales elécticas existen? "; 
            cin >> input;
            n_centrales = stod(input);
            if (n_centrales <= 0) 
            {
                cout << "\nERROR: Introduzca un numero mayor a cero." << "\n\n";
            }
            else 
            {
                break;
            }
        }
        catch(const std::exception& e)
        {
            cout << "\nERROR: Error en conversion de entrada a input. Por favor introduzca un numero." << "\n\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    for (int i = 0; i < n_centrales; i++)
    {
        while (true)
        {
            cout << "Coordenada de Central " << i + 1 << " [x y]: ";
            try
            {
                cin >> input;
                x = stod(input);
                cin >> input;
                y = stod(input);
                centrales.push_back(Point(pair<double,double>(x,y)));
                break;
            }
            catch(const std::exception& e)
            {
                cout << "Formato incorrecto. Ingrese un par de numeros validos." << '\n';
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }

    while (true)
    {
        try
        {
            cout << "¿Cuantas nuevas contrataciones quiere? "; 
            cin >> input;
            n_nuevas_contrataciones = stod(input);
            if (n_nuevas_contrataciones <= 0)
            {
                cout << "\nERROR: Introduzca un numero mayor a cero." << "\n\n";
            }
            else 
            {
                break;
            }
        }
        catch(const std::exception& e)
        {
            cout << "\nERROR: Error en conversion de entrada a input. Por favor introduzca un numero" << "\n\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    for (int i = 0; i < n_nuevas_contrataciones; i++)
    {
        while (true)
        {
            cout << "Coordenada de Contratacion " << i + 1 << " [x y]: ";
            try
            {
                cin >> input;
                x = stod(input);
                cin >> input;
                y = stod(input);
                contrataciones.push_back(Point(pair<double,double>(x,y)));
                break;
            }
            catch(const std::exception& e)
            {
                cout << "Formato incorrecto. Ingrese un par de numeros validos." << '\n';
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }

    // Solution_4_Voronoi a; a.solution(coordenadas);
    Solution_4_connection b;
    int num = 1;
    for (Point nuevo : contrataciones)
    {
        cout << "Contratacion " << num ;
        b.minDistance(centrales, nuevo); cout << "\n";
        num++;
    }

    return 0;
}
