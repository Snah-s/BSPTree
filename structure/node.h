#ifndef NODE_H
#define NODE_H

#include "polygon.h"
#include <iostream>

struct BSPTreeNode {
  float A, B, C, D;

  std::vector<Polygon> polygons;
  BSPTreeNode *front; 
  BSPTreeNode *back;

  BSPTreeNode(float a, float b, float c, float d): A(a), B(b), C(c), D(d), front(nullptr), back(nullptr){}

  void insert(const Polygon& polygon) {
    if (polygon.isCoplanar(A, B, C, D)) {
      polygons.push_back(polygon);
    } else if (polygon.isFrontOf(A, B, C, D)) {
      if (front) {
        front->insert(polygon);
      } else {
        float a, b, c, d;
        polygon.getPlaneEquation(a, b, c, d);
        front = new BSPTreeNode(a, b, c, d);
        front->polygons.push_back(polygon);
      }
    } else if (polygon.isBackOf(A, B, C, D)) {
      if (back) {
        back->insert(polygon);
      } else {
        float a, b, c, d;
        polygon.getPlaneEquation(a, b, c, d);
        back = new BSPTreeNode(a, b, c, d);
        back->polygons.push_back(polygon);
      }
    } else {
      Polygon frontPart, backPart;
      polygon.divide(A, B, C, D, frontPart, backPart);
      if (!frontPart.vertex.empty()) {
        if (front) {
          front->insert(frontPart);
        } else {
          float a, b, c, d;
          frontPart.getPlaneEquation(a, b, c, d);
          front = new BSPTreeNode(a, b, c, d);
          front->polygons.push_back(frontPart);
        }
      }
      if (!backPart.vertex.empty()) {
        if (back) {
          back->insert(backPart);
        } else {
          float a, b, c, d;
          backPart.getPlaneEquation(a, b, c, d);
          back = new BSPTreeNode(a, b, c, d);
          back->polygons.push_back(backPart);
        }
      }
    }
  }

  bool intersects(const Polygon& polygon) const {
    for (const Polygon& p : polygons) {
      if (polygon.intersects(p)) {
        std::cout << "Intersection found at node with plane: " << A << "x + " << B << "y + " << C << "z + " << D << " = 0"<<std::endl;
        return true;
      }
    }

    if (polygon.isFrontOf(A, B, C, D)) {
      if (front) {
        return front->intersects(polygon);
      } else {
        return false;
      }
    } else if (polygon.isBackOf(A, B, C, D)) {
      if (back) {
        return back->intersects(polygon);
      } else {
        return false;
      }
    } else {
      Polygon frontPart, backPart;
      polygon.divide(A, B, C, D, frontPart, backPart);

      bool intersectsFront = false;
      if (!frontPart.vertex.empty()) {
        if (front) {
          intersectsFront = front->intersects(frontPart);
        }
      }

      bool intersectsBack = false;
      if (!backPart.vertex.empty()) {
        if (back) {
          intersectsBack = back->intersects(backPart);
        }
      }

      return intersectsFront || intersectsBack;
    }
  }

};

#endif // !NODE_H
