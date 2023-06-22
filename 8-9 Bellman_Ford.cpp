#include <iostream>
#include <vector>
using namespace std;

struct node {
    int u;
    int v;
    int wt; 
    node(int first, int second, int weight) {
        u = first;
        v = second;
        wt = weight;
    }
};

void printGraph(const vector<node>& edges) {
    cout << "Graph:\n";
    for(vector<node>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
        cout << it->u << " - " << it->v << " : " << it->wt << endl;
    }
    cout << endl;
}

int main() {
    int N, m;
    cout << "Enter the number of nodes (N): ";
    cin >> N;
    cout << "Enter the number of edges (m): ";
    cin >> m;
    
    vector<node> edges;
    int u, v, wt;
    for (int i = 0; i < m; i++) {
        cout << "Enter the details for edge " << i+1 << ":\n";
        cout << "Source node: ";
        cin >> u;
        cout << "Destination node: ";
        cin >> v;
        cout << "Weight: ";
        cin >> wt;
        edges.push_back(node(u, v, wt));
        cout << endl;
    }

    int src;
    cout << "Enter the source node: ";
    cin >> src;

    int inf = 10000000; 
    vector<int> dist(N, inf); 
    dist[src] = 0; 
    for(int i = 1; i <= N-1; i++) {
        for(vector<node>::iterator it = edges.begin(); it != edges.end(); ++it) {
            if(dist[it->u] + it->wt < dist[it->v]) {
                dist[it->v] = dist[it->u] + it->wt; 
            }
        }
    }

    int fl = 0; 
    for(vector<node>::iterator it = edges.begin(); it != edges.end(); ++it) {
        if(dist[it->u] + it->wt < dist[it->v]) {
            cout << "Graph contains negative weight cycle. Cannot find shortest paths.";
            fl = 1; 
            break; 
        }
    }

    if(!fl) {
        cout << "Shortest Distances from Source (" << src << "):\n";
        for(int i = 0; i < N; i++) {
            cout << "Node " << i << ": " << dist[i] << endl;
        }
        cout << endl;
    }

    printGraph(edges);

    return 0;
}
 
 
/*
Use this input

Enter the number of nodes (N): 6
Enter the number of edges (m): 7
Enter the details for edge 1:
Source node: 0
Destination node: 1
Weight: 5

Enter the details for edge 2:
Source node: 1
Destination node: 2
Weight: -2

Enter the details for edge 3:
Source node: 1
Destination node: 5
Weight: -3

Enter the details for edge 4:
Source node: 2
Destination node: 4
Weight: 3

Enter the details for edge 5:
Source node: 3
Destination node: 2
Weight: 6

Enter the details for edge 6:
Source node: 3
Destination node: 4
Weight: -2

Enter the details for edge 7:
Source node: 5
Destination node: 3
Weight: 1
*/
