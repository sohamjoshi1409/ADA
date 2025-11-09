#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> values = {60, 100, 120};
vector<int> weights = {10, 20, 30};

bool cmp(int a, int b)
{
    double r1 = (double)values[a] / weights[a];
    double r2 = (double)values[b] / weights[b];
    return r1 > r2;
}

int main()
{
    int capacity = 50;
    int n = values.size();

    vector<int> idx(n);
    for (int i = 0; i < n; i++)
        idx[i] = i;

    // Sort items by value/weight ratio
    sort(idx.begin(), idx.end(), cmp);

    double totalValue = 0.0;
    int remainingCapacity = capacity;

    cout << "Knapsack capacity = " << capacity << endl;
    cout << "Items taken (value, weight):\n";

    for (int i = 0; i < n; i++)
    {
        int j = idx[i];
        if (weights[j] <= remainingCapacity)
        {
            cout << "Take full item (value = " << values[j]
                 << ", weight = " << weights[j] << ")\n";

            totalValue += values[j];
            remainingCapacity -= weights[j];
        }
        else
        {
            double fraction = (double)remainingCapacity / weights[j];
            double fractionValue = values[j] * fraction;

            cout << "Take " << fraction * 100 << "% of item (value = " << values[j]
                 << ", weight = " << weights[j] << ") -> Added value = " << fractionValue << "\n";

            totalValue += fractionValue;
            remainingCapacity = 0;
            break;
        }
    }

    cout << "------------------------------------------------------------------------\n";
    cout << "Maximum value in Knapsack = " << totalValue << endl;

    return 0;
}
