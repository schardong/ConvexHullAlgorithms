#include "GLCanvas.hpp"

GLCanvas::GLCanvas(scv::Point p1, scv::Point p2) : scv::Canvas(p1, p2)
{
  mouseHeld = false;
  m_pSelectedPoint = NULL;
  glPointSize(g_pointRadius);
  m_vPoints.push_back(p1 + 50);
  m_vPoints.push_back(p2 - 40);
}

GLCanvas::~GLCanvas()
{
  m_vPoints.clear();
  m_pSelectedPoint = NULL;
  mouseHeld = false;
}

std::vector<scv::Point>::iterator GLCanvas::collisionTest(scv::Point p)
{
  for(auto it = m_vPoints.begin(); it != m_vPoints.end(); it++)
    if(p.x > it->x - g_pointRadius && p.x < it->x + g_pointRadius && p.y > it->y - g_pointRadius && p.y < it->y + g_pointRadius)
      return it;
  return m_vPoints.end();
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
}

void GLCanvas::update()
{
}

void GLCanvas::onMouseClick(const scv::MouseEvent &evt)
{
  //Insert new points on the canvas.
  if(evt.getButton() == evt.LEFT)
  {
    auto it = collisionTest(evt.getPosition());
    if(it == m_vPoints.end())
      m_vPoints.push_back(scv::Point(evt.getPosition()));
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
        mouseHeld = false;
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
    if(mouseHeld == false)
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
      mouseHeld = true;
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
  mouseHeld = false;
}