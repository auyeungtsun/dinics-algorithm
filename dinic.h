#ifndef DINIC_H
#define DINIC_H

#include <vector>
#include <queue>
#include <limits>

const int INF = 1e9;

class Dinic {
public:
    struct Edge {
        int to;
        int cap;
        int flow;
        int rev;
    };

    Dinic(int n);
    void add_edge(int from, int to, int cap);
    int dinic(int s, int t);

    std::vector<bool> getReachableNodes(int source);
private:
    int n;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> level;
    std::vector<int> ptr;
    bool bfs(int s, int t);
    int dfs(int u, int pushed, int t);
};

#endif