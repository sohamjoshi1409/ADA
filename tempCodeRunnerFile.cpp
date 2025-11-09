for (auto &[v, w] : adj[u])
        {
            if (!inMST[v] && w < key[v])
            {
                key[v] = w;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }