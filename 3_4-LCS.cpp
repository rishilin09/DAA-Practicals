#include<iostream>
#include<iomanip>
#include<stdio.h>
#include <sstream> 
#include<vector>
#include<string>

using namespace std;

 /*
 	This class will be helpful to build and present the elements in the matrix
 	as StringNode* object which will have all the properties of the
	StringNode class.
 	For direction :- A = Above; L = Left; B = Both; D = Diagonal; N = NULL
 */
class StringNode{
	
	private:
		int rank;
		bool hasDiagonal;
		StringNode* previous;
		string characters;
		char direction;
		
	public:
		StringNode(){
			this->rank= 0;
			this->hasDiagonal = false;
			this->previous = NULL;
			this->characters = "PHI";
			this->direction = 'N'; 
		}
		
		void setRank(int rank){
			this->rank = rank;
		}
		
		int getRank(){
			return rank;
		}
		
		void setHasDiagonal(bool hasDiagonal){
			this->hasDiagonal = hasDiagonal;
		}
		
		bool getHasDiagonal(){
			return hasDiagonal;
		}
		
		void setPrevious(StringNode* previous){
			this->previous = previous;
		}
		
		StringNode* getPrevious(){
			return this->previous;
		}
		
		void setCharacters(string characters){
			this->characters = characters;
		}
		
		string getCharacters(){
			return this->characters;
		}
		
		void setDirection(char direction){
			this->direction = direction;
		}
		
		char getDirection(){
			return this->direction;
		}
};

/* 
	We are creating a 2D-vector type and give it a name as
	'LCSMATRIX' so everytime if we want to create a 2D vector
	we will call the LCSMATRIX which is inturn a vector<vector<StringNode*>> type.
*/
typedef vector<vector<StringNode*> > LCSMATRIX;

/*
	This class will perform the necessary functions regarding
	LONGEST COMMON SUB-SEQUENT STRING like building, showing
	and applying the logic of LCS.
*/
class LCS{
	
	private:
		LCSMATRIX lcsM;
		string str1;
		string str2;
		string dispStr;
		int sizeStr1;
		int sizeStr2;
		int rank;
		StringNode* newStrNode = NULL;
		StringNode* previous = NULL;
		StringNode* left = NULL;
		StringNode* above = NULL;
	
	public:
		LCS(string str1, string str2){
			if (str1.size() > str2.size()) {
        		swap(str1, str2); //We are checking only because we want to have the string with min length to be in row
    		}
			this->str1 = str1;
			this->str2 = str2;
			this->sizeStr1 = str1.size();
			this->sizeStr2 = str2.size();
			lcsM.resize(sizeStr1 + 1, vector<StringNode*>(sizeStr2 + 1));
		}
		
		//To Convert the integer to string	
		string intTostr(int num) {
        	stringstream ss;
        	ss << num;
        	return ss.str();
    	}
		
		/*
			This function builds the LCS matrix which will be used
			to identify the LCS later on. This is a good example of
			DYNAMIC PROGRAMMING.
		*/
		void buildLCSMatrix(){
			
			lcsM[0][0] = new StringNode();
				
			//str1 is considered in rows
			for(int i = 1; i < sizeStr1 + 1; i++){
				lcsM[i][0] = new StringNode();
			}
			
			//str2 is considered in columns
			for(int i = 1; i < sizeStr2 + 1; i++){
				lcsM[0][i] = new StringNode();
			}
			
			/* 
				For filling the values we will loop through
				both the strings simultaneously.
				1. If match found then that StringNode* object will have its diagonal
				property set to true and direction set to 'D'. It's previous member
				will be its diagonal opposite object. Also the 'i-1' element in
				the any of the string will be the character of that object.
				2. If match not found then there are three scenarios:
					a. If left-value > above-value, then we will copy the
					left value and its direction will be set to 'L' and 
					previous will be set to object left of the current object.
					b. If left-value < above-value, then we will copy the
					above value and its direction will be set to 'A' and 
					previous will be set to object above the current object.
					c. If none of these case is true, then we will copy any
					of the value, Its direction will be set to 'B' and either
					of the left or above object can be set as previous for 
					that particular object.
			*/ 
			for (int i = 1; i < sizeStr1 + 1; i++){
				for (int j = 1; j < sizeStr2 + 1; j++){
					string str = "";
					newStrNode = new StringNode();
					if (str1[i-1] == str2[j-1]){
						newStrNode->setHasDiagonal(true);
						newStrNode->setDirection('D');
						previous = lcsM[i-1][j-1];
						newStrNode->setRank(previous->getRank() + 1); 
						newStrNode->setPrevious(previous);
						str += str1[i-1];
						newStrNode->setCharacters(str);
					} else {
						left = lcsM[i][j-1];
						above = lcsM[i-1][j];
						str += str1[i-1];
						str += str2[j-1];
						if (left->getRank() > above->getRank()){
							newStrNode->setRank(left->getRank());
							newStrNode->setPrevious(left);
							newStrNode->setDirection('L');
						}
						else if (left->getRank() < above->getRank()){
							newStrNode->setRank(above->getRank());
							newStrNode->setPrevious(above);
							newStrNode->setDirection('A');
						}
						else {
							newStrNode->setRank(left->getRank());
							newStrNode->setPrevious(left);
							newStrNode->setDirection('B');
						}
						newStrNode->setCharacters(str);
					}
					lcsM[i][j] = newStrNode;
				}
			}
		}
		
