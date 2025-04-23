#include <vector>
#include <queue>
#include "dinic.h"
#include <algorithm>

using namespace std;

/**
 * @brief Constructor for the Dinic class.
 * 
 * @param n The number of vertices in the flow network.
 * @note Initializes the adjacency list, level array, and pointer array.
 * `adj`: The adjacency list representing the flow network.
 *         Each element `adj[u]` is a list of edges outgoing from vertex `u`.
 * `level`: Stores the level of each vertex in the layered network constructed by BFS.
 * `ptr`: Stores the current edge index in the adjacency list for each vertex during DFS.
 */
Dinic::Dinic(int n) : adj(n), level(n), ptr(n) {
    this->n = n;
}

/**
 * @brief Adds an edge to the flow network.
 * 
 * @param u The source vertex of the edge.
 * @param v The destination vertex of the edge.
 * @param cap The capacity of the edge.
 * @note Adds a forward edge from u to v with the given capacity and a backward edge from v to u with zero capacity.
 */
void Dinic::add_edge(int u, int v, int cap) {
    adj[u].push_back({v, cap, 0, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
}

bool Dinic::bfs(int s, int t) {
    level.assign(adj.size(), -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge& e : adj[u]) {
            if (e.cap - e.flow > 0 && level[e.to] == -1) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] != -1;
}

int Dinic::dfs(int u, int pushed, int t) {
    if (pushed == 0 || u == t) return pushed;
    for (int& cid = ptr[u]; cid < adj[u].size(); cid++) {
        Edge& e = adj[u][cid];
        if (level[u] + 1 != level[e.to] || e.cap - e.flow == 0) continue;
        int tr = dfs(e.to, min(pushed, e.cap - e.flow), t);
        if (tr == 0) continue;
        e.flow += tr;
        adj[e.to][e.rev].flow -= tr;
        return tr;
    }
    return 0;
}

/**
 * @brief Calculates the maximum flow in a flow network using Dinic's algorithm.
 * It utilizes BFS to build a layered network and DFS to push flow through the network.
 * 
 * @param s The source vertex.
 * @param t The sink vertex.
 * @return The maximum flow from s to t.
 * @note Time complexity: O(V^2 * E) in the worst case, but often faster in practice.
 * @note Space complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 */
int Dinic::dinic(int s, int t) {
    int f = 0;
    while (bfs(s, t)) {
        ptr.assign(adj.size(), 0);
        while (int pushed = dfs(s, INF, t)) {
            f += pushed;
        }
    }
    return f;
}

/**
 * @brief Performs a breadth-first search to find all nodes reachable from a given source in the residual graph.
 * 
 * @param source The source vertex to start the BFS from.
 * @return A vector of booleans where each element represents whether the corresponding node is reachable from the source.
 * @note This function is used to find the minimum cut after the max flow has been computed.
 *       Nodes that are reachable from the source in the residual graph are part of one side of the min cut.
 */
std::vector<bool> Dinic::getReachableNodes(int source) {
    std::vector<bool> visited(n, false);
    std::vector<int> q;
    q.push_back(source);
    visited[source] = true;
    int head = 0;
    while(head < q.size()){
      int u = q[head++];
      for(auto& edge : adj[u]){
        if(edge.flow < edge.cap && !visited[edge.to]){
          visited[edge.to] = true;
          q.push_back(edge.to);
        }
      }
    }
    return visited;
}