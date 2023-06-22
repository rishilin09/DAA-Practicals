#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

class KnapSack
{

private:
	map<string, map<int, int> > ProductDetails;
	vector<float> ratios, temp_ratios;
	map<string, map<int, float> > Bag;
	int productSize = 0, bagSize = 0;
	string name = "";
	float ratio = 0.0, profit = 0.0, weight = 0.0;

public:
	// This a comparison function to sort the ratios in
	// descending order
	struct DescendingFloatSort
	{
		bool operator()(const float &a, const float &b)
		{
			return a > b;
		}
	};

	KnapSack()
	{
		cout << endl
			 << "Enter the Bag Size:";
		cin >> bagSize;
		cout << endl
			 << "\nEnter the no of products: ";
		cin >> productSize;
		fillProducts(productSize);
		displayProducts();
		fillRatios();
		temp_ratios = ratios;
		sort(temp_ratios.begin(), temp_ratios.end(), DescendingFloatSort());
	}

	// Function to get product details from user
	void fillProducts(int size)
	{
		cout << endl
			 << "\nEnter the products to be inserted into bag" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << endl
				 << "Enter the name of the product: " << endl;
			cin >> name;
			cout << endl
				 << "Enter the weight of the product: " << endl;
			cin >> weight;
			cout << endl
				 << "Enter the profit of the product: " << endl;
			cin >> profit;
			ProductDetails[name][weight] = profit;
		}
	}

	// Function to fill the ratios in a vector
	// from provided product details
	void fillRatios()
	{
		for (map<string, map<int, int> >::iterator itr = ProductDetails.begin(); itr != ProductDetails.end(); itr++)
		{
			map<int, int> proWeight = itr->second;
			map<int, int>::iterator proItr = proWeight.begin();
			weight = proItr->first;
			profit = proItr->second;
			ratio = profit / weight;
			ratios.push_back(ratio);
		}
	}

	// Function to display the products
	void displayProducts()
	{
		cout << endl
			 << "\nProducts present are: " << endl;
		cout << endl
			 << setw(18) << "Product-Name" << setw(18) << "Product-Weight" << setw(18) << "Product-Profit";
		for (map<string, map<int, int> >::iterator itr = ProductDetails.begin(); itr != ProductDetails.end(); itr++)
		{
			map<int, int> proWeight = itr->second;
			map<int, int>::iterator proItr = proWeight.begin();
			weight = proItr->first;
			profit = proItr->second;
			cout << endl
				 << setw(16) << itr->first << setw(16) << weight << setw(16) << profit;
		}
	}

	// Function to the find the product using the ratio
	map<string, map<int, int> > findProduct(float ratioParams)
	{
		map<string, map<int, int> > resultProduct;
		map<string, map<int, int> >::iterator itr = ProductDetails.begin();
		float r = 0.0, w = 0.0, p = 0.0;
		while (itr != ProductDetails.end())
		{
			map<int, int> proDetails = itr->second;
			map<int, int>::iterator prodItr = proDetails.begin();
			w = prodItr->first;
			p = prodItr->second;
			r = p / w;
			if (ratioParams == r)
			{
				resultProduct[itr->first] = itr->second;
				break;
			}
			itr++;
		}
		return resultProduct;
	}

	// Logical function to calculate KnapSack Function
	void KS_Logic()
	{
		int tmpBagSz = bagSize, noItems = 0;
		while (tmpBagSz != 0)
		{
			ratio = temp_ratios.front();
			map<string, map<int, int> > product = findProduct(ratio);
			map<string, map<int, int> >::iterator proItr = product.begin();
			map<int, int>::iterator proWItr = (proItr->second).begin();
			weight = proWItr->first;
			if (weight > tmpBagSz)
			{
				noItems = tmpBagSz;
			}
			else
			{
				noItems = weight;
			}
			Bag[proItr->first][noItems] = ratio;
			temp_ratios.erase(temp_ratios.begin());
			tmpBagSz -= noItems;
		}
	}

	// Function to display the knapsack result
	void displayKnapSack()
	{
		string noItemStr = "", itemProStr = "", optSolStr = "";
		int noItems = 0;
		float ratio = 0.0, itemProfit = 0.0, totalProfit = 0.0, optimalSol = 0.0;
		cout << endl
			 << "\nKnackSack solution for the problem is:\n"
			 << endl;
		map<string, map<int, float> >::iterator itr = Bag.begin();
		while (itr != Bag.end())
		{
			string nameP = itr->first;
			map<string, map<int, int> >::iterator prodItr = ProductDetails.find(nameP);
			map<int, int>::iterator proWItr = (prodItr->second).begin();
			map<int, float>::iterator itemsRItr = (itr->second).begin();
			noItems = itemsRItr->first;
			ratio = itemsRItr->second;
			itemProfit = noItems * ratio;
			totalProfit += itemProfit;
			optimalSol = (float)noItems / (float)proWItr->first;
			cout << "\nProduct " << nameP << " is taken with "<< noItems << " no of items having a profit of " << itemProfit << " (Optimal Solution: " << optimalSol << ")";
			itr++;
		}
		cout << "\nTotal profit calculates to: " << totalProfit;
	}
};

int main()
{

	KnapSack ks;
	ks.KS_Logic();
	ks.displayKnapSack();

	return 0;
}