		/*
			This function displays the LCSMatrix
		*/	
		void showLCSMatrix() {
			
			StringNode* first = lcsM[0][0];
			
			/*
				Displaying Column-Labels of character string
			*/
			cout<< setw(2*(sizeStr1+1))<< first->getCharacters() << setw(sizeStr1+1);
			for (int i = 0; i < sizeStr2; i++){
				cout<< str2[i] << setw(sizeStr1+1);
			}
			cout<<endl;
			
			/*
				Displaying First Row Values (i.e 0 values)
			*/
			cout<< first->getCharacters() << setw(sizeStr1+1);
			for (int i = 0; i < sizeStr2 + 1; i++){
				newStrNode = lcsM[0][i];
				cout<< intTostr(newStrNode->getRank()) + newStrNode->getDirection() << setw(sizeStr1+1);
			}
			cout<<endl;
			
			/*
				Displaying other values in the matrix form with the Row-Labels
			*/
			for (int i = 1; i < sizeStr1 + 1; i++){
				cout<< str1[i-1] << setw(sizeStr1+1);
				newStrNode = lcsM[i][0];
				cout << intTostr(newStrNode->getRank()) + newStrNode->getDirection() << setw(sizeStr1+1);
				for (int j = 1; j < sizeStr2 + 1; j++){
					newStrNode = lcsM[i][j];
					cout<< intTostr(newStrNode->getRank()) + newStrNode->getDirection() << setw(sizeStr1+1);	
				}
				cout<<endl;
			}	
		}
		
		/*
			This is the logic function to find the LCS of the strings.
			We will find this by taking the last value of the matrix
			and declaring it as 'previous'.
			If the previous's diagonal property is set to true then we
			will capture the character of that object else we will move
			on to previous of the current previous.
			This cycle will remain until the previous is not NULL.
			Lastly, we will reverse the string to get our required LCS Stirng.
		*/
		void lcsLogic(){
			string lcs = "";
			previous = lcsM[sizeStr1][sizeStr2];
			cout<<endl<<"\nTHE LENGTH OF THE LONGEST SUB-SEQUENCE IS: "<<previous->getRank()<<endl;			
			cout<<"\nPATH TAKEN: ";
			while (previous != NULL){
				
				if (previous->getHasDiagonal()){
					lcs += previous->getCharacters();
				}
				
				if (previous->getPrevious() != NULL){
					cout<< intTostr(previous->getRank()) + previous->getDirection() << " --> ";
				} else {
					cout<< intTostr(previous->getRank()) + previous->getDirection();
				}
				previous = previous->getPrevious();
			}
			cout<<endl<<"\nTHE LONGEST SUB-SEQUENT STRING IS: " << string(lcs.rbegin(), lcs.rend());
		}
		
};

int main(){
	
	string str1,str2;
	cout << endl << "Enter the string 1: ";
	cin >> str1;
	cout << endl << "Enter the string 2: ";
	cin >> str2;
	cout << endl;
	LCS l(str1,str2);
	l.buildLCSMatrix();
	l.showLCSMatrix();
	l.lcsLogic();
	return 0;
}
