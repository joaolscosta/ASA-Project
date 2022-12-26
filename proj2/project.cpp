#include <iostream>
#include <unordered_map>
#include <vector>
#include <string> 

using namespace std;



int main()
{

    int vertices = 0, edges = 0;

    cin >> vertices;
    cin >> edges;


    int graph[vertices][vertices];
    int vertice1 = 0, vertice2 = 0, w = 0;

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < edges; i++) {

        cin >> vertice1 >> vertice2 >> w;
        graph[vertice1-1][vertice2-1] = w;
        graph[vertice2-1][vertice1-1] = w;


    }

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout<< graph[i][j] << ", ";
        }
        cout << endl;
    }

    int parent[vertices];
    int key[vertices];
    bool mstSet[vertices];
    for(int i = 0; i < vertices; i++) {
        key[i] = 0; mstSet[i] = false;
    }
    key[0] = 1;
    parent[0] = -1;

    for(int count = 0; count < vertices-1; count++) {
        int u = 0;
        int max = 0;
        for(int i = 0; i < vertices; i++) {
            for(int v = 0; v < vertices; v++) {
                if(mstSet[i] == false && graph[i][v] > max) {
                    max = graph[i][v], u = i; 
                }
            }
        }
        cout<< u << endl;
        mstSet[u] = true;
        for(int v = 0; v < vertices; v++) {
            if(graph[u][v] && mstSet[v] == false && graph[u][v] > key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
        for(int i = 1; i < vertices; i++) {
            cout << parent[i] << "-" <<i << "     "<< graph[i][parent[i]] << endl;
        }
    }

    return 0;
}