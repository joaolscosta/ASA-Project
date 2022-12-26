#include <iostream>
#include <algorithm>  

using namespace std;

struct edge {
    int vertice1;
    int vertice2;
    int w;
};


bool comp(edge a, edge b) {
    if(a.w > b.w) {
        return true;
    }

    return false;
}

int find(int vertice, int par[]) {
    if(par[vertice] == -1) {
        return vertice;
    }
    return par[vertice] = find(par[vertice], par);
}



int main()
{

    int vertices = 0, edges = 0;

    cin >> vertices;
    cin >> edges;

    edge ar[edges];
    int par[vertices +1];

    for(int i = 1; i <= vertices; i++) {
        par[i] = -1;
    }

    int vertice1 = 0, vertice2 = 0;
    for (int i = 0; i < edges; i++) { 

        cin >> ar[i].vertice1 >> ar[i].vertice2 >> ar[i].w;
    }

    int sum = 0;
    sort(ar, ar + edges, comp);

    for (int i = 0; i < edges; i++) { 

        vertice1 = find(ar[i].vertice1, par);
        vertice2 = find(ar[i].vertice2, par);

        if(vertice1 != vertice2) {
            sum += ar[i].w;
            par[vertice1] = vertice2;
        }
    }
    cout << sum << endl;
    return 0;
}