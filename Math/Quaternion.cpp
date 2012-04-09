/**
 * File: Quaternion.cpp
 * Author: Guilherme Gonçalves Schardong
 * File created on December 29, 2011, 19:08
 */

#include "Quaternion.hpp"
#include "BasicMath.hpp"

namespace Math
{
  
Quaternion::Quaternion(Scalar _w, Scalar _x, Scalar _y, Scalar _z)
{
  m[0] = _w;
  m[1] = _x;
  m[2] = _y;
  m[3] = _z;
}

Quaternion::Quaternion(const Quaternion& rhs)
{
  m[0] = rhs.m[0];
  m[1] = rhs.m[1];
  m[2] = rhs.m[2];
  m[3] = rhs.m[3];
}

Quaternion::~Quaternion()
{
  m[0] = m[1] = m[2] = m[3] = 0.0;
}

Scalar Quaternion::norm()
{
  return (SquareRoot(dot(*this, *this)));
}

void Quaternion::normalize()
{
  m[0] = m[0] / norm();
  m[1] = m[1] / norm();
  m[2] = m[2] / norm();
  m[3] = m[3] / norm();
}

Quaternion Quaternion::normalized()
{
  Quaternion q(*this);
  q.normalize();
  return q;
}

void Quaternion::loadIdentity()
{
  m[0] = 1.0;
  m[1] = 0.0;
  m[2] = 0.0;
  m[3] = 0.0;
}

Quaternion& Quaternion::operator =(const Quaternion& rhs)
{
  if(this == &rhs)
    return *this;
  m[0] = rhs.m[0];
  m[1] = rhs.m[1];
  m[2] = rhs.m[2];
  m[3] = rhs.m[3];
  return *this;
}

Quaternion Quaternion::operator +(Quaternion& rhs)
{
  return Quaternion(m[0] + rhs.m[0], m[1] + rhs.m[1], m[2] + rhs.m[2], m[3] + rhs.m[3]);
}

Quaternion Quaternion::operator -(Quaternion& rhs)
{
  return Quaternion(m[0] - rhs.m[0], m[1] - rhs.m[1], m[2] - rhs.m[2], m[3] - rhs.m[3]);
}

Quaternion& Quaternion::operator -()
{
  m[1] = -m[1];
  m[2] = -m[2];
  m[3] = -m[3];
  return *this;
}

Quaternion Quaternion::operator *(Quaternion& rhs)
{
  return Quaternion(m[0] * rhs.m[0] - m[1] * rhs.m[1] - m[2] * rhs.m[2] - m[3] * rhs.m[3],
                    m[0] * rhs.m[1] + m[1] * rhs.m[0] + m[2] * rhs.m[3] - m[3] * rhs.m[2],
                    m[0] * rhs.m[2] - m[1] * rhs.m[3] + m[2] * rhs.m[0] + m[3] * rhs.m[1],
                    m[0] * rhs.m[3] + m[1] * rhs.m[2] - m[2] * rhs.m[1] + m[3] * rhs.m[0]);
}

Quaternion Quaternion::operator *(Scalar rhs)
{
  return Quaternion(m[0] * rhs, m[1] * rhs, m[2] * rhs, m[3] * rhs);
}

Quaternion Quaternion::operator /(Quaternion& rhs)
{
  Quaternion inverse = -rhs / Power(rhs.norm(), 2);
  return *this * inverse;
}

Quaternion Quaternion::operator /(Scalar rhs)
{
  return Quaternion(m[0] / rhs, m[1] / rhs, m[2] / rhs, m[3] / rhs);
}

bool Quaternion::operator ==(Quaternion& rhs)
{
  return (m[0] == rhs.m[0] && m[1] == rhs.m[1] && m[2] == rhs.m[2] && m[3] == rhs.m[3]);
}

bool Quaternion::operator !=(Quaternion& rhs)
{
  return (*this == rhs);
}

Scalar dot(Quaternion q1, Quaternion q2)
{
  return (q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3]);
}

Quaternion lerp(Quaternion q1, Quaternion q2, const Scalar t)
{
  Quaternion q3 = q1 * (1 - t) + q2 * t;
  q3.normalize();
  return q3;
}

Quaternion slerp(Quaternion q1, Quaternion q2, const Scalar t)
{
  Scalar angle = ArcCosine(dot(q1, q2));
  if(angle < 0)
    angle = -angle;
  return q1 * (Sine(angle * (1 - t)) / Sine(angle)) + q2 * (Sine(angle * t) / Sine(angle));
}


}