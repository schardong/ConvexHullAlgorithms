#ifndef __GL_POINT_HPP__
#define __GL_POINT_HPP__

#include <SCV/Point.h>

class GLPoint : public scv::Point
{
public:
  GLPoint(int x = 0, int y = 0);
  GLPoint(const scv::Point& rhs);
  ~GLPoint();
  
  //The norm of the vector represented by this point.
  inline float norm();

  //
  inline GLPoint operator -(GLPoint& rhs);

  //Dot product: The points can be defined as vectors too.
  inline float operator *(GLPoint& rhs);
};

GLPoint::GLPoint(int x, int y) : scv::Point(x, y)
{}

GLPoint::GLPoint(const scv::Point& rhs)
{
  x = rhs.x;
  y = rhs.y;
}

GLPoint::~GLPoint()
{}

float GLPoint::norm()
{
  return sqrt((*this) * (*this));
}

GLPoint GLPoint::operator -(GLPoint& rhs)
{
  return GLPoint(x - rhs.x, y - rhs.y);
}

float GLPoint::operator *(GLPoint& rhs)
{
  return (float)(x * rhs.x + y * rhs.y);
}

#endif /* __GL_POINT_HPP__ */