#include <SCV/SCV.h>
#include "Edge.hpp"

Edge::Edge(CoreMath::Vector4 p, CoreMath::Vector4 q)
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
    glVertex2f(m_aPoints[0][0], m_aPoints[0][1]);
    glVertex2f(m_aPoints[1][0], m_aPoints[1][1]);
  glEnd();
}
