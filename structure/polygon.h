#ifndef POLYGON_H
#define POLYGON_H

#include "R3.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

struct Polygon{
  std::vector<R3> vertex;

  static constexpr float EPSILON = 1e-6f;

  Polygon(){}
  Polygon(const std::vector<R3>& vertex): vertex(vertex){}

  void getPlaneEquation(float &A, float &B, float &C, float &D) const {
    R3 n = normal();
    if (n.magnitude() == 0) {
      A = B = C = D = 0;
      return;
    }
    A = n.x;
    B = n.y;
    C = n.z;
    D = -n.dot(vertex[0]);
  }

  bool isFrontOf(float A, float B, float C, float D) const {
    for (const auto& v : vertex){
      float distance = A*v.x + B*v.y + C*v.z + D;
      if (distance < -EPSILON){
        return false;
      }
    }
    return true;
  }

  bool isBackOf(float A, float B, float C, float D) const {
    for (const auto& v : vertex){
      float distance = A*v.x + B*v.y + C*v.z + D;
      if (distance > EPSILON){
        return false;
      }
    }
    return true;
  }

  bool isCoplanar(float A, float B, float C, float D) const {
    for (const auto& v : vertex){
      float distance = A*v.x + B*v.y + C*v.z + D;
      if (std::fabs(distance) > EPSILON){
        return false;
      }
    }
    return true;
  }

  void divide(float A, float B, float C, float D, Polygon &front, Polygon &back) const {
    std::vector<R3> frontVertex;
    std::vector<R3> backVertex;

    for (size_t i = 0; i < vertex.size(); i++){
      const R3& v1 = vertex[i];
      const R3& v2 = vertex[(i+1)%vertex.size()];
      float d1 = A*v1.x + B*v1.y + C*v1.z + D;
      float d2 = A*v2.x + B*v2.y + C*v2.z + D;

      if (d1 >= -EPSILON) frontVertex.push_back(v1);
      if (d1 <= EPSILON) backVertex.push_back(v1);

      if ((d1 > EPSILON && d2 < -EPSILON) || (d1 < -EPSILON && d2 > EPSILON)){
        float t = d1 / (d1 - d2);
        R3 intersection = {v1.x + t*(v2.x - v1.x), v1.y + t*(v2.y - v1.y), v1.z + t*(v2.z - v1.z)};
        frontVertex.push_back(intersection);
        backVertex.push_back(intersection);
      }
    }
    front = Polygon(frontVertex);
    back = Polygon(backVertex);
  }

  R3 normal() const {
    if (vertex.size() < 3) return R3();
    R3 v1 = vertex[1] - vertex[0];
    R3 v2 = vertex[2] - vertex[0];
    return (v1*v2).normalize();
  }

  bool isInside(const R3& point) const {
    R3 n = normal();
    for (size_t i = 0; i < vertex.size(); i++){
      const R3& v1 = vertex[i];
      const R3& v2 = vertex[(i+1)%vertex.size()];
      R3 edge = v2 - v1;
      R3 toPoint = point - v1;
      if (n.dot(edge*toPoint) < -EPSILON) return false;
    }
    return true;
  }

  bool intersects(const Polygon &other) const {
    std::vector<R3> axes;

    auto getAxes = [](const std::vector<R3>& vertices, std::vector<R3>& axes) {
      size_t numVertices = vertices.size();
      for (size_t i = 0; i < numVertices; ++i) {
        R3 edge = vertices[(i + 1) % numVertices] - vertices[i];
        R3 axis = edge * R3(0, 0, 1);
        axis = axis.normalize();
        axes.push_back(axis);
      }
    };

    getAxes(vertex, axes);
    getAxes(other.vertex, axes);

    for (const R3& axis : axes) {
      float minA = INFINITY, maxA = -INFINITY;
      float minB = INFINITY, maxB = -INFINITY;

      for (const R3& v : vertex) {
        float projection = axis.dot(v);
        minA = std::min(minA, projection);
        maxA = std::max(maxA, projection);
      }

      for (const R3& v : other.vertex) {
        float projection = axis.dot(v);
        minB = std::min(minB, projection);
        maxB = std::max(maxB, projection);
      }

      if (maxA < minB || maxB < minA) {
        return false;
      }
    }

    return true;
  }
};

#endif // !POLYGON_H
