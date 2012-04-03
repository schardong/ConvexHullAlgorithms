#ifndef __EDGE_HPP__
#define __EDGE_HPP__

#include <SCV/SCV.h>
#include <SCV/Point.h>

class Edge
{
private:
  scv::Point m_aPoints[2];
  float m_aColor[3];
public:
  Edge(scv::Point p, scv::Point q);
  ~Edge();

  void setColor(float r, float g, float b);
  void render();
};

#endif /* __EDGE_HPP__ */