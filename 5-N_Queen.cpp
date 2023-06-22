#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<bool> >& board, int row, int col) {
    // Check upper areas
    for (int i = row; i >= 0; i--) {
        if (board[i][col]) {
            return false;
        }
    }

    int r = row;
    int c = col;

    // Check diagonal left
    while (r >= 0 && c >= 0) {
        if (board[r][c]) {
            return false;
        }
        r--;
        c--;
    }

    int rr = row;
    int cr = col;

    // Check diagonal right
    while (rr >= 0 && cr < board.size()) {
        if (board[rr][cr]) {
            return false;
        }
        rr--;
        cr++;
    }

    return true;
}

void display(vector<vector<bool> >& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j]) {
                cout << "Q ";
            } else {
                cout << "X ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int nQueen(vector<vector<bool> >& board, int row) {
    if (row == board.size()) {
        static int solutionCount = 0; // Counter to keep track of the number of solutions
        cout << "Solution " << ++solutionCount << ":\n";
        display(board);
        return 1;
    }

    int count = 0;

    for (int col = 0; col < board.size(); col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = true;
            cout << "Placing queen at position (" << row << ", " << col << ")\n";
            count += nQueen(board, row + 1);
            board[row][col] = false;
            cout << "Removing queen from position (" << row << ", " << col << ")\n";
        }
    }

    return count;
}

int main() {
    int n;
    cout << "Enter the size of the board: ";
    cin >> n;

    vector<vector<bool> > board(n, vector<bool>(n, false));
    cout << "Solutions for " << n << " queens:\n";
    int totalSolutions = nQueen(board, 0);
    cout << "Total solutions: " << totalSolutions << endl;

    return 0;
}

