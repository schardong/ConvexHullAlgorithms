/**
 * File:   Vector4.cpp
 * Author: Guilherme Goncalves Schardong
 *
 * File created on December 18, 2010, 13:45 PM
 */

#include <cstring>

#include "Vector4.hpp"
#include "BasicMath.hpp"

namespace Math
{

Vector4::Vector4(Scalar x, Scalar y, Scalar z, Scalar w)
{
  m[0] = x;
  m[1] = y;
  m[2] = z;
  m[3] = w;
}

Vector4::Vector4(const Vector4& rhs)
{
  m[0] = rhs.m[0];
  m[1] = rhs.m[1];
  m[2] = rhs.m[2];
  m[3] = rhs.m[3];
}

Vector4::~Vector4(void)
{
  m[0] = m[1] = m[2] = m[3] = 0.0;
}

Scalar Vector4::norm(void)
{
  return SquareRoot((*this) * (*this));
}

void Vector4::normalize(void)
{
  Scalar n = norm();
  m[0] /= n;
  m[1] /= n;
  m[2] /= n;
}

Vector4 Vector4::normalized(void)
{
  Vector4 a_result(*this);
  a_result.normalize();
  return a_result;
}

Vector4& Vector4::operator =(const Vector4& rhs)
{
  if (this == &rhs)  //handle self assignment
    return *this;
  memcpy(m, rhs.m, sizeof(Scalar) * 4);
  return *this;
}

Vector4 Vector4::operator +(Vector4& rhs)
{
  return Vector4((*this)[0] + rhs[0], (*this)[1] + rhs[1], (*this)[2] + rhs[2]);
}

Vector4 Vector4::operator -(Vector4& rhs)
{
  return Vector4((*this)[0] - rhs[0], (*this)[1] - rhs[1], (*this)[2] - rhs[2]);
}

Vector4& Vector4::operator -(void)
{
  (*this)[0] = -(*this)[0];
  (*this)[1] = -(*this)[1];
  (*this)[2] = -(*this)[2];
  return *this;
}

Scalar Vector4::operator *(Vector4& rhs)
{
  return ((*this)[0] * rhs[0] + (*this)[1] * rhs[1] + (*this)[2] * rhs[2]);
}

Vector4 Vector4::operator *(const Scalar rhs)
{
  return Vector4((*this)[0] * rhs, (*this)[1] * rhs, (*this)[2] * rhs);
}

Vector4 Vector4::operator ^(Vector4& rhs)
{
  return Vector4((*this)[1]*rhs[2] - (*this)[2]*rhs[1], (*this)[2]*rhs[0] - (*this)[0]*rhs[2], (*this)[0]*rhs[1] - (*this)[1]*rhs[0]);
}

bool Vector4::operator ==(Vector4& rhs)
{
  return ((*this)[0] == rhs[0] && (*this)[1] == rhs[1] && (*this)[2] == rhs[2] && (*this)[3] == rhs[3]);
}

bool Vector4::operator !=(Vector4& rhs)
{
  return ((*this)[0] != rhs[0] || (*this)[1] != rhs[1] || (*this)[2] != rhs[2] || (*this)[3] != rhs[3]);
}

}

