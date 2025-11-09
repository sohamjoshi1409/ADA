#include <iostream>
#include <vector>
using namespace std;

bool findHamiltonianPath(const vector<vector<int>> &graph, vector<int> &path, vector<int> &visited, int pos, int n)
{
    // Base case: all vertices are visited and last connects to first
    if (pos == n)
    {
        if (graph[path[pos - 1]][path[0]] == 1)
        {
            path.push_back(path[0]); // complete the cycle
            return true;
        }
        return false;
    }

    // Try next vertices
    for (int v = 1; v < n; ++v)
    {
        if (!visited[v] && graph[path[pos - 1]][v] == 1)
        {
            visited[v] = 1;
            path.push_back(v);

            if (findHamiltonianPath(graph, path, visited, pos + 1, n))
                return true; // found cycle

            // Backtrack
            visited[v] = 0;
            path.pop_back();
        }
    }

    return false;
}

int main()
{
    // Example graph (adjacency matrix)
    vector<vector<int>> graph = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}};

    int n = graph.size();

    vector<int> path;          // to store path
    vector<int> visited(n, 0); // visited array

    // Start from vertex 0
    path.push_back(0);
    visited[0] = 1;

    if (findHamiltonianPath(graph, path, visited, 1, n))
    {
        cout << "Hamiltonian Cycle found: ";
        for (int v : path)
            cout << v << " ";
        cout << endl;
    }
    else
    {
        cout << "No Hamiltonian Cycle exists." << endl;
    }

    return 0;
}
