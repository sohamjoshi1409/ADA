#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// tsp function returns minimum cost to visit all cities starting from 'current'
// mask indicates which cities are visited
int tsp(int current, int mask, const vector<vector<int>> &dist, vector<vector<int>> &dp, vector<vector<int>> &parent)
{
    int n = dist.size();
    if (mask == (1 << n) - 1)
    {
        return dist[current][0]; // return to start
    }

    if (dp[current][mask] != -1)
        return dp[current][mask];

    int ans = INT_MAX;
    int bestNext = -1;

    for (int city = 0; city < n; city++)
    {
        if ((mask & (1 << city)) == 0)
        { // city not visited
            int newAns = dist[current][city] + tsp(city, mask | (1 << city), dist, dp, parent);
            if (newAns < ans)
            {
                ans = newAns;
                bestNext = city;
            }
        }
    }
    parent[current][mask] = bestNext; // store best city to go next
    return dp[current][mask] = ans;
}

// Reconstruct path from parent array
vector<int> getPath(const vector<vector<int>> &parent, int n)
{
    vector<int> path;
    int mask = 1;
    int current = 0;

    for (int i = 0; i < n; i++)
    {
        path.push_back(current);
        current = parent[current][mask];
        mask |= (1 << current);
    }
    path.push_back(0); // return to start
    return path;
}

int main()
{
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}};
    int n = dist.size();
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));
    vector<vector<int>> parent(n, vector<int>(1 << n, -1));

    int result = tsp(0, 1, dist, dp, parent);

    cout << "Minimum cost: " << result << "\n";

    vector<int> path = getPath(parent, n);
    cout << "Path: ";
    for (int city : path)
    {
        cout << city << " ";
    }
    cout << "\n";

    return 0;
}
