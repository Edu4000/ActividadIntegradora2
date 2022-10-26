#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;


int salesman(vector<vector<int>> graph, int s){

    int n = graph.size();
    vector<int> vertex, mejorCamino;

    for (int i = 0; i < n; i++)
        if (i != s)
            vertex.push_back(i);

    int costo = INT_MAX;

    while(next_permutation(vertex.begin(), vertex.end())){

        int currLength = 0;

        int value = s;
        for(int i = 0; i < vertex.size(); i++){
            currLength += graph[value][vertex[i]];
            value = vertex[i];
        }

        currLength += graph[value][s];

        if(costo > currLength){
            costo = currLength;
            mejorCamino.clear();

            for(int i = 0; i < vertex.size(); i++){
                mejorCamino.push_back(vertex[i]);
            }
        }
    }
    

    cout << "Shortest path: " << s << " ---> ";
    
    string delim = "";
    for(int i = 0; i < mejorCamino.size(); i++){
        cout << delim << mejorCamino[i];
        delim = " ---> ";
    }

    cout << " ---> " << s << endl;

    cout << endl;

    return costo;
}
