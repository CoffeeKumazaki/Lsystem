#pragma once

#include <stack>
#include <string>
#include <list>

template <typename T>
struct TVector2D {
  T x, y;
};

using Vector2D = TVector2D<float>;

template <typename T>
struct TPosition {
  TVector2D<T> pos;
  T dir;
};
using Position = TPosition<float>;


struct Line {
  Vector2D start, end;
};

class LTurtle
{
public:
  LTurtle();
  ~LTurtle();

  void init(float _step, float _angle);
  void interpret(std::string condition);
  void draw();

  void moveto(Vector2D to);
  void moveForward(float step);
  void turnRight(float angle);
  void turnLeft(float angle);

  void save();
  void restore();

private:
  float step;
  float angle; // rad.
  Position pos;

  std::stack<Position> stack;

  std::list<Line> lines;
};