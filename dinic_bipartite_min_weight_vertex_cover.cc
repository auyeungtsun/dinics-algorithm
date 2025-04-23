#include <iostream>
#include <vector>
#include <algorithm>
#include "dinic.h"
#include <cassert>
#include <set>

using namespace std;

/**
 * @brief Computes the minimum weight vertex cover in a bipartite graph.
 * 
 * This function takes a bipartite graph represented by two sets of nodes (left and right partitions)
 * and the weights associated with each node. It then computes the minimum weight vertex cover using 
 * the maximum flow algorithm (Dinic's algorithm) on a transformed flow network.
 * 
 * @param n1 The number of nodes in the left partition.
 * @param weights1 The weights of the nodes in the left partition.
 * @param n2 The number of nodes in the right partition.
 * @param weights2 The weights of the nodes in the right partition.
 * @param edges A vector of pairs representing the edges between the left and right partitions.
 *              Each pair (u, v) represents an edge from node u in the left partition to node v in the right partition.
 * @return A pair of vectors representing the minimum weight vertex cover. The first vector contains the nodes from the left partition, and the second vector contains the nodes from the right partition.
 */
pair<vector<int>, vector<int>> bipartiteMinWeightVertexCover(int n1, const vector<int>& weights1, int n2, const vector<int>& weights2, const vector<pair<int, int>>& edges) {
    pair<vector<int>, vector<int>> result;
    int n = n1 + n2 + 2; // Total number of nodes in the flow network, including source and sink
    int source = n - 2; // Source node
    int sink = n - 1;   // Sink node

    Dinic dinic(n);

    for (int i = 0; i < n1; ++i) {
        dinic.add_edge(source, i, weights1[i]);
    }

    for (int i = 0; i < n2; ++i) {
        dinic.add_edge(n1 + i, sink, weights2[i]);
    }

    for (const auto& edge : edges) {
        dinic.add_edge(edge.first, n1 + edge.second, INF);
    }

    dinic.dinic(source, sink);

    vector<bool> visited = dinic.getReachableNodes(source);
    for(int i=0;i<n1;++i) if(!visited[i]) result.first.push_back(i);
    for(int i=0;i<n2;++i) if(visited[n1+i]) result.second.push_back(i);
    return result;
}

pair<set<int>, set<int>> toSetPair(const pair<vector<int>, vector<int>>& vecPair) {
    return {
        set<int>(vecPair.first.begin(), vecPair.first.end()),
        set<int>(vecPair.second.begin(), vecPair.second.end())
    };
}

void testBipartiteMinWeightVertexCover() {
    cout << "Running bipartiteMinWeightVertexCover tests..." << endl;

    // Test Case 1: Empty graph
    {
        cout << "  Test Case 1: Empty graph..." << flush;
        int n1 = 0, n2 = 0;
        vector<int> w1 = {}, w2 = {};
        vector<pair<int, int>> edges = {};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
        auto expected_result = toSetPair({{},{}});
        assert(toSetPair(result) == expected_result);
        cout << " Passed." << endl;
    }

    // Test Case 2: No edges
    {
        cout << "  Test Case 2: No edges..." << flush;
        int n1 = 2, n2 = 3;
        vector<int> w1 = {10, 20}, w2 = {5, 15, 25};
        vector<pair<int, int>> edges = {};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
         auto expected_result = toSetPair({{},{}});
        assert(toSetPair(result) == expected_result);
        cout << " Passed." << endl;
    }

    // Test Case 3: Single edge, weight on L smaller
    {
        cout << "  Test Case 3: Single edge (L cheaper)..." << flush;
        int n1 = 1, n2 = 1;
        vector<int> w1 = {5}, w2 = {10};
        vector<pair<int, int>> edges = {{0, 0}};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
        auto expected_result = toSetPair({{0},{}});
        assert(toSetPair(result) == expected_result);
        cout << " Passed." << endl;
    }

    // Test Case 4: Single edge, weight on R smaller
    {
        cout << "  Test Case 4: Single edge (R cheaper)..." << flush;
        int n1 = 1, n2 = 1;
        vector<int> w1 = {10}, w2 = {5};
        vector<pair<int, int>> edges = {{0, 0}};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
        auto expected_result = toSetPair({{},{0}});
        assert(toSetPair(result) == expected_result);
        cout << " Passed." << endl;
    }

     // Test Case 5: Single edge, equal weights
    {
        cout << "  Test Case 5: Single edge (equal weights)..." << flush;
        int n1 = 1, n2 = 1;
        vector<int> w1 = {10}, w2 = {10};
        vector<pair<int, int>> edges = {{0, 0}};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
        auto expected_result = toSetPair({{0}, {}});
        assert(toSetPair(result) == expected_result);
        cout << " Passed." << endl;
    }

    // Test Case 6: K(2,2), specific weights
    {
        cout << "  Test Case 6: K(2,2) specific weights..." << flush;
        int n1 = 2, n2 = 2;
        vector<int> w1 = {10, 1};
        vector<int> w2 = {2, 12};
        vector<pair<int, int>> edges = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
        auto expected_result = toSetPair({{0, 1}, {}});
        assert(toSetPair(result) == expected_result);
        cout << " Passed." << endl;
    }

    // Test Case 7: K(2,2), different weights favouring R partition
    {
        std::cout << "  Test Case 7: K(2,2) different weights..." << std::flush;
        int n1 = 2, n2 = 2;
        std::vector<int> w1 = {10, 20};
        std::vector<int> w2 = {5, 5};
        std::vector<std::pair<int, int>> edges = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
        auto expected_result = toSetPair({{}, {0, 1}});
        assert(toSetPair(result) == expected_result);
        std::cout << " Passed." << std::endl;
    }

    // Test Case 8: More complex graph
    {
        std::cout << "  Test Case 8: Complex graph..." << std::flush;
        int n1 = 3, n2 = 2;
        std::vector<int> w1 = {5, 10, 3};
        std::vector<int> w2 = {8, 6};
        std::vector<std::pair<int, int>> edges = {{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}};
        auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
        auto expected_result = toSetPair({{0, 2}, {1}});
        assert(toSetPair(result) == expected_result);
        std::cout << " Passed." << std::endl;
    }


    cout << "All bipartiteMinWeightVertexCover tests passed!" << endl;
}

void bipartiteMinWeightVertexCoverSample() {
    int n1 = 3, n2 = 2;
    vector<int> w1 = {5, 10, 3};
    vector<int> w2 = {8, 6};
    vector<pair<int, int>> edges = {{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}};
    auto result = bipartiteMinWeightVertexCover(n1, w1, n2, w2, edges);
    cout << "Sample Min Weight Vertex Cover:" << endl;
    cout << "Left Partition: ";
    for (int node : result.first) cout << node << " ";
    cout << endl;
    cout << "Right Partition: ";
    for (int node : result.second) cout << node << " ";
    cout << endl;
}

int main() {
    testBipartiteMinWeightVertexCover();
    bipartiteMinWeightVertexCoverSample();
    return 0;
}