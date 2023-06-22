#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Backtracking approach
void printLCSBacktracking(const string& s1, const string& s2, int i, int j, vector<vector<int> >& dp) {
    if (i == 0 || j == 0)
        return;
    
    if (s1[i - 1] == s2[j - 1]) {
        printLCSBacktracking(s1, s2, i - 1, j - 1, dp);
        cout << s1[i - 1];
    }
    else {
        if (dp[i][j - 1] > dp[i - 1][j])
            printLCSBacktracking(s1, s2, i, j - 1, dp);
        else
            printLCSBacktracking(s1, s2, i - 1, j, dp);
    }
}

void findLCSBacktracking(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
    }

    printLCSBacktracking(s1, s2, m, n, dp);
}

// Greedy approach
void findLCSGreedy(const string& s1, const string& s2) {
    string lcs;
    int i = 0;
    int j = 0;
    while (i < s1.length() && j < s2.length()) {
        if (s1[i] == s2[j]) {
            lcs += s1[i];
            i++;
            j++;
        }
        else if (s1[i] != s2[j]) {
            if (i < s1.length() - 1 && j < s2.length() - 1 && s1[i + 1] == s2[j + 1]) {
                lcs += s1[i + 1];
                i += 2;
                j += 2;
            }
            else if (i < s1.length() - 1 && s1[i + 1] == s2[j]) {
                i++;
            }
            else if (j < s2.length() - 1 && s1[i] == s2[j + 1]) {
                j++;
            }
            else {
                i++;
                j++;
            }
        }
    }
    cout << lcs << endl;
}

int main() {
	
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";

    cout << "Backtracking approach: ";
    findLCSBacktracking(s1, s2);
    cout << endl;

    cout << "Greedy approach: ";
    findLCSGreedy(s1, s2);
    cout << endl;

    return 0;
}

