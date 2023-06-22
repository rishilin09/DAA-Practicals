// 0/1 Knapsack
//#include <iostream>
//#include <vector>
//#include <stdlib.h>
//using namespace std;
//
//struct Item {
//    int value;
//    int weight;
//};
//
//void knapsackBacktracking(int W, vector<Item>& items, vector<int>& taken, vector<int>& currTaken, int currValue, int currWeight, int index, int& maxVal) {
//    if (index >= items.size())
//        return;
//
//    currTaken[index] = 1;
//    currValue += items[index].value;
//    currWeight += items[index].weight;
//
//    if (currWeight <= W && currValue > maxVal) {
//        maxVal = currValue;
//        taken = currTaken;
//    }
//
//    knapsackBacktracking(W, items, taken, currTaken, currValue, currWeight, index + 1, maxVal);
//
//    currTaken[index] = 0;
//    currValue -= items[index].value;
//    currWeight -= items[index].weight;
//
//    knapsackBacktracking(W, items, taken, currTaken, currValue, currWeight, index + 1, maxVal);
//}
//
//int main() {
//    Item itemArr[] = {{80, 10}, {100, 20}, {120, 30}};
//    vector<Item> items(itemArr, itemArr + sizeof(itemArr) / sizeof(itemArr[0]));
//    int W = 50;
//    int maxVal = 0;
//    vector<int> taken(items.size(), 0);
//    vector<int> currTaken(items.size(), 0);
//    knapsackBacktracking(W, items, taken, currTaken, 0, 0, 0, maxVal);
//	cout << "Taken items: ";
//    for (int i = 0; i < taken.size(); i++) {
//        if (taken[i])
//            cout << i << " ";
//    }
//    cout << endl;
//    cout << "Maximum value: " << maxVal << endl;
//    return 0;
//}


// Fractional Knapsack
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value;
    int weight;
    double fraction;
};

bool compare(Item a, Item b) {
    double ratioA = (double)a.value / a.weight;
    double ratioB = (double)b.value / b.weight;
    return ratioA > ratioB;
}

double knapsackFractional(int W, vector<Item>& items, vector<double>& taken) {
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    int remainingWeight = W;

    for (int i = 0; i < items.size(); i++) {
        if (items[i].weight <= remainingWeight) {
            totalValue += items[i].value;
            remainingWeight -= items[i].weight;
            taken[i] = 1.0;
        } else {
            double fraction = (double)remainingWeight / items[i].weight;
            totalValue += fraction * items[i].value;
            taken[i] = fraction;
            break;
        }
    }

    return totalValue;
}

int main() {
    Item itemArr[] = {{60, 10}, {100, 20}, {120, 30}};
    vector<Item> items(itemArr, itemArr + sizeof(itemArr) / sizeof(itemArr[0]));
    int W = 50;

    vector<double> taken(items.size(), 0.0);
    double totalValue = knapsackFractional(W, items, taken);

    cout << "Total value: " << totalValue << endl;
    cout << "Taken items: " << endl;
    for (int i = 0; i < items.size(); i++) {
        if (taken[i] > 0.0)
            cout << "Item " << i << ": " << taken[i] << endl;
    }

    return 0;
}

