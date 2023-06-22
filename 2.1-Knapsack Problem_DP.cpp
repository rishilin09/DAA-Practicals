// 0 / 1 Knapsack
#include <iostream>
#include <vector>
using namespace std;

struct Item {
    int value;
    int weight;
};

pair<int, vector<vector<int> > > knapsackDP(int W, vector<Item>& items) {
    int n = items.size();
    vector<vector<int> > K(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (items[i - 1].weight <= w) {
                K[i][w] = max(items[i - 1].value + K[i - 1][w - items[i - 1].weight], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    return make_pair(K[n][W], K);
}

int main() {
    Item itemArr[] = {{60, 10}, {100, 20}, {120, 30}};
    vector<Item> items(itemArr, itemArr + sizeof(itemArr) / sizeof(itemArr[0]));
    int W = 40;
    pair<int, vector<vector<int> > > result = knapsackDP(W, items);

    int maxVal = result.first;
    vector<vector<int> > K = result.second;

    vector<int> taken(items.size(), 0);
    int i = items.size(), j = W;
    while (i > 0 && j > 0) {
        if (K[i][j] != K[i - 1][j]) {
            taken[i - 1] = 1;
            j -= items[i - 1].weight;
        }
        i--;
    }
    
	cout << "Taken items: ";
    for (int i = 0; i < items.size(); i++) {
        if (taken[i])
            cout << i << " ";
    }
    cout << endl;
    cout << "Maximum value: " << maxVal << endl;
    return 0;
}

