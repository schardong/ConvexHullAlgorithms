#ifndef __GL_CANVAS_HPP__
#define __GL_CANVAS_HPP__

#include <SCV/Canvas.h>
#include "Edge.hpp"
#include "GLPoint.hpp"

static const GLfloat g_pointRadius = 9.f;

class GLCanvas : public scv::Canvas
{
private:
  std::vector<GLPoint> m_vPoints;
  std::vector<Edge> m_vEdges;
  GLPoint* m_pSelectedPoint;
  bool m_bMouseHeld;

  /**
   * collisionTest: Tests if a given point p is within an existing
   * point of the canvas.
   * @p: The point to be tested.
   * @returns: An iterator to the point hit, or end() if no point was
   * hit.
   */
  std::vector<GLPoint>::iterator collisionTest(GLPoint p);

public:
  GLCanvas(GLPoint p1, GLPoint p2);
  virtual ~GLCanvas();

  //Convex Hull functions.
  std::vector<GLPoint> giftWrap(std::vector<GLPoint> points);

  //Drawing callbacks.
  void render();
  void update();
  //Mouse action callbacks.
  virtual void onMouseClick(const scv::MouseEvent &evt);
  virtual void onMouseHold (const scv::MouseEvent &evt);
  virtual void onMouseUp(const scv::MouseEvent &evt);

};

#endif /* __GL_CANVAS_HPP__ */