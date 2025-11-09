#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

class DisjointSet
{
    vector<int> parent, rank;

public:
    DisjointSet(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int u)
    {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }
    bool unionSets(int u, int v)
    {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u == root_v)
            return false;
        if (rank[root_u] < rank[root_v])
            parent[root_u] = root_v;
        else if (rank[root_u] > rank[root_v])
            parent[root_v] = root_u;
        else
        {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
        return true;
    }
};

int main()
{
    int n = 4; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    sort(edges.begin(), edges.end());
    DisjointSet ds(n);
    vector<Edge> mst;
    int total_weight = 0;
    for (const auto &e : edges)
    {
        if (ds.unionSets(e.u, e.v))
        {
            mst.push_back(e);
            total_weight += e.weight;
        }
    }
    cout << "Edges in MST:\n";
    for (const auto &e : mst)
    {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }
    cout << "Total Weight: " << total_weight << endl;
    return 0;
}
