#ifndef __EDGE_HPP__
#define __EDGE_HPP__


#include <Vector4.hpp>

class Edge
{
private:
  Math::Vector4 m_aPoints[2];
  float m_aColor[3];
public:
  Edge(Math::Vector4 p, Math::Vector4 q);
  ~Edge();

  void setColor(float r, float g, float b);
  void render();
};

#endif /* __EDGE_HPP__ */