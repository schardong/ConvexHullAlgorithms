#ifndef __GL_POINT_HPP__
#define __GL_POINT_HPP__

#include <SCV/Point.h>

class GLPoint : public scv::Point
{
public:
  GLPoint() : scv::Point() {}
  GLPoint(int x, int y) : scv::Point(x, y) {}

  GLPoint(const scv::Point& rhs)
  {
    x = rhs.x;
    y = rhs.y;
  }

  ~GLPoint() {}
  
  //The norm of the vector represented by this point.
  inline float norm()
  {
    return sqrt((*this) * (*this));
  }

  inline void normalize()
  {
    if(norm() == 0)
      return;
    x /= (int)norm();
    y /= (int)norm();
  }

  inline GLPoint& operator =(const GLPoint& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

  inline GLPoint operator -(GLPoint& rhs)
  {
    return GLPoint(x - rhs.x, y - rhs.y);
  }

  //Dot product: The points can be defined as vectors too.
  inline float operator *(GLPoint& rhs)
  {
    return (float)(x * rhs.x + y * rhs.y);
  }
};

#endif /* __GL_POINT_HPP__ */