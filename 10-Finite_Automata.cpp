#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

class State {
private:
    string stateValue;
    map<char, State> transitions;

public:
    void setStateValue(const string& stateValue) {
        this->stateValue = stateValue;
    }

    string getStateValue() const {
        return stateValue;
    }

    void setTransitions(const State& nextState, char transitionValue) {
        transitions[transitionValue] = nextState;
    }

    char getTransitionValue(const State& nextState) const {
        for (map<char, State>::const_iterator it = transitions.begin(); it != transitions.end(); ++it) {
            if (it->second.getStateValue() == nextState.getStateValue()) {
                return it->first;
            }
        }
        return '\0';
    }

    bool operator<(const State& other) const {
        return stateValue < other.stateValue;
    }
};

class FiniteAutomata {
private:
    State initialState;
    vector<State> vectorQ;
    vector<State> vectorF;
    vector<char> inputs;
    map<State, map<char, State> > transFunc;
    int noStates;
    int noInputs;

public:
    FiniteAutomata() {
        cout << "Enter the number of states: ";
        cin >> noStates;
        cout << "Enter the number of inputs: ";
        cin >> noInputs;
        createStates(noStates);
        createInputs(noInputs);
    }

    void createStates(int nStates) {
        char choice;
        for (int i = 0; i < nStates; i++) {
            cout << "Is state q" << i << " an initial state? (Y/N): ";
            cin >> choice;
            State newState;
            stringstream ss;
            ss << "q" << i;
            string stateValue;
            ss >> stateValue;
            newState.setStateValue(stateValue);
            if ((choice == 'Y' || choice == 'y') && initialState.getStateValue().empty()) {
                initialState = newState;
            } else {
                cout << "Is state q" << i << " a final state? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    vectorF.push_back(newState);
                }
            }
            vectorQ.push_back(newState);
        }
    }

    void createInputs(int noInp) {
        char inp;
        for (int i = 0; i < noInp; i++) {
            cout << "Enter input " << i + 1 << ": ";
            cin >> inp;
            inputs.push_back(inp);
        }
    }

    void setTransitionFunction() {
        for (vector<State>::const_iterator it = vectorQ.begin(); it != vectorQ.end(); ++it) {
            map<char, State> transitions;
            for (vector<char>::const_iterator inputIt = inputs.begin(); inputIt != inputs.end(); ++inputIt) {
                cout << "Enter the transition for state " << it->getStateValue() << " with input " << *inputIt << ": ";
                int nextStateIndex;
                cin >> nextStateIndex;
                if (nextStateIndex < 0 || nextStateIndex >= noStates) {
                    continue;
                }
                State nextState = vectorQ[nextStateIndex];
                transitions[*inputIt] = nextState;
            }
            if (!transitions.empty()) {
                transFunc[*it] = transitions;
            }
        }
    }

    void processInput() {
        cout << "Enter the input sequence: ";
        string inputSequence;
        cin >> inputSequence;

        State currentState = initialState;

        for (string::const_iterator it = inputSequence.begin(); it != inputSequence.end(); ++it) {
            char currentInput = *it;
            map<char, State>::const_iterator transIt = transFunc[currentState].find(currentInput);
            if (transIt != transFunc[currentState].end()) {
                State nextState = transIt->second;
                currentState = nextState;
            } else {
                cout << "Invalid input sequence!\n";
                return;
            }
        }

        if (isFinalState(currentState)) {
            cout << "Valid input sequence!\n";
        } else {
            cout << "Invalid input sequence!\n";
        }
    }

    bool isFinalState(const State& state) {
        for (vector<State>::const_iterator it = vectorF.begin(); it != vectorF.end(); ++it) {
            if (state.getStateValue() == it->getStateValue()) {
                return true;
            }
        }
        return false;
    }
    
    void printTransitionFunction() {
        cout << "\nTransition Function:\n";

        // Calculate column widths
        int stateColumnWidth = 8;
        int inputColumnWidth = 8;
        int transitionColumnWidth = 8;

        // Print column headers (inputs)
        cout << string(stateColumnWidth, ' ') << "|";
        for (vector<char>::const_iterator it = inputs.begin(); it != inputs.end(); ++it) {
            cout << setw(inputColumnWidth) << *it << "|";
        }
        cout << endl;

        // Print separator line
        cout << string(stateColumnWidth + 1, '-') << "+";
        for (size_t i = 0; i < inputs.size(); ++i) {
            cout << string(inputColumnWidth, '-') << "+";
        }
        cout << endl;

        // Print table rows (states and transition values)
        for (vector<State>::const_iterator stateIt = vectorQ.begin(); stateIt != vectorQ.end(); ++stateIt) {
            cout << setw(stateColumnWidth) << stateIt->getStateValue() << "|";
            map<char, State> transitions = transFunc[*stateIt];
            for (vector<char>::const_iterator inputIt = inputs.begin(); inputIt != inputs.end(); ++inputIt) {
                map<char, State>::const_iterator transIt = transitions.find(*inputIt);
                if (transIt != transitions.end()) {
                    cout << setw(transitionColumnWidth) << transIt->second.getStateValue() << "|";
                } else {
                    cout << setw(transitionColumnWidth) << "-" << "|";
                }
            }
            cout << endl;

            // Print separator line
            cout << string(stateColumnWidth + 1, '-') << "+";
            for (size_t i = 0; i < inputs.size(); ++i) {
                cout << string(inputColumnWidth, '-') << "+";
            }
            cout << endl;
        }
    }
};

int main() {
    FiniteAutomata automata;
    automata.setTransitionFunction();
    automata.printTransitionFunction();
    automata.processInput();
    return 0;
}

