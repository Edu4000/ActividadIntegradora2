#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfs(vector<vector<double>> &residualGraph, double source, double sink, vector<double> &parent){
    vector<bool> visited(residualGraph.size(), false);
    queue<double> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while(!q.empty()){
        double currentNode = q.front();
        q.pop();

        for(int i = 0; i < residualGraph.size(); i++){
            if(visited[i] == false && residualGraph[currentNode][i] > 0){
                q.push(i);
                parent[i] = currentNode;
                visited[i] = true;
            }
        }
    }

    return (visited[sink] == true);
}

// In a adjacency matrix, check if there are negative values. If there are turn them to cero and add the value to its mirror as abs(value)
vector<vector<double>> treatGraph(vector<vector<double>> graph){
    vector<vector<double>> newGraph = graph;
    for(int i = 0; i < graph.size(); i++){
        for(int j = 0; j < graph.size(); j++){
            if(graph[i][j] < 0){
                newGraph[i][j] = 0;
                newGraph[j][i] += abs(graph[i][j]);
            }
        }
    }
    return newGraph;

}


double fordFulkerson(vector<vector<double>> graph, double origen, double destino){

    graph = treatGraph(graph);

    double n = graph.size();
    vector<vector<double>> residualGraph(n, vector<double>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            residualGraph[i][j] = graph[i][j];
        }
    }

    vector<double> parent(n, -1);
    double maxFlow = 0;

    while(bfs(residualGraph, origen, destino, parent)){
        double pathFlow = INT_MAX;
        for(int v = destino; v != origen; v = parent[v]){
            double u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for(int v = destino; v != origen; v = parent[v]){
            double u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}