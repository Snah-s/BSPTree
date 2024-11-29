#include <vector>
#include <cmath>
#include <limits>
#include <functional>
#include <tuple>

using Line = std::tuple<double, double, double, double>;

struct Node {
  Line line;
  Node *front;
  Node *back;

  Node(const Line &l, Node *f = nullptr, Node *b = nullptr) : line(l), front(f), back(b) {}
};

class BSPTree {
private:
  Node *root;
public:
  BSPTree(const std::vector<Line> &lines) {
    root = build_tree(lines);
  }

  Node *build_tree(const std::vector<Line> &lines) {
    if (lines.empty()) {
      return nullptr;
    }

    Line line = lines[0];
    std::vector<Line> front_lines;
    std::vector<Line> back_lines;

    for (size_t i = 1; i < lines.size(); ++i) {
      if (is_front(line, lines[i])) {
        front_lines.push_back(lines[i]);
      }
      else {
        back_lines.push_back(lines[i]);
      }
    }

    return new Node(
        line,
        build_tree(front_lines),
        build_tree(back_lines));
  }

  bool is_front(const Line &line, const Line &other) {
    double x1, y1, x2, y2;
    double ox1, oy1, ox2, oy2;
    std::tie(x1, y1, x2, y2) = line;
    std::tie(ox1, oy1, ox2, oy2) = other;

    // Punto medio de la otra línea
    double mx = (ox1 + ox2) / 2.0;
    double my = (oy1 + oy2) / 2.0;

    // Ecuación de la línea principal
    double a = y2 - y1;
    double b = x1 - x2;
    double c = x2 * y1 - x1 * y2;

    return a * mx + b * my + c > 0;
  }

  std::tuple<double, double> consult_intersection(const std::tuple<double, double> &origin, double angle) {
    double closest_dist = std::numeric_limits<double>::infinity();
    std::tuple<double, double> closest_point;

    std::function<void(Node *)> traverse = [&](Node *node) {
      if (!node)
        return;

      double x1, y1, x2, y2;
      std::tie(x1, y1, x2, y2) = node->line;

      double dx_line = x2 - x1;
      double dy_line = y2 - y1;
      double dx_ray = std::cos(angle);
      double dy_ray = std::sin(angle);

      double denom = dx_line * dy_ray - dy_line * dx_ray;
      if (denom == 0) {
        return;
      }

      double t = ((std::get<0>(origin) - x1) * dy_ray - (std::get<1>(origin) - y1) * dx_ray) / denom;
      double u = ((std::get<0>(origin) - x1) * dy_line - (std::get<1>(origin) - y1) * dx_line) / denom;

      if (t >= 0 && t <= 1 && u >= 0) {
        double intersection_x = x1 + t * dx_line;
        double intersection_y = y1 + t * dy_line;
        double dist = std::sqrt(
            (intersection_x - std::get<0>(origin)) * (intersection_x - std::get<0>(origin)) +
            (intersection_y - std::get<1>(origin)) * (intersection_y - std::get<1>(origin)));

        if (dist < closest_dist) {
          closest_dist = dist;
          closest_point = std::make_tuple(intersection_x, intersection_y);
        }
      }

      Line ray_line = std::make_tuple(
          std::get<0>(origin),
          std::get<1>(origin),
          std::get<0>(origin) + std::cos(angle),
          std::get<1>(origin) + std::sin(angle));

      if (is_front(node->line, ray_line)) {
        traverse(node->front);
        traverse(node->back);
      }
      else {
        traverse(node->back);
        traverse(node->front);
      }
    };

    traverse(root);

    return closest_point;
  }

};
