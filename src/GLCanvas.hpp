#ifndef __GL_CANVAS_H__
#define __GL_CANVAS_H__

#include <SCV/Canvas.h>

const GLfloat g_pointRadius = 9.f;

class GLCanvas : public scv::Canvas
{
private:
  std::vector<scv::Point> m_vPoints;
  scv::Point* m_pSelectedPoint;
  bool mouseHeld;

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

  void render();
  void update();

  virtual void onMouseClick(const scv::MouseEvent &evt);
  virtual void onMouseHold (const scv::MouseEvent &evt);
  virtual void onMouseUp(const scv::MouseEvent &evt);

};

#endif /* __GL_CANVAS_H__ */