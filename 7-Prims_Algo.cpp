#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

class Solution {
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<pair<int, int> > adj[], vector<pair<int, int> >& mstEdges) {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        vector<int> vis(V, 0);
        // {wt, node}
        pq.push(make_pair(0, 0));
        int sum = 0;
        while (!pq.empty()) {
            pair<int, int> it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node] == 1)
                continue;
            // add it to the mst
            vis[node] = 1;
            sum += wt;
            for (int i = 0; i < adj[node].size(); i++) {
                int adjNode = adj[node][i].first;
                int edW = adj[node][i].second;
                if (!vis[adjNode]) {
                    pq.push(make_pair(edW, adjNode));
                    mstEdges.push_back(make_pair(node, adjNode));
                }
            }
        }
        return sum;
    }
};

int main() {
    int V = 5;
    vector<vector<int> > edges;
    edges.push_back(vector<int>(3, 0));
    edges[0][0] = 0;
    edges[0][1] = 1;
    edges[0][2] = 2;
    edges.push_back(vector<int>(3, 0));
    edges[1][0] = 0;
    edges[1][1] = 2;
    edges[1][2] = 1;
    edges.push_back(vector<int>(3, 0));
    edges[2][0] = 1;
    edges[2][1] = 2;
    edges[2][2] = 1;
    edges.push_back(vector<int>(3, 0));
    edges[3][0] = 2;
    edges[3][1] = 3;
    edges[3][2] = 2;
    edges.push_back(vector<int>(3, 0));
    edges[4][0] = 3;
    edges[4][1] = 4;
    edges[4][2] = 1;
    edges.push_back(vector<int>(3, 0));
    edges[5][0] = 4;
    edges[5][1] = 2;
    edges[5][2] = 2;

    vector<pair<int, int> > adj[V];
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
    }

    Solution obj;
    vector<pair<int, int> > mstEdges;
    int sum = obj.spanningTree(V, adj, mstEdges);
    cout << "The sum of all the edge weights: " << sum << endl;

    cout << "Minimum Spanning Tree Edges:\n";
    for (int i = 0; i < mstEdges.size(); i++) {
        cout << mstEdges[i].first << " - " << mstEdges[i].second << endl;
    }

    return 0;
}


