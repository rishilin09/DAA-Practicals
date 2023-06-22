#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Node{
public:
	int data;
	vector<Node*> neighbours;
	string colorNode;
	Node(int ele){
		this->data = ele;
		this->colorNode = "";
	}
};

class Graph{

    private:
        char choice;
        int numNodes;
        vector<Node*> nodes;
        vector<string> colors;
        map<Node*, vector<Node*> > adjacencyList;

    public:
        Graph(int numNodes, vector<string> colors) {
            for (int i = 1; i <= numNodes; i++) {
                Node* node = new Node(i);
                nodes.push_back(node);
            }
            this->colors = colors;
        }

        void addEdge(int from, int to){

            Node* fromNode = nodes[from];
            Node* toNode = nodes[to];

            fromNode->neighbours.push_back(toNode);
            toNode->neighbours.push_back(fromNode);

            adjacencyList[fromNode].push_back(toNode);
            adjacencyList[toNode].push_back(fromNode);

        }

        void graphBuilder(int noNodes){

            this->numNodes = noNodes;
            for(int i = 0; i < numNodes; i++){
                for (int j = i+1; j < noNodes; j++){
                    cout<<endl<<"Is there a edge between "<<i+1<<" and "<<j+1<<" (Y/N): ";
                    cin>>choice;
                    if(choice == 'Y' || choice == 'y'){
                        addEdge(i,j);
                    }
                }
            }
        }

        void displayGraph(){
            cout<<endl<<"\nThe Adjacency List is: \n"<<endl;
            for (map<Node*, vector<Node*> >::iterator it=adjacencyList.begin(); it!=adjacencyList.end(); it++){
                int size = it->second.size();
                cout<<"\nFor "<<it->first->data<<" node:";
                cout<<endl<<it->first->data<<"-->";
                for (int j=0; j < size; j++){
                    if (j == size-1){
                        cout<<it->second[j]->data;
                    }
                    else{
                        cout<<it->second[j]->data<<"-->";    
                    }
                }
                cout<<endl;
            }
        }

        bool isValidColor(Node* node,string color){
            for(vector<Node*>::iterator neighbour = node->neighbours.begin(); neighbour != node->neighbours.end(); neighbour++){
                if((*neighbour)->colorNode == color){
                    return false;
                }
            }
            return true;
        }

        bool colorGraph(){
            for(vector<Node*>::iterator node = nodes.begin(); node!=nodes.end(); node++){
                for (vector<string>::iterator color = colors.begin(); color != colors.end(); color++){
                    if(isValidColor(*node,*color)){
                        (*node)->colorNode = *color;
                        break;
                    }
                }
                if ((*node)->colorNode == ""){
                    return false;
                }
            }
            return true;
        }

        void printColorsNode(){
            cout<<endl<<"\nThe Colors of the nodes is: \n"<<endl;
            for (vector<Node*>::iterator node = nodes.begin(); node != nodes.end(); node++){
                cout<<"Color of Node "<<(*node)->data<<" is: "<<(*node)->colorNode<<endl<<"\n";
            }
        }
};

int main(){
	int numNodes, numEdges;
    cout << "Enter the number of nodes in the graph: ";
    cin >> numNodes;
    vector<string> colors;
    int numColors;
    cout << endl << "\nEnter the number of colors: ";
    cin >> numColors;
    cout<< endl;
    for (int i = 1; i <= numColors; i++) {
        string color;
        cout << "\nEnter color " << i << ": ";
        cin >> color;
        colors.push_back(color);
    }
	Graph G(numNodes,colors);
	G.graphBuilder(numNodes);
	G.displayGraph();
	if (G.colorGraph()) {
        G.printColorsNode();
    } else {
        cout << endl << "Failed to color the graph.\n";
    }
	return 0;
}
