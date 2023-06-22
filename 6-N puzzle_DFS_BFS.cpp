//#include <iostream>
//#include <vector>
//#include <queue>
//#include <stack>
//#include <map>
//#include <algorithm>
//
//using namespace std;
//
//const int N = 4; // Size of the puzzle board
//
//// Structure to represent a state of the puzzle
//struct PuzzleState {
//    int board[N][N];
//    int blankRow;
//    int blankCol;
//
//    // Operator overloading for less-than comparison
//    bool operator<(const PuzzleState& other) const {
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                if (board[i][j] != other.board[i][j]) {
//                    return board[i][j] < other.board[i][j];
//                }
//            }
//        }
//        return false;
//    }
//};
//
//// Function to print the puzzle board
//void printBoard(const PuzzleState& state) {
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            cout << state.board[i][j] << "\t";
//        }
//        cout << endl;
//    }
//    cout << endl;
//}
//
//// Function to check if a given state is the goal state
//bool isGoalState(const PuzzleState& state) {
//    int value = 1;
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            if (state.board[i][j] != value && value != N * N) {
//                return false;
//            }
//            value++;
//        }
//    }
//    return true;
//}
//
//// Function to check if a move is valid
//bool isValidMove(int row, int col) {
//    return (row >= 0 && row < N && col >= 0 && col < N);
//}
//
//// Function to perform a move in the puzzle board
//void makeMove(PuzzleState& state, int newRow, int newCol) {
//    swap(state.board[state.blankRow][state.blankCol], state.board[newRow][newCol]);
//    state.blankRow = newRow;
//    state.blankCol = newCol;
//}
//
//// Function to solve the puzzle using BFS (Breadth-First Search)
//bool solvePuzzleBFS(const PuzzleState& initialState) {
//    queue<PuzzleState> q;
//    map<PuzzleState, bool> visited;
//    map<PuzzleState, PuzzleState> parent;
//
//    q.push(initialState);
//    visited[initialState] = true;
//    parent[initialState] = initialState;
//
//    while (!q.empty()) {
//        PuzzleState currentState = q.front();
//        q.pop();
//
//        printBoard(currentState);
//
//        if (isGoalState(currentState)) {
//            cout << "Puzzle solved using BFS!\n";
//            return true;
//        }
//
//        int row = currentState.blankRow;
//        int col = currentState.blankCol;
//
//        // Move Up
//        if (isValidMove(row - 1, col)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row - 1, col);
//            if (!visited[newState]) {
//                q.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//
//        // Move Down
//        if (isValidMove(row + 1, col)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row + 1, col);
//            if (!visited[newState]) {
//                q.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//
//        // Move Left
//        if (isValidMove(row, col - 1)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row, col - 1);
//            if (!visited[newState]) {
//                q.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//
//        // Move Right
//        if (isValidMove(row, col + 1)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row, col + 1);
//            if (!visited[newState]) {
//                q.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//    }
//
//    return false;
//}
//
//// Function to solve the puzzle using DFS (Depth-First Search)
//bool solvePuzzleDFS(const PuzzleState& initialState) {
//    stack<PuzzleState> s;
//    map<PuzzleState, bool> visited;
//    map<PuzzleState, PuzzleState> parent;
//
//    s.push(initialState);
//    visited[initialState] = true;
//    parent[initialState] = initialState;
//
//    while (!s.empty()) {
//        PuzzleState currentState = s.top();
//        s.pop();
//
//        printBoard(currentState);
//
//        if (isGoalState(currentState)) {
//            cout << "Puzzle solved using DFS!\n";
//            return true;
//        }
//
//        int row = currentState.blankRow;
//        int col = currentState.blankCol;
//
//        // Move Up
//        if (isValidMove(row - 1, col)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row - 1, col);
//            if (!visited[newState]) {
//                s.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//
//        // Move Down
//        if (isValidMove(row + 1, col)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row + 1, col);
//            if (!visited[newState]) {
//                s.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//
//        // Move Left
//        if (isValidMove(row, col - 1)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row, col - 1);
//            if (!visited[newState]) {
//                s.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//
//        // Move Right
//        if (isValidMove(row, col + 1)) {
//            PuzzleState newState = currentState;
//            makeMove(newState, row, col + 1);
//            if (!visited[newState]) {
//                s.push(newState);
//                visited[newState] = true;
//                parent[newState] = currentState;
//            }
//        }
//    }
//
//    return false;
//}
//
//int main() {
//    PuzzleState initialState;
//
//    cout << "Enter the initial state of the puzzle (space-separated numbers, 0 represents the blank tile):\n";
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            cin >> initialState.board[i][j];
//            if (initialState.board[i][j] == 0) {
//                initialState.blankRow = i;
//                initialState.blankCol = j;
//            }
//        }
//    }
//
//    cout << "\nSolving the puzzle using BFS:\n";
//    if (!solvePuzzleBFS(initialState)) {
//        cout << "Solution not found using BFS.\n";
//    }
//
//    cout << "\nSolving the puzzle using DFS:\n";
//    if (!solvePuzzleDFS(initialState)) {
//        cout << "Solution not found using DFS.\n";
//    }
//
//    return 0;
//}

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

const int N = 4; // Size of the puzzle board

// Structure to represent a state of the puzzle
struct PuzzleState {
    int board[N][N];
    int blankRow;
    int blankCol;
    int depth;  // Depth of the current state in the search tree
    int cost;   // Cost of reaching the current state
    string path;    // Path followed to reach the current state
    string previousMove;    // Name of the previous move

    // Operator overloading for less-than comparison
    bool operator<(const PuzzleState& other) const {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] != other.board[i][j]) {
                    return board[i][j] < other.board[i][j];
                }
            }
        }
        return false;
    }

    // Function to calculate the cost of the current state
    int calculateCost() const {
        int cost = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] != 0) {
                    int targetRow = (board[i][j] - 1) / N;
                    int targetCol = (board[i][j] - 1) % N;
                    cost += abs(i - targetRow) + abs(j - targetCol);
                }
            }
        }
        return cost;
    }
};

