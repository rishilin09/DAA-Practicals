#include <iostream>
#include <climits> // for INT_MAX
#include <vector>
using namespace std;

class Graph
{
private:
	int **adjMatrix;
	int numVertices;

public:
	// Initialize the matrix to zero
	Graph(int vertices)
	{
		numVertices = vertices;

		// Allocate memory for the adjacency matrix
		adjMatrix = new int *[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			adjMatrix[i] = new int[numVertices];
			for (int j = 0; j < numVertices; j++)
				adjMatrix[i][j] = 0;
		}
	}

	// Add edges
	void addEdge(int i, int j, int weight)
	{
		adjMatrix[i][j] = weight;
		adjMatrix[j][i] = weight;
	}

	// Print the matrix
	void printAdjMatrix(int **adjMatrix)
	{
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
			{
				cout << adjMatrix[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}

	int minDistance(int dist[], bool visited[])
	{
		int min = INT_MAX;
		int min_index = -1;
		for (int v = 0; v < numVertices; v++)
		{
			if (!visited[v] && dist[v] <= min)
			{
				min = dist[v];
				min_index = v;
			}
		}
		return min_index;
	}

	// Dijkstra's Algorithm
	int dijkstra(int src, int dest, vector<int> &path)
	{
		int dist[numVertices];
		bool visited[numVertices];
		int prev[numVertices];

		for (int i = 0; i < numVertices; i++)
		{
			dist[i] = INT_MAX;
			visited[i] = false;
			prev[i] = -1;
		}

		dist[src] = 0;

		for (int count = 0; count < numVertices - 1; count++)
		{
			int u = minDistance(dist, visited);
			visited[u] = true;

			for (int v = 0; v < numVertices; v++)
			{
				if (!visited[v] && adjMatrix[u][v] != 0 && dist[u] != INT_MAX &&
					dist[u] + adjMatrix[u][v] < dist[v])
				{
					dist[v] = dist[u] + adjMatrix[u][v];
					prev[v] = u;
				}
			}
			//        	cout << endl << "\nFor Iteration " << count + 1 << endl;
			//        	printAdjMatrix(adjMatrix);
		}

		int current = dest;
		while (current != -1)
		{
			path.insert(path.begin(), current);
			current = prev[current];
		}

		return dist[dest];
	}
};

int main()
{
	int numNodes;
	cout << "Enter the number of nodes: ";
	cin >> numNodes;

	Graph g(numNodes);

	// Take input from the user to create the graph
	for (int i = 0; i < numNodes; i++)
	{
		for (int j = i + 1; j < numNodes; j++)
		{
			int weight;
			cout << "\nEnter the weight between vertex " << i + 1 << " and " << j + 1 << ": ";
			cin >> weight;
			g.addEdge(i, j, weight);
		}
	}

	cout << endl
		 << "\nAdjacency matrix after each step:\n";
	int src, dest;
	cout << "Enter the source vertex: ";
	cin >> src;
	cout << "Enter the destination vertex: ";
	cin >> dest;

	vector<int> path;
	int dist = g.dijkstra(src - 1, dest - 1, path);

	cout << endl
		 << "\nShortest distance from source to destination: " << dist << "\n";

	cout << "Shortest path: ";
	for (int i = 0; i < path.size(); i++)
	{
		cout << path[i] + 1;
		if (i != path.size() - 1)
		{
			cout << " -> ";
		}
	}
	cout << "\n";

	return 0;
}
