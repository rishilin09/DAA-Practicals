#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Node{
public:
    int nodeVal;
    vector<Node*> neighbours;
    Node(int ele){
        this->nodeVal = ele;
    }
};

class Edge{
public:
    Node* from;
    Node* to;
    int weight;
    Edge(Node* f, Node* t, int w){
        from = f;
        to = t;
        weight = w;
    }
};

class CompareEdges {
public:
    bool operator() (const Edge* a, const Edge* b) const {
        return a->weight > b->weight;
    }
};

class Graph{
private:
    int numNodes,weight;
    char choice;
    vector<Node*> nodes;
    /*
	The first argument specifies the type of the elements in the queue, which is Edge* in this case.
	The second argument specifies the container type used to store the elements.
		Here, we are using a vector to store the edges.
	The third argument is the comparison function used to order the elements in the queue.
		Here, we are passing an instance of the CompareEdges class as the comparison function.
	*/
    priority_queue<Edge*, vector<Edge*>, CompareEdges> pq;
    vector<set<int> > sets;
    map<Node*, vector<Node*> > adjacencyList;

public:
    Graph(int numN) {
    	numNodes = numN;
        for (int i = 1; i <= numNodes; i++) {
            Node* node = new Node(i);
            nodes.push_back(node);
            set<int> s;
            s.insert(i);
            sets.push_back(s);
        }
    }

    void addEdge(int from, int to, int weight){
        Node* fromNode = nodes[from];
        Node* toNode = nodes[to];

        fromNode->neighbours.push_back(toNode);
        toNode->neighbours.push_back(fromNode);
			
		adjacencyList[fromNode].push_back(toNode);
        adjacencyList[toNode].push_back(fromNode);
		
        Edge* edge = new Edge(fromNode, toNode, weight);
        pq.push(edge);
    }
    
    void graphBuilder(){
		for(int i = 0; i < numNodes; i++){
		    for (int j = i+1; j < numNodes; j++){
		        cout<<endl<<"Is there a edge between "<<i+1<<" and "<<j+1<<" (Y/N): ";
		        cin>>choice;
		        if(choice == 'Y' || choice == 'y'){
		        	cout<<endl<<"\nEnter the weight for the edge: ";
					cin>>weight;
		            addEdge(i,j,weight);
		        }
		    }
		}
	}
	
    void displayGraph(){
	    cout<<endl<<"\nThe Adjacency List is: \n"<<endl;
	    for (map<Node*, vector<Node*> >::iterator it=adjacencyList.begin(); it!=adjacencyList.end(); it++){
	        int size = it->second.size();
	        cout<<"\nFor "<<it->first->nodeVal<<" node:";
	        cout<<endl<<it->first->nodeVal<<"-->";
	        for (int j=0; j < size; j++){
	            if (j == size-1){
	                cout<<it->second[j]->nodeVal;
	            }
	            else{
	                cout<<it->second[j]->nodeVal<<"-->";    
	            }
	        }
	        cout<<endl;
	    }
	}

	
	/*	The find function searches for the set that contains a given node 
		value and returns the index of that set. 
	*/
    int find(int nodeVal){
        for (int i=0; i<sets.size(); i++){
            set<int>::iterator it = sets[i].find(nodeVal);
            if (it != sets[i].end()){
                return i;
            }
        }
        return -1;
    }
	
	/*
		The Union function merges two sets specified by their indices by inserting all 
		elements from one set into the other and then removing the second set from the vector of sets.
	*/
    void Union(int a, int b){
        sets[a].insert(sets[b].begin(), sets[b].end());
        sets.erase(sets.begin() + b);
    }

    void KruskalMST(){
        vector<Edge*> mst;
        int totalWeight = 0;
        while(!pq.empty()){
            Edge* currEdge = pq.top();
            pq.pop();

            int setA = find(currEdge->from->nodeVal) ;
            int setB = find(currEdge->to->nodeVal) ;
            /*
				If setA and setB's index value are not same that means
				that the nodes are not a part of the same set and can
				be included in the MST. 
			*/
            if (setA != setB){
                mst.push_back(currEdge);
                totalWeight += currEdge->weight;
                Union(setA, setB);
            }
        }

        cout << "\nMinimum Spanning Tree using Kruskal's Algorithm:\n";
        for(vector<Edge*>::iterator it = mst.begin(); it != mst.end(); ++it){
            cout << (*it)->from->nodeVal << " -- " << (*it)->to->nodeVal << " : " << (*it)->weight << endl;
		}
        cout << "Total weight of Tree: " << totalWeight << endl;
    }
};

int main() {
	int numNodes, numEdges;
    cout << "Enter the number of nodes in the graph: ";
    cin >> numNodes;
    Graph G(numNodes);
	G.graphBuilder();
    G.displayGraph();
    G.KruskalMST();
    return 0;
}


