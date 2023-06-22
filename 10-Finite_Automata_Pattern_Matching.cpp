// CPP program for Finite Automata Pattern searching
// Algorithm
#include <bits/stdc++.h>
#include<set>
using namespace std;
#define NO_OF_CHARS 256

set<int>charset;

int getNextState(string pat, int M, int state, int x)
{
    
	if (state < M && x == pat[state])
		return state+1;


	int ns, i;
	
	for (ns = state; ns > 0; ns--)
	{
		if (pat[ns-1] == x)
		{
			for (i = 0; i < ns-1; i++)
				if (pat[i] != pat[state-ns+1+i])
					break;
			if (i == ns-1)
				return ns;
		}
	}

	return 0;
}

void computeTF(string pat, int M, int TF[][NO_OF_CHARS])
{
	int state, x;
	for (state = 0; state <= M; ++state)
		for (x = 0; x < NO_OF_CHARS; ++x)
			TF[state][x] = getNextState(pat, M, state, x);
}


void search(string pat, string txt)
{   
    
    int count=0;
    int c2=0;
	int M = pat.size();
	
	for(int i=0;i<M;i++){
	    
	    charset.insert((int)pat[i]);
	}
	int N = txt.size();

	int TF[M+1][NO_OF_CHARS];

	computeTF(pat, M, TF);
	
	
	//
	
	cout<<"The Transition table is "<<endl;
	for (int p = 0; p <= M; ++p){
		for (int q = 0; q < NO_OF_CHARS; ++q){
		    if(charset.find(q)!=charset.end()){
		        cout<<TF[p][q]<<" ";
		    }
		}
		cout<<endl;
	}
	
	
	//

	// Process txt over FA.
	int i, state=0;
	for (i = 0; i < N; i++)
	{
		state = TF[state][txt[i]];
		if (state == M)
			cout<<" Pattern found at index "<< i-M+1<<endl;
	}
}


int main()
{
	string txt = "AABAACAADAABAAABAA";
	string pat = "ABA";
	search(pat, txt);
	return 0;
}
