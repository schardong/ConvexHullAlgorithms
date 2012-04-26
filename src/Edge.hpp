#ifndef __EDGE_HPP__
#define __EDGE_HPP__

#include <CoreMath/Vector4.hpp>

class Edge
{
private:
  CoreMath::Vector4 m_aPoints[2];
  float m_aColor[3];
public:
  Edge(CoreMath::Vector4 p, CoreMath::Vector4 q);
  ~Edge();

  void setColor(float r, float g, float b);
  void render();
};

#endif /* __EDGE_HPP__ */
