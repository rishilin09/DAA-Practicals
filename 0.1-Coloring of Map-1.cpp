#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

class Node{
public:
	int data;
	Node *nextN;
	string colorNode;
	Node(int ele){
		data = ele;
		nextN = NULL;
		colorNode = "";
	}
};

class AdjacencyList{
	
	private:
		Node *newNode,*end,*start; 
		vector<Node*> nodes;
		vector<string> colors;
		int noNodes, noColors;
		char choice;
		string color;
	
	public:
		
		AdjacencyList(){
			newNode = NULL;
			end = NULL;
			start = NULL;
		}
		
		void inputColors(){
			cout<<endl<<"\nNumber of colors in the pallete: ";
			cin>>noColors;
			for(int i=0; i<noColors; i++){
				cout<<"Enter the "<<i+1<<" color: ";
				cin>>color;
				colors.push_back(color);
			}
		}
		
		void builder(){
			
			cout<<"Enter the number of nodes for the graph: ";
			cin>>noNodes;
			for(int i = 0; i < noNodes; i++){
				Node* newNode = new Node(i+1);
				nodes.push_back(newNode);
				end = newNode;
				start = newNode;
				for (int j = 0; j < noNodes; j++){
					if (i == j){
						continue;
					}
					cout<<endl<<"Is there a edge between "<<i+1<<" and "<<j+1<<" (Y/N): ";
						cin>>choice;
					if(choice == 'Y'){
						Node* newNode = new Node(j+1);
						end->nextN = newNode;
						end = newNode;
					}
				}
			}
		}
		
		void displayAL(){
			cout<<endl<<"\nThe Adjacency List is: \n"<<endl;
			for (int i=0; i < noNodes; i++){
				Node* newNode = nodes[i];
				while(newNode != NULL){
					if(newNode->nextN == NULL){
						cout<<newNode->data;
						break;
					}
					else{
						cout<<newNode->data<<"-->";
						newNode = newNode->nextN;
					}
				}
				cout<<endl;
			}
		}
		
		void colorBuilder(){
			int idx = 0;
			inputColors();
			vector<vector<int> > colorsMatrix( nodes.size() , vector<int> (colors.size(), 0));
			for(int i = 0; i < nodes.size(); i++){
				int k = 0;
				Node* newNode = nodes[i];
				Node* temp = newNode->nextN;
				while(temp != NULL){
					idx = temp->data;
					if (colorsMatrix[idx - 1][k] == 1){
						k += 1;
					}
					temp = temp->nextN;
				}
				newNode->colorNode = colors[k];
				colorsMatrix[newNode->data - 1][k] = colors[k];
			}	
		}
		
		void displayColorsNode(){
			cout<<endl<<"\nThe Colors of the nodes is: \n"<<endl;
			for (int i=0; i < noNodes; i++){
				Node* newNode = nodes[i];
				cout<<"Color of Node "<<newNode->data<<" is: "<<newNode->colorNode<<endl<<"\n";
			}
		}
};


int main(){
	AdjacencyList aL;
	aL.builder();
	aL.displayAL();
	aL.colorBuilder();
	aL.displayColorsNode();
	return 0;
}
