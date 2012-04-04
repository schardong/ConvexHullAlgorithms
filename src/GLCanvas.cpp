#define _USE_MATH_DEFINES
#include <math.h>
#include "GLCanvas.hpp"

GLCanvas::GLCanvas(GLPoint p1, GLPoint p2) : scv::Canvas(p1, p2)
{
  m_bMouseHeld = false;
  m_pSelectedPoint = NULL;
  glPointSize(g_pointRadius);
}

GLCanvas::~GLCanvas()
{
  m_vPoints.clear();
  m_vEdges.clear();
  m_pSelectedPoint = NULL;
  m_bMouseHeld = false;
}

std::vector<GLPoint>::iterator GLCanvas::collisionTest(GLPoint p)
{
  for(auto it = m_vPoints.begin(); it != m_vPoints.end(); it++)
    if(p.x > it->x - g_pointRadius && p.x < it->x + g_pointRadius && p.y > it->y - g_pointRadius && p.y < it->y + g_pointRadius)
      return it;
  return m_vPoints.end();
}

std::vector<GLPoint> GLCanvas::giftWrap(std::vector<GLPoint> points)
{
  std::vector<GLPoint> chPoints;

  if(points.size() > 0)
  {
    int x = MAXDWORD32;
    int idx = -1;
    GLPoint currPoint(0, 1);

    //Finds the leftmost point of the set.
    for(int i = 0; i < points.size(); i++)
    {
      if(points[i].x < x)
      {
        x = points[i].x;
        idx = i;
      }
    }

    chPoints.push_back(points[idx]);
    float smlAngle = (float) (2 * M_PI);

    do
    {
      for(int i = 0; i < points.size(); i++)
      {
        float angle = acos(currPoint * (points[i] - chPoints[chPoints.size() - 1]));
        //calc angle between the current point and every other point.
        //test wheter the angle is smaller than the angle we have.
        //if it is, add it to the convex hull.
      }
    } while(smlAngle == 2 * M_PI); //chance the condition!

  }

  return chPoints;
}

void GLCanvas::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glColor3d(0.f, 0.f, 0.f);
  for(int i = 0; i < m_vPoints.size(); i++)
  {
    glBegin(GL_POINTS);
      glVertex2i(m_vPoints[i].x, m_vPoints[i].y);
    glEnd();
  }
  for(int i = 0; i < m_vEdges.size(); i++)
    m_vEdges[i].render();
}

void GLCanvas::update()
{
}

void GLCanvas::onMouseClick(const scv::MouseEvent &evt)
{
  //Insert new points on the canvas.
  if(evt.getButton() == evt.LEFT)
  {
    auto it = collisionTest(GLPoint(evt.getPosition()));
    if(it == m_vPoints.end())
      m_vPoints.push_back(GLPoint(evt.getPosition()));
  }

  //Erase points from the canvas.
  if(evt.getButton() == evt.RIGHT)
  {
    auto it = collisionTest(evt.getPosition());
    if(it != m_vPoints.end())
    {
      if(m_pSelectedPoint == &*it)
      {
        m_pSelectedPoint = NULL;
        m_bMouseHeld = false;
      }
      m_vPoints.erase(it);
    }
  }
}

void GLCanvas::onMouseHold (const scv::MouseEvent &evt)
{
  //A point will be moved only if the left mouse button is held.
  if(evt.getButton() == evt.LEFT)
  {
    if(m_bMouseHeld == false)
    {
      if(evt.getButton() == evt.LEFT)
      {
        auto it = collisionTest(evt.getPosition());
        if(it != m_vPoints.end())
        {
          *it = evt.getPosition();
          m_pSelectedPoint = &*it;
        }
      }
      m_bMouseHeld = true;
    }
    else
    {
      if(m_pSelectedPoint != NULL)
        *m_pSelectedPoint = evt.getPosition();
    }
  }
}

void GLCanvas::onMouseUp(const scv::MouseEvent &evt)
{
  m_pSelectedPoint = NULL;
  m_bMouseHeld = false;
}