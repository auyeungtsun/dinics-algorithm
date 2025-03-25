#include "dinic.h"
#include <cassert>
#include <iostream>
#include <vector>

void test_empty_graph() {
  Dinic dinic(5);
  assert(dinic.dinic(0, 4) == 0);
  std::cout << "test_empty_graph passed" << std::endl;
}

void test_single_edge() {
  Dinic dinic(5);
  dinic.add_edge(0, 1, 10);
  assert(dinic.dinic(0, 1) == 10);
    std::cout << "test_single_edge passed" << std::endl;

}

void test_two_edges() {
  Dinic dinic(5);
  dinic.add_edge(0, 1, 10);
  dinic.add_edge(1, 2, 5);
  assert(dinic.dinic(0, 2) == 5);
    std::cout << "test_two_edges passed" << std::endl;
}

void test_multiple_paths() {
  Dinic dinic(5);
  dinic.add_edge(0, 1, 10);
  dinic.add_edge(0, 2, 5);
  dinic.add_edge(1, 3, 5);
  dinic.add_edge(2, 3, 5);
  assert(dinic.dinic(0, 3) == 10);
    std::cout << "test_multiple_paths passed" << std::endl;

}

void test_larger_network() {
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
    assert(dinic.dinic(0, 5) == 23);
        std::cout << "test_larger_network passed" << std::endl;

}
void test_disconnected(){
    Dinic dinic(4);
    dinic.add_edge(0,1, 10);
    dinic.add_edge(2,3,5);
    assert(dinic.dinic(0,3) == 0);
        std::cout << "test_disconnected passed" << std::endl;
}
int main() {
  test_empty_graph();
  test_single_edge();
  test_two_edges();
  test_multiple_paths();
  test_larger_network();
  test_disconnected();
  return 0;
}