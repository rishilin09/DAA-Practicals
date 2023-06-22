// 0/1 Knapsack
//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//struct Item {
//    int value;
//    int weight;
//};
//
//bool compare(Item a, Item b) {
//    double ratioA = (double)a.value / a.weight;
//    double ratioB = (double)b.value / b.weight;
//    return ratioA > ratioB;
//}
//
//int bound(int i, int n, int W, vector<Item>& items, int currValue, int currWeight) {
//    if (currWeight >= W)
//        return 0;
//
//    int boundVal = currValue;
//    int totalWeight = currWeight;
//    while (i < n && totalWeight + items[i].weight <= W) {
//        boundVal += items[i].value;
//        totalWeight += items[i].weight;
//        i++;
//    }
//
//    if (i < n) {
//        boundVal += (W - totalWeight) * items[i].value / items[i].weight;
//    }
//
//    return boundVal;
//}
//
//void knapsackBnB(int W, vector<Item>& items, vector<int>& taken) {
//    int n = items.size();
//    sort(items.begin(), items.end(), compare);
//
//    vector<int> currTaken(n, 0);
//    int currValue = 0;
//    int currWeight = 0;
//    int maxVal = 0;
//
//    vector<int> path(n, 0);
//    int i = 0;
//
//    while (true) {
//        while (i < n && currWeight + items[i].weight <= W) {
//            currWeight += items[i].weight;
//            currValue += items[i].value;
//            currTaken[i] = 1;
//            i++;
//        }
//
//        if (i == n) {
//            if (currValue > maxVal) {
//                maxVal = currValue;
//                taken = currTaken;
//            }
//            if (path.empty())
//                break;
//
//            i = path.back();
//            path.pop_back();
//
//            currWeight -= items[i].weight;
//            currValue -= items[i].value;
//            currTaken[i] = 0;
//
//            i++;
//        } else {
//            if (bound(i, n, W, items, currValue, currWeight) > maxVal) {
//                path.push_back(i);
//            }
//            i++;
//        }
//    }
//}
//
//int main() {
//    Item itemArr[] = {{60, 10}, {100, 20}, {120, 30}};
//    vector<Item> items(itemArr, itemArr + sizeof(itemArr) / sizeof(itemArr[0]));
//    int W = 40;
//    vector<int> taken(items.size(), 0);
//    knapsackBnB(W, items, taken);
//    int maxVal = 0;
//    cout << "Items taken: ";
//    for (int i = 0; i < items.size(); i++) {
//        if (taken[i]) {
//            cout << i << " ";
//            maxVal += items[i].value;
//        }
//    }
//    cout << endl;
//    cout << "Total value: " << maxVal << endl;
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
};

bool compare(Item a, Item b) {
    double ratioA = (double)a.value / a.weight;
    double ratioB = (double)b.value / b.weight;
    return ratioA > ratioB;
}

void knapsackFractional(int W, vector<Item>& items, vector<double>& taken) {
    int n = items.size();
    sort(items.begin(), items.end(), compare);

    int currWeight = 0;
    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (currWeight + items[i].weight <= W) {
            currWeight += items[i].weight;
            totalValue += items[i].value;
            taken[i] = 1.0;
        } else {
            double fraction = (double)(W - currWeight) / items[i].weight;
            currWeight = W;
            totalValue += fraction * items[i].value;
            taken[i] = fraction;
            break;
        }
    }
}

int main() {
    Item itemArr[] = {{60, 10}, {100, 20}, {120, 30}};
    vector<Item> items(itemArr, itemArr + sizeof(itemArr) / sizeof(itemArr[0]));
    int W = 40;
    vector<double> taken(items.size(), 0.0);
    knapsackFractional(W, items, taken);

    double totalValue = 0.0;
    cout << "Items taken: " << endl;
    for (int i = 0; i < items.size(); i++) {
        if (taken[i] > 0.0) {
            cout << "Item " << i << ": " << taken[i] << endl;
            totalValue += taken[i] * items[i].value;
        }
    }
    cout << "Total value: " << totalValue << endl;

    return 0;
}

