#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <functional>


using namespace std;

struct path{
    int cost;
    vector<int> camino;
};

void printPath(vector<int> mejorCamino, int s, int currLength){
    cout << "Shortest path: " << s << " ---> ";

    string delim = "";
    for(int i = 0; i < mejorCamino.size(); i++){
        cout << delim << mejorCamino[i];
        delim = " ---> ";
    }

    cout << " ---> " << s << endl;
    cout << "Cost: " << currLength << endl;
    cout << endl;
}

bool checkIfvalidPath(vector<int> camino, vector<vector<int>> graph, int s, int currLength){



    if(graph[s][camino[0]] == 0){
        return false;
    }

    for(int c = 0; c < camino.size() -1 ; c++){
        if(graph[camino[c]][camino[c + 1]] == 0){
            return false;
        }
    }

    if(graph[camino[camino.size() - 1]][0] == 0){
        return false;
    }

    if(currLength < 0){
        return false;
    }

    return true;
    
}


void salesman(vector<vector<int>> graph, int s){

    int n = graph.size();
    vector<int> vertex, mejorCamino, selected;
    vector<path> paths;

    // Add vertices to vector and validate conexion
    for (int i = 0; i < n; i++){
        if(i != s){
            vertex.push_back(i);
        }
    }
    
    int costo = INT_MAX;

    while(next_permutation(vertex.begin(), vertex.end())){

        mejorCamino.clear();

        int currLength = 0;

        int value = s;
        for(int i = 0; i < vertex.size(); i++){
           // validate conectivity between vertices
            if(graph[value][vertex[i]] != 0){
                currLength += graph[value][vertex[i]];
                value = vertex[i];
            }
            else{
                currLength = INT_MAX;
                break;
            }
        }

        currLength += graph[value][s];

         for(int i = 0; i < vertex.size(); i++){
            mejorCamino.push_back(vertex[i]);
        }

        paths.push_back({currLength, mejorCamino});

    }

    //cout << paths.size() << endl;

    if(paths.size() == 0){
        cout << "No valid path found" << endl;
        return;
    }

    // Find path with lowest cost
    for(int i = 0; i < paths.size(); i++){
        if(paths[i].cost < costo && checkIfvalidPath(paths[i].camino, graph, s, paths[i].cost)){
            costo = paths[i].cost;
            mejorCamino = paths[i].camino;
        }
    }

    printPath(mejorCamino, s, costo);

}
