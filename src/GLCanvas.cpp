#include <Vector4.hpp>
#include <Scalar.hpp>
#include <BasicMath.hpp>
#include "SCV/Point.h"
#include "GLCanvas.hpp"

#include "Edge.hpp"

GLCanvas::GLCanvas(scv::Point p1, scv::Point p2) : scv::Canvas(p1, p2)
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

std::vector<Math::Vector4>::iterator GLCanvas::collisionTest(Math::Vector4 p)
{
  for(auto it = m_vPoints.begin(); it != m_vPoints.end(); it++)
    if(p[0] > (*it)[0] - g_pointRadius && p[0] < (*it)[0] + g_pointRadius && p[1] > (*it)[1] - g_pointRadius && p[1] < (*it)[1] + g_pointRadius)
      return it;
  return m_vPoints.end();
}

std::vector<Math::Vector4> GLCanvas::giftWrap(std::vector<Math::Vector4> points)
{
  std::vector<Math::Vector4> chPoints;

  if(points.size() > 2)
  {
    Math::Scalar y = 0.0;
    int idx = -1;

    //Finds the bottom-most point of the set.
    for(int i = 0; i < points.size(); i++)
    {
      if(points[i][1] > y)
      {
        y = points[i][1];
        idx = i;
      }
    }
    //Add the point found to the convex hull vector.
    chPoints.push_back(points[idx]);

    Math::Vector4 pivotPoint(1, 0);
    do
    {
      idx = -1;
      Math::Scalar smlAngle = 2 * Math::PI;

      for(int i = 0; i < points.size(); i++)
      {
        if(points[i] == chPoints[chPoints.size() - 1])
          continue;

        Math::Vector4 currPoint = points[i] - chPoints[chPoints.size() - 1];
        currPoint.normalize();
        Math::Scalar angle = Math::ArcCosine(pivotPoint * currPoint);
        
        if(angle < smlAngle && angle != 0.0 && angle != Math::PI && angle != 2 * Math::PI)
        {
          smlAngle = angle;
          idx = i;
        }
      }

      if(idx >= 0 && idx < points.size())
        chPoints.push_back(points[idx]);

      pivotPoint = points[idx] - chPoints[chPoints.size() - 2];
      pivotPoint.normalize();

    } while(points.size() > chPoints.size() && chPoints[chPoints.size() - 1] != chPoints[0]);

    //chPoints.pop_back();
    //The loop above will be executed until we arrive at the first point
    //added to the convex hull vector.

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
      glVertex2f(m_vPoints[i][0], m_vPoints[i][1]);
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
    auto it = collisionTest(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
    if(it == m_vPoints.end())
      m_vPoints.push_back(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
  }

  //Erase points from the canvas.
  if(evt.getButton() == evt.RIGHT)
  {
    auto it = collisionTest(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
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

  m_vEdges.clear();
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
        auto it = collisionTest(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
        if(it != m_vPoints.end())
        {
          *it = Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y);
          m_pSelectedPoint = &*it;
        }
      }
      m_bMouseHeld = true;
    }
    else
    {
      if(m_pSelectedPoint != NULL)
        *m_pSelectedPoint = Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y);
    }
  }

  m_vEdges.clear();
}

void GLCanvas::onMouseUp(const scv::MouseEvent &evt)
{
  m_pSelectedPoint = NULL;
  m_bMouseHeld = false;
}

void GLCanvas::onKeyPressed(const scv::KeyEvent& evt)
{
  std::vector<Math::Vector4> a;
  switch(evt.keycode)
  {
  case GLUT_KEY_F1:
    a = giftWrap(m_vPoints);
    m_vEdges.clear();
    if(a.size() > 0)
    {
      for(int i = 1; i < a.size(); i++)
        m_vEdges.push_back(Edge(scv::Point((int) a[i - 1][0], (int) a[i - 1][1]), scv::Point((int) a[i][0], (int) a[i][1])));
      m_vEdges.push_back(Edge(scv::Point((int) a[0][0], (int) a[0][1]), scv::Point((int) a[a.size() - 1][0], (int) a[a.size() - 1][1])));
      std::cout << std::endl;
    }
    break;
  case GLUT_KEY_F2:
    for(int i = 0; i < m_vPoints.size(); i++)
      std::cout << m_vPoints[i] << std::endl;
    std::cout << std::endl;
    break;
  }
}