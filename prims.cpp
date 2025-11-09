#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Edge structure: (from, to, weight)
struct Edge
{
    int u, v, w;
};

const int INF = 1e9;

void primMST(int n, const vector<Edge> &edges)
{
    // Build adjacency list from edge list
    vector<vector<pair<int, int>>> adj(n);
    for (const auto &e : edges)
    {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }

    vector<int> key(n, INF);      // Minimum weight to connect
    vector<bool> inMST(n, false); // Included in MST
    vector<int> parent(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0}); // (weight, vertex)

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;
        inMST[u] = true;

        for (auto &[v, w] : adj[u])
        {
            if (!inMST[v] && w < key[v])
            {
                key[v] = w;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "Edge \tWeight\n";
    for (int i = 1; i < n; ++i)
        cout << parent[i] << " - " << i << "\t" << key[i] << endl;
}

int main()
{
    int n = 5;
    vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}};

    primMST(n, edges);

    return 0;
}
