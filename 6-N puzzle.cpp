#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Size of the puzzle board
const int boardSize = 4;

//Opposite moves Map Type
map<string, string> oppositeMoves;

// Structure to represent a state of the puzzle
struct PuzzleState {
    int board[boardSize][boardSize];
    int cost;
    int depth;
    int blankRow;
    int blankCol;
    string previousMove;
    string path;

    // calculate distance
    int calculateCost() {
        int sum = 0;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                int value = board[i][j];
                if (value != 0) {
                    int targetRow = (value - 1) / boardSize;
                    int targetCol = (value - 1) % boardSize;
                    sum += abs(i - targetRow) + abs(j - targetCol);
                }
            }
        }
        return sum;
    }
};

// Custom comparison function for priority queue
struct ComparePuzzleState {
    bool operator()(const PuzzleState& a, const PuzzleState& b) {
        return (a.cost + a.depth) > (b.cost + b.depth);
    }
};

class N_Puzzle {
public:
    N_Puzzle() {
        oppositeMoves["U"] = "D";
        oppositeMoves["D"] = "U";
        oppositeMoves["L"] = "R";
        oppositeMoves["R"] = "L";
    }

    // check if a given state is the goal state
    bool isGoalState(const PuzzleState& state) {
        int value = 1;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (state.board[i][j] != value && value != boardSize * boardSize) {
                    return false;
                }
                value++;
            }
        }
        return true;
    }

    // check if a move is valid
    bool isValidMove(int row, int col) {
        return (row >= 0 && row < boardSize && col >= 0 && col < boardSize);
    }

    // perform a move in the puzzle board
    void makeMove(PuzzleState& state, int newRow, int newCol) {
        swap(state.board[state.blankRow][state.blankCol], state.board[newRow][newCol]);
        state.blankRow = newRow;
        state.blankCol = newCol;
    }

    // print the puzzle board
    void printBoard(const PuzzleState& state) {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                cout << state.board[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    // solve the puzzle using Branch and Bound technique
    void solvePuzzle(const PuzzleState& initialState) {
        priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> pq;
        pq.push(initialState);

        int iteration = 0;
        while (!pq.empty()) {
            PuzzleState currentState = pq.top();
            pq.pop();

            cout << endl << "\nIteration " << iteration << ":\n";
            cout << "Current Cost: " << currentState.cost << endl;
            cout << "Current Path: " << currentState.path << endl;
            printBoard(currentState);

            if (isGoalState(currentState)) {
                cout << "\nPuzzle solved!\n";
                cout << "Minimum Cost: " << currentState.cost << endl;
                cout << "Minimum Path: " << currentState.path << endl;
                return;
            }

            int row = currentState.blankRow;
            int col = currentState.blankCol;

            // Move Up
            if (isValidMove(row - 1, col) && oppositeMoves[currentState.previousMove] != "U") {
                PuzzleState newState = currentState;
                makeMove(newState, row - 1, col);
                newState.depth = currentState.depth + 1;
                newState.cost = newState.calculateCost();
                newState.path += "U";
                newState.previousMove = "U";
                pq.push(newState);
                cout << "Possible Move (Up): " << endl;
                cout << "Cost of the Move: "<< newState.cost <<endl;
                printBoard(newState);
            }

            // Move Down
            if (isValidMove(row + 1, col) && oppositeMoves[currentState.previousMove] != "D") {
                PuzzleState newState = currentState;
                makeMove(newState, row + 1, col);
                newState.depth = currentState.depth + 1;
                newState.cost = newState.calculateCost();
                newState.path += "D";
                newState.previousMove = "D";
                pq.push(newState);
                cout << "Possible Move (Down): " << endl;
                cout << "Cost of the Move: "<< newState.cost <<endl;
                printBoard(newState);
            }

            // Move Left
            if (isValidMove(row, col - 1) && oppositeMoves[currentState.previousMove] != "L") {
                PuzzleState newState = currentState;
                makeMove(newState, row, col - 1);
                newState.depth = currentState.depth + 1;
                newState.cost = newState.calculateCost();
                newState.path += "L";
                newState.previousMove = "L";
                pq.push(newState);
                cout << "Possible Move (Left): " << endl;
                cout << "Cost of the Move: "<< newState.cost <<endl;
                printBoard(newState);
            }

            // Move Right
            if (isValidMove(row, col + 1) && oppositeMoves[currentState.previousMove] != "R") {
                PuzzleState newState = currentState;
                makeMove(newState, row, col + 1);
                newState.depth = currentState.depth + 1;
                newState.cost = newState.calculateCost();
                newState.path += "R";
                newState.previousMove = "R";
                pq.push(newState);
                cout << "Possible Move (Right): " << endl;
                cout << "Cost of the Move: "<< newState.cost <<endl;
                printBoard(newState);
            }

            iteration++;
        }

        cout << "Solution not found within the specified iterations.\n";
    }
};

int main() {
    N_Puzzle puzzleSolver;

    PuzzleState initialState;
    cout << "Enter the initial state of the puzzle (space-separated numbers, 0 represents the blank tile):\n";
    for (int i = 0; i < boardSize; i++) {
    	cout<< endl <<"For Row "<< i+1 <<": "<<endl;
        for (int j = 0; j < boardSize; j++) {
            cin >> initialState.board[i][j];
            if (initialState.board[i][j] == 0) {
                initialState.blankRow = i;
                initialState.blankCol = j;
            }
        }
        cout << endl;
    }

    initialState.cost = initialState.calculateCost();
    initialState.depth = 0;
    initialState.path = "";
    initialState.previousMove = "";

    puzzleSolver.solvePuzzle(initialState);

    return 0;
}

