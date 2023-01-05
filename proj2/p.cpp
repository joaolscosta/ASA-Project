/* Daniel Nunes e João Costa - 2º Projeto de Analise e Sintese de Algoritmos */
#include <iostream>
#include <algorithm>  
#include <vector>

using namespace std;

struct edge {
    int vertice_1;
    int vertice_2;
    int weight;
};

bool comp(edge edge_1, edge edge_2) { return edge_1.weight > edge_2.weight; }

int search_free(int vertice, vector<int> &parent) { //find
    if(parent[vertice] == -1) {
        return vertice;
    }
    return parent[vertice] = search_free(parent[vertice], parent);
}

int main() {

    int vertices = 0, edges = 0, vertice_1 = 0, vertice_2 = 0, max_trade = 0;

    if(scanf("%d", &vertices) != 1) {exit(1);}
    if(scanf("%d", &edges) != 1) {exit(1);}

    vector<edge> vector_edges;
    vector<int> parent;
    
    for(int i = 1; i <= vertices+1; i++) {
        parent.push_back(-1);
    }
    for (int i = 0; i < edges; i++) { 
        vector_edges.push_back(edge());
        if(scanf("%d %d %d", &vector_edges[i].vertice_1 ,&vector_edges[i].vertice_2, 
           &vector_edges[i].weight)!= 3) {
            exit(1);
        }
    }   

    sort(vector_edges.begin(), vector_edges.end(), comp);

    for (int i = 0; i < edges; i++) {

        vertice_1 = search_free(vector_edges[i].vertice_1, parent);
        vertice_2 = search_free(vector_edges[i].vertice_2, parent);

        if(vertice_1 != vertice_2) {
            max_trade += vector_edges[i].weight;
            parent[vertice_1] = vertice_2; //union
        }
    }

    cout << max_trade << endl;
    return 0;
}