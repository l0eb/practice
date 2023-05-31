#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;
const int MAX = 100000;

// define graph and visited bool
vector<int> graph[MAX];
bool visited[MAX];

// bfs function
void bfs(int node)
{
    queue<int> q;         // define queue
    q.push(node);         // enqueue the starting node
    visited[node] = true; // mark the starting node as visited

    while (!q.empty())
    {
        int current_node;
#pragma omp critical
        {
            current_node = q.front(); // get the front of the queue
            q.pop();                  // dequeue the current node
        }

        cout << current_node << " ";

#pragma omp parallel for
        for (int i = 0; i < graph[current_node].size(); i++)
        {
            int adjacent_node = graph[current_node][i];
#pragma omp critical
            {
                if (!visited[adjacent_node])
                {
                    visited[adjacent_node] = true; // mark the adjacent node as visited
                    q.push(adjacent_node);         // enqueue the adjacent node
                }
            }
        }
    }
}

int main()
{
    int nodes, edges, start_node;
    cout << "[Enter Number of Nodes] [Number of edges] [starting node of graph]\n";
    cin >> nodes >> edges >> start_node;
    cout << "enter pair of nodes and edges\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        // for graph u, push back v and for graph v, push back u
        graph[u].push_back(v);
        graph[v].push_back(u);
        // u->v and v->u
    }

#pragma omp parallel for
    for (int i = 0; i < nodes; i++)
    {
        visited[i] = false;
    }
    bfs(start_node);
    return 0;
}
