#include <iostream>
#include "BSPTree.h"

void testBSPTreeConstruction() {
  std::vector<Polygon> polygons = {
    Polygon({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}),
    Polygon({{0, 0, 1}, {1, 0, 1}, {0, 1, 1}}),
    Polygon({{0, 0, 2}, {1, 0, 2}, {0, 1, 2}})
  };

  BSPTree tree(polygons);
  if(tree.intersects(polygons[0]) == true) std::cout << "Nodo pertenece al BSP Tree" << std::endl;
  if(tree.intersects(polygons[1]) == true) std::cout << "Nodo pertenece al BSP Tree" << std::endl;
  if(tree.intersects(polygons[2]) == true) std::cout << "Nodo pertenece al BSP Tree" << std::endl;

  std::cout<<std::endl;
}

void testBSPTreeInsertPolygon() {
  BSPTree tree;
  Polygon polygon({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}});
  tree.insertPolygon(polygon);

  if (tree.intersects(polygon) == true) std::cout << "Nodo insertado correctamente" << std::endl;

    std::cout<<std::endl;
}

void testBSPTreeIntersects() {
  std::vector<Polygon> polygons = {
    Polygon({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}),
    Polygon({{0, 0, 1}, {1, 0, 1}, {0, 1, 1}})
  };

  BSPTree tree(polygons);
  Polygon testPolygon({{0, 0, 0.5}, {1, 0, 0.5}, {0, 1, 0.5}});
  if (!tree.intersects(testPolygon)) std::cout << "Intersección no encontrada" << std::endl;

  Polygon nonIntersectingPolygon({{2, 2, 2}, {3, 2, 2}, {2, 3, 2}});
  if (!tree.intersects(nonIntersectingPolygon)) std::cout << "Intersección no encontrada" << std::endl;
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