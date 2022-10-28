#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfs(vector<vector<int>> &residualGraph, int source, int sink, vector<int> &parent){
    vector<bool> visited(residualGraph.size(), false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while(!q.empty()){
        int currentNode = q.front();
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
vector<vector<int>> treatGraph(vector<vector<int>> graph){
    vector<vector<int>> newGraph = graph;
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


int fordFulkerson(vector<vector<int>> graph, int origen, int destino){

    graph = treatGraph(graph);

    int n = graph.size();
    vector<vector<int>> residualGraph(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            residualGraph[i][j] = graph[i][j];
        }
    }

    vector<int> parent(n, -1);
    int maxFlow = 0;

    while(bfs(residualGraph, origen, destino, parent)){
        int pathFlow = INT_MAX;
        for(int v = destino; v != origen; v = parent[v]){
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for(int v = destino; v != origen; v = parent[v]){
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
