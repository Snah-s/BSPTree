#ifndef BSPTREE_H
#define BSPTREE_H

#include "node.h"

class BSPTree{
private:
  BSPTreeNode *root;

  BSPTreeNode* buildBSPTree(std::vector<Polygon>& polygons){
    if (polygons.empty()) return nullptr;

    Polygon partition = polygons[0];

    float A, B, C, D;
    partition.getPlaneEquation(A, B, C, D);

    BSPTreeNode* node = new BSPTreeNode(A, B, C, D);

    node->polygons.push_back(partition);

    std::vector<Polygon> frontPolygons;
    std::vector<Polygon> backPolygons;

    for (size_t i = 1; i < polygons.size(); ++i){
      const Polygon& polygon = polygons[i];

      if (polygon.isCoplanar(A, B, C, D)) {
        node->polygons.push_back(polygon);
      } else if (polygon.isFrontOf(A, B, C, D)){
        frontPolygons.push_back(polygon);
      } else if (polygon.isBackOf(A, B, C, D)){
        backPolygons.push_back(polygon);
      } else {
        Polygon front, back;
        polygon.divide(A, B, C, D, front, back);
        if (!front.vertex.empty()) {
          frontPolygons.push_back(front);
        }
        if (!back.vertex.empty()) {
          backPolygons.push_back(back);
        }
      }
    }

    node->front = buildBSPTree(frontPolygons);
    node->back = buildBSPTree(backPolygons);

    return node;
  }

  void deleteTree(BSPTreeNode* node){
    if (node){
      deleteTree(node->front);
      deleteTree(node->back);
      delete node;
    }
  }

public:
  BSPTree() : root(nullptr) {}

  BSPTree(const std::vector<Polygon>& polygons){
    std::vector<Polygon> polygonsCopy = polygons;
    root = buildBSPTree(polygonsCopy);
  }

  ~BSPTree(){
    deleteTree(root);
  }

  void insertPolygon(const Polygon& polygon){
    if (root) {
      root->insert(polygon);
    } else {
      float A, B, C, D;
      polygon.getPlaneEquation(A, B, C, D);
      root = new BSPTreeNode(A, B, C, D);
      root->polygons.push_back(polygon);
    }
  }

  bool intersects(const Polygon& polygon) const {
    if (root) {
      return root->intersects(polygon);
    } else {
      return false;
    }
  }
};

#endif // !BSPTREE_H
