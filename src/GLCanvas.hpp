#ifndef __GL_CANVAS_HPP__
#define __GL_CANVAS_HPP__

#include <SCV/Canvas.h>
#include "Edge.hpp"

static const GLfloat g_pointRadius = 9.f;

class GLCanvas : public scv::Canvas
{
private:
  std::vector<scv::Point> m_vPoints;
  std::vector<Edge> m_vEdges;
  scv::Point* m_pSelectedPoint;
  bool m_bMouseHeld;

  /**
   * collisionTest: Tests if a given point p is within an existing
   * point of the canvas.
   * @p: The point to be tested.
   * @returns: An iterator to the point hit, or end() if no point was
   * hit.
   */
  std::vector<scv::Point>::iterator collisionTest(scv::Point p);

public:
  GLCanvas(scv::Point p1, scv::Point p2);
  virtual ~GLCanvas();

  //Convex Hull functions.
  std::vector<scv::Point> giftWrap(std::vector<scv::Point> points);

  //Drawing callbacks.
  void render();
  void update();
  //Mouse action callbacks.
  virtual void onMouseClick(const scv::MouseEvent &evt);
  virtual void onMouseHold (const scv::MouseEvent &evt);
  virtual void onMouseUp(const scv::MouseEvent &evt);

};

#endif /* __GL_CANVAS_HPP__ */