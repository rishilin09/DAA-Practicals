#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>

using namespace std;

class SubsetSum {
	
	public:
		vector<vector<int> > findSubSet(const vector<int>& numsSet, int target, vector<int>& currSubset, int currIdx)
		{
			vector<vector<int> > subsets;
			
			if (target == 0){
				subsets.push_back(currSubset);
        		return subsets;
			}
			
			if (target < 0 || currIdx == numsSet.size()){
				return subsets;
			}
			
			// Include the current number in the subset and recurse
			currSubset.push_back(numsSet[currIdx]);
			vector<vector<int> > includeSubset = findSubSet(numsSet, target - numsSet[currIdx], currSubset, currIdx + 1);
			subsets.insert(subsets.end(), includeSubset.begin(), includeSubset.end());
			
			// Exclude the current number from the subset and recurse
		    currSubset.pop_back();
		    vector<vector<int> > excludeSubset = findSubSet(numsSet, target, currSubset, currIdx + 1);
		    subsets.insert(subsets.end(), excludeSubset.begin(), excludeSubset.end());
		
		    return subsets;
				
		}		
	
		vector<vector<int> > subsetSum(const vector<int>& numsSet, int target) {
    		vector<int> currSubset;
    		return findSubSet(numsSet, target, currSubset, 0);
		}
};


int main(){
	
	int noEle, input, target;
	cout << "Enter the number of elements in the set: ";
	cin >> noEle;
	vector<int> numsSet;
    for(int i=0; i < noEle; i++){
    	cout << endl <<"Enter the " << i+1 << " element: ";
    	cin >> input;
    	numsSet.push_back(input);
	}

    cout << endl <<"\nEnter the target the sum: ";
	cin >> target;
	
	SubsetSum sub;
    vector<vector<int> > subsets = sub.subsetSum(numsSet, target);

    // Print the subsets
    cout << endl << "THE ALL POSSIBLE SUBSETS THAT REACH TO TARGET VALUE " << target << " are:"<<endl;
    for (vector<vector<int> >::const_iterator it = subsets.begin(); it != subsets.end(); ++it) {
        cout << endl << "{ ";
		for (vector<int>::const_iterator iter = it->begin(); iter != it->end(); ++iter) {
			cout << *iter;	
			if (iter != it->end() - 1) {
                cout << ", ";
            }
        }
        cout << " }" << endl;
    }
    return 0;
	
}
