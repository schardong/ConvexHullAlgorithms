#ifndef __GL_CANVAS_HPP__
#define __GL_CANVAS_HPP__

#include <SCV/Canvas.h>
#include <SCV/Point.h>
#include <CoreMath/Vector4.hpp>
#include <CoreMath/Scalar.hpp>

class Edge;
class Application;

static const GLfloat g_pointRadius = 9.f;

class GLCanvas : public scv::Canvas
{
private:
  std::vector<CoreMath::Vector4> m_vPoints;
  std::vector<Edge> m_vEdges;
  CoreMath::Vector4* m_pSelectedPoint;
  scv::ButtonGroup* m_pButtonGroup;
  bool m_bMouseHeld;

  /**
   * collisionTest: Tests if a given point p is within an existing
   * point of the canvas.
   * @p: The point to be tested.
   * @returns: An iterator to the point hit, or end() if no point was
   * hit.
   */
  std::vector<CoreMath::Vector4>::iterator collisionTest(CoreMath::Vector4 p);

  /**
   * ccw: Tests wheter the given points are in a counter clockwise 
   * rotation or if they are in a clockwise rotation from each other
   * @vn: The points to be tested.
   * @returns: The area of the triangle formed by the points. If the
   * area is < 0 then the points are in a clockwise rotation. Or if
   * the area is 0 then the points are collinear. Else the points are
   * in a ccw rotation.
   */
  CoreMath::Scalar ccw(CoreMath::Vector4 v0, CoreMath::Vector4 v1, CoreMath::Vector4 v2);

public:
  GLCanvas(scv::Point p1, scv::Point p2, scv::ButtonGroup* bg);
  virtual ~GLCanvas();

  //Convex Hull functions.
  std::vector<int> giftWrap(std::vector<CoreMath::Vector4> points);
  std::vector<int> grahamScan(std::vector<CoreMath::Vector4> points);
  void applyConvexHull();

  //Drawing callbacks.
  void render();
  void update();
  //Mouse action callbacks.
  virtual void onMouseClick(const scv::MouseEvent &evt);
  virtual void onMouseHold (const scv::MouseEvent &evt);
  virtual void onMouseUp(const scv::MouseEvent &evt);
  virtual void onKeyPressed(const scv::KeyEvent& evt);

};

#endif /* __GL_CANVAS_HPP__ */