// Function to print the puzzle board
void printBoard(const PuzzleState& state) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << state.board[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Move: " << state.previousMove << endl;
    cout << "Cost: " << state.cost << endl;
    cout << "Path: " << state.path << endl;
    cout << endl;
}

// Function to check if a given state is the goal state
bool isGoalState(const PuzzleState& state) {
    int value = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (state.board[i][j] != value && value != N * N) {
                return false;
            }
            value++;
        }
    }
    return true;
}

// Function to check if a move is valid
bool isValidMove(int row, int col) {
    return (row >= 0 && row < N && col >= 0 && col < N);
}

// Function to perform a move in the puzzle board
void makeMove(PuzzleState& state, int newRow, int newCol) {
    swap(state.board[state.blankRow][state.blankCol], state.board[newRow][newCol]);
    state.blankRow = newRow;
    state.blankCol = newCol;
}

// Function to solve the puzzle using BFS (Breadth-First Search)
bool solvePuzzleBFS(const PuzzleState& initialState) {
    queue<PuzzleState> q;
    map<PuzzleState, bool> visited;
    map<PuzzleState, PuzzleState> parent;

    q.push(initialState);
    visited[initialState] = true;
    parent[initialState] = initialState;

    while (!q.empty()) {
        PuzzleState currentState = q.front();
        q.pop();

        printBoard(currentState);

        if (isGoalState(currentState)) {
            cout << "Puzzle solved using BFS!\n";
            return true;
        }

        int row = currentState.blankRow;
        int col = currentState.blankCol;

        // Move Up
        if (isValidMove(row - 1, col) && currentState.previousMove != "D") {
            PuzzleState newState = currentState;
            makeMove(newState, row - 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "U";
            newState.previousMove = "U";

            if (!visited[newState]) {
                q.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }

        // Move Down
        if (isValidMove(row + 1, col) && currentState.previousMove != "U") {
            PuzzleState newState = currentState;
            makeMove(newState, row + 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "D";
            newState.previousMove = "D";

            if (!visited[newState]) {
                q.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }

        // Move Left
        if (isValidMove(row, col - 1) && currentState.previousMove != "R") {
            PuzzleState newState = currentState;
            makeMove(newState, row, col - 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "L";
            newState.previousMove = "L";

            if (!visited[newState]) {
                q.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }

        // Move Right
        if (isValidMove(row, col + 1) && currentState.previousMove != "L") {
            PuzzleState newState = currentState;
            makeMove(newState, row, col + 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "R";
            newState.previousMove = "R";

            if (!visited[newState]) {
                q.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }
    }

    return false;
}

// Function to solve the puzzle using DFS (Depth-First Search)
bool solvePuzzleDFS(const PuzzleState& initialState) {
    stack<PuzzleState> s;
    map<PuzzleState, bool> visited;
    map<PuzzleState, PuzzleState> parent;

    s.push(initialState);
    visited[initialState] = true;
    parent[initialState] = initialState;

    while (!s.empty()) {
        PuzzleState currentState = s.top();
        s.pop();

        printBoard(currentState);

        if (isGoalState(currentState)) {
            cout << "Puzzle solved using DFS!\n";
            return true;
        }

        int row = currentState.blankRow;
        int col = currentState.blankCol;

        // Move Up
        if (isValidMove(row - 1, col) && currentState.previousMove != "D") {
            PuzzleState newState = currentState;
            makeMove(newState, row - 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "U";
            newState.previousMove = "U";

            if (!visited[newState]) {
                s.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }

        // Move Down
        if (isValidMove(row + 1, col) && currentState.previousMove != "U") {
            PuzzleState newState = currentState;
            makeMove(newState, row + 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "D";
            newState.previousMove = "D";

            if (!visited[newState]) {
                s.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }

        // Move Left
        if (isValidMove(row, col - 1) && currentState.previousMove != "R") {
            PuzzleState newState = currentState;
            makeMove(newState, row, col - 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "L";
            newState.previousMove = "L";

            if (!visited[newState]) {
                s.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }

        // Move Right
        if (isValidMove(row, col + 1) && currentState.previousMove != "L") {
            PuzzleState newState = currentState;
            makeMove(newState, row, col + 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calculateCost();
            newState.path += "R";
            newState.previousMove = "R";

            if (!visited[newState]) {
                s.push(newState);
                visited[newState] = true;
                parent[newState] = currentState;
            }
        }
    }

    return false;
}

int main() {
    PuzzleState initialState;

    cout << "Enter the initial state of the puzzle (space-separated numbers, 0 represents the blank tile):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> initialState.board[i][j];
            if (initialState.board[i][j] == 0) {
                initialState.blankRow = i;
                initialState.blankCol = j;
            }
        }
    }

    initialState.depth = 0;
    initialState.cost = initialState.calculateCost();
    initialState.path = "";
    initialState.previousMove = "";

    cout << "\nSolving the puzzle using BFS:\n";
    if (!solvePuzzleBFS(initialState)) {
        cout << "Solution not found using BFS.\n";
    }

    cout << "\nSolving the puzzle using DFS:\n";
    if (!solvePuzzleDFS(initialState)) {
        cout << "Solution not found using DFS.\n";
    }

    return 0;
}


/*
Use this example to run the code
1 2 3 4
5 6 7 8
9 10 0 11
13 14 15 12
*/

