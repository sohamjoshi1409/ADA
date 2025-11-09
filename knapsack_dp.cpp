#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Matrix DP method for 0/1 Knapsack
int knapsack(const vector<int> &weights, const vector<int> &values, int W, vector<int> &selected)
{
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            dp[i][w] = dp[i - 1][w];
            if (weights[i - 1] <= w)
            {
                if (dp[i][w] < dp[i - 1][w - weights[i - 1]] + values[i - 1])
                {
                    dp[i][w] = dp[i - 1][w - weights[i - 1]] + values[i - 1];
                }
            }
        }
    }

    // Backtrack to find selected items
    int w = W;
    for (int i = n; i > 0 && w > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected.push_back(i - 1);
            w -= weights[i - 1];
        }
    }
    reverse(selected.begin(), selected.end()); // Optional: order by input
    return dp[n][W];
}

int main()
{
    vector<int> values = {2, 3, 1, 4};
    vector<int> weights = {3, 4, 6, 5};
    int W = 8;
    vector<int> selected;

    int maxValue = knapsack(weights, values, W, selected);
    cout << "Maximum value in Knapsack: " << maxValue << endl;
    cout << "Selected item indices: ";
    for (int idx : selected)
        cout << idx << " ";
    cout << endl;
    return 0;
}
