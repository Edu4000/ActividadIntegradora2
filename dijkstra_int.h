#include <iostream>
#include <vector>
using namespace std;

#include <iostream>
#include <vector>
using namespace std;

struct node {
    vector<pair<int,node*>> edges;
    string name;
    bool visited;
    node* prev;
    int weight = 0;

    void goes_to(int dist, node b) {
        edges.push_back(pair<int,node*>(dist, &b));
    }
};

void result (node end) {
    string res;
    node traverse = end;
    while (traverse.prev != nullptr)
    {
        res += traverse.name;
        res += " - ";
        traverse = *traverse.prev;
    }
    res += traverse.name;
    cout << traverse.name << "\n";
}

void add_edge (node &a, node &b, int dist) {
    a.edges.push_back(pair<int,node*>(dist, &b));
}

void dijkstra (node* begin, node* end) { //O(nlog(m)): n is the number of nodes / m is the number of edges
    // Base case: Reaching end node
    if (begin->name == end->name) {
        return;
    }

    vector<node*> candidates;
    for (pair<int,node*> next : begin->edges) {
        if (!next.second->visited) {
            int cumulative_weight = next.first + begin->weight;
            if (next.second->weight == 0) { // Node has not been asinged a weight
                next.second->weight = cumulative_weight;
                next.second->prev = begin;
                candidates.push_back(next.second);
            }
            else { // Node has already a weight
                if (cumulative_weight < next.second->weight) {
                    next.second->weight = cumulative_weight;
                    next.second->prev = begin;
                    candidates.push_back(next.second);
                }
            }
        }
    }
    begin->visited = true;
    for (node* n : candidates) {
        dijkstra(n, end);
    }
}

void dijkstra_result (vector<vector<int>> adyacency_matrix) {
    int length = adyacency_matrix.size();
    for (int node_begin = 0; node_begin < length; node_begin++) {
        for (int node_end = 0; node_end < length; node_end++) {
        
        if (node_begin != node_end) {

        // Creating nodes
        vector<node> test_nodes = vector<node>(length);
        for (int i = 0; i < length; i++) {
            test_nodes[i].name = "" + char(i);
        }
        for (int start = 0; start < length; start++) {
            for (int end = 0; end < length; end++) {
                if (start != end) {
                    if (adyacency_matrix[start][end] > 0) {
                        add_edge(test_nodes[start], test_nodes[end], adyacency_matrix[start][end]);
                    }
                }
            }
        }

        // Calling Dijkstra
        dijkstra(&test_nodes[node_begin], &test_nodes[node_end]);
        cout << "Colonia " << node_begin+1 << " a Colonia " << node_end+1 << " - Dist: ";
        if (test_nodes[node_end].weight == 0) {
            cout << "SIN RESULTADOS" << "\n";
        }
        else {
            cout << test_nodes[node_end].weight << " km\n";
        }

        }

        }
    }
}