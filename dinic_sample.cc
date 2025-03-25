#include "dinic.h"
#include <iostream>

int main() {
    Dinic dinic(6); 
    dinic.add_edge(0, 1, 16);
    dinic.add_edge(0, 2, 13);
    dinic.add_edge(1, 2, 10);
    dinic.add_edge(1, 3, 12);
    dinic.add_edge(2, 1, 4);
    dinic.add_edge(2, 4, 14);
    dinic.add_edge(3, 2, 9);
    dinic.add_edge(3, 5, 20);
    dinic.add_edge(4, 3, 7);
    dinic.add_edge(4, 5, 4);

    int max_flow = dinic.dinic(0, 5);
    std::cout << "Maximum flow: " << max_flow << std::endl;

    return 0;
}