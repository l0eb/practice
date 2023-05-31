#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;
const int MAX = 100000;

// define graph and visited bool
vector<int> graph[MAX];
bool visited[MAX];

// dfs function
void dfs(int node)
{
    stack<int> s; // define stack
    s.push(node); // push node in stack

    while (!s.empty())
    {
        int current_node = s.top(); // current node set to top of stack

        if (!visited[current_node])
        {
            visited[current_node] = true;

            s.pop();
            cout << current_node << " ";

#pragma omp parallel for
            // loop for i is less that graph size at that current node
            for (int i = 0; i < graph[current_node].size(); i++)
            {
                // set adjecent node to children of current node
                int adjecent_node = graph[current_node][i];
                if (!visited[adjecent_node])
                {
                    // push univisted adjecent node in stack
                    s.push(adjecent_node);
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
        // for graph u , pushback v and for graph v, pushback u
        graph[u].push_back(v);
        graph[v].push_back(u);
        // u->v and v-> u
    }

#pragma omp parallel for
    for (int i = 0; i < nodes; i++)
    {
        visited[i] = false;
    }
    dfs(start_node);
    return 0;
}