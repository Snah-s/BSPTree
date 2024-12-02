#include <cassert>
#include <iostream>
#include "BSPTree.h"

void testBSPTreeConstruction() {
  std::vector<Polygon> polygons = {
    Polygon({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}),
    Polygon({{0, 0, 1}, {1, 0, 1}, {0, 1, 1}}),
    Polygon({{0, 0, 2}, {1, 0, 2}, {0, 1, 2}})
  };

  BSPTree tree(polygons);
  assert(tree.intersects(polygons[0]) == true);
  assert(tree.intersects(polygons[1]) == true);
  assert(tree.intersects(polygons[2]) == true);

  std::cout << "testBSPTreeConstruction passed!" << std::endl;
}

void testBSPTreeInsertPolygon() {
  BSPTree tree;
  Polygon polygon({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}});
  tree.insertPolygon(polygon);

  assert(tree.intersects(polygon) == true);

  std::cout << "testBSPTreeInsertPolygon passed!" << std::endl;
}

void testBSPTreeIntersects() {
  std::vector<Polygon> polygons = {
    Polygon({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}),
    Polygon({{0, 0, 1}, {1, 0, 1}, {0, 1, 1}})
  };

  BSPTree tree(polygons);
  Polygon testPolygon({{0, 0, 0.5}, {1, 0, 0.5}, {0, 1, 0.5}});
  assert(tree.intersects(testPolygon) == true);

  Polygon nonIntersectingPolygon({{2, 2, 2}, {3, 2, 2}, {2, 3, 2}});
  assert(tree.intersects(nonIntersectingPolygon) == false);

  std::cout << "testBSPTreeIntersects passed!" << std::endl;
}

void runAllTests() {
  testBSPTreeConstruction();
  testBSPTreeInsertPolygon();
  testBSPTreeIntersects();
}

int main() {
  runAllTests();

  return 0;
}