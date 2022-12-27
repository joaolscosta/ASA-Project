#include <iostream>
#include <algorithm>  

using namespace std;

struct edge {
    int vertice_1;
    int vertice_2;
    int weight;
};

bool comp(edge edge_1, edge edge_2) {
    if(edge_1.weight > edge_2.weight) {
        return true;
    }
    return false;
}

int search_free(int vertice, int parent[]) {
    if(parent[vertice] == -1) {
        return vertice;
    }
    return parent[vertice] = search_free(parent[vertice], parent);
}

int main() {

    int vertices = 0, edges = 0;
    int vertice_1 = 0, vertice_2 = 0;
    int max_trade = 0;

    cin >> vertices;
    cin >> edges;

    edge edges_array[edges];
    int parent[vertices + 1];

    for(int i = 1; i <= vertices; i++) {
        parent[i] = -1;
    }

    for (int i = 0; i < edges; i++) { 
        cin >> edges_array[i].vertice_1 >> edges_array[i].vertice_2 >> edges_array[i].weight;
    }

    sort(edges_array, edges_array + edges, comp);

    for (int i = 0; i < edges; i++) { 

        vertice_1 = search_free(edges_array[i].vertice_1, parent);
        vertice_2 = search_free(edges_array[i].vertice_2, parent);

        if(vertice_1 != vertice_2) {
            max_trade += edges_array[i].weight;
            parent[vertice_1] = vertice_2;
        }
    }

    cout << max_trade << endl;
    return 0;
}