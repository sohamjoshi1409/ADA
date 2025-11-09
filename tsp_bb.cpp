#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max() / 4;

// Branch and Bound for TSP (simple lower bound using min outgoing edge)
void tspBranchAndBound(const vector<vector<int>> &cost,
                       vector<int> &path,
                       vector<int> &bestPath,
                       vector<char> &visited,
                       const vector<int> &minEdge,
                       int curr,
                       int visitedCount,
                       int currentCost,
                       int &bestCost,
                       int n)
{
    // If all vertices visited, try to close the tour back to 0
    if (visitedCount == n)
    {
        if (cost[curr][0] < INF) // there is an edge back to start
        {
            int totalCost = currentCost + cost[curr][0];
            if (totalCost < bestCost)
            {
                bestCost = totalCost;
                bestPath = path;
                bestPath.push_back(0); // explicitly close cycle for printing
            }
        }
        return;
    }

    // Compute simple lower bound:
    // currentCost + sum of minEdge for every unvisited vertex
    long long bound = currentCost;
    for (int v = 0; v < n; ++v)
        if (!visited[v])
            bound += minEdge[v];

    // If even the optimistic bound is not better than bestCost, prune
    if (bound >= bestCost)
        return;

    // Try next vertices
    for (int v = 0; v < n; ++v)
    {
        if (!visited[v] && cost[curr][v] < INF)
        {
            visited[v] = 1;
            path.push_back(v);

            tspBranchAndBound(cost, path, bestPath, visited, minEdge,
                              v, visitedCount + 1, currentCost + cost[curr][v], bestCost, n);

            visited[v] = 0;
            path.pop_back();
        }
    }
}

int main()
{
    // Example weighted complete graph (symmetric). 0-based indices.
    // Use INF to represent "no edge" if needed; here we show a complete graph.
    vector<vector<int>> cost = {
        {INF, 10, 15, 20, 25},
        {10, INF, 35, 25, 17},
        {15, 35, INF, 30, 28},
        {20, 25, 30, INF, 22},
        {25, 17, 28, 22, INF}};

    int n = cost.size();

    // Precompute min outgoing cost for each vertex (used in bound)
    vector<int> minEdge(n, INF);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                continue;
            minEdge[i] = min(minEdge[i], cost[i][j]);
        }
        // In a disconnected case, if minEdge[i] stays INF, TSP is impossible
        if (minEdge[i] == INF)
        {
            cout << "Graph is not fully connected; TSP impossible." << endl;
            return 0;
        }
    }

    vector<char> visited(n, 0);
    vector<int> path, bestPath;
    int bestCost = INF;

    // Start from vertex 0
    visited[0] = 1;
    path.push_back(0);

    tspBranchAndBound(cost, path, bestPath, visited, minEdge,
                      0, 1, 0, bestCost, n);

    if (bestCost < INF)
    {
        cout << "Best tour cost: " << bestCost << "\n";
        cout << "Tour (0-based indices): ";
        for (int v : bestPath)
            cout << v << " ";
        cout << endl;
    }
    else
    {
        cout << "No Hamiltonian cycle (complete tour) exists." << endl;
    }

    return 0;
}
