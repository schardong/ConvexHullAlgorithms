#include "Edge.hpp"

Edge::Edge(scv::Point p, scv::Point q)
{
  m_aPoints[0] = p;
  m_aPoints[1] = q;
}

Edge::~Edge()
{
}

void Edge::setColor(float r, float g, float b)
{
  m_aColor[0] = r;
  m_aColor[1] = g;
  m_aColor[2] = b;
}

void Edge::render()
{
  glColor3f(m_aColor[0], m_aColor[1], m_aColor[2]);
  glBegin(GL_LINES);
    glVertex2i(m_aPoints[0].x, m_aPoints[0].y);
    glVertex2i(m_aPoints[1].x, m_aPoints[1].y);
  glEnd();
}