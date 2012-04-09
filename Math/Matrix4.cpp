/**
 * File:   Matrix4.cpp
 * Author: Guilherme Goncalves Schardong
 *
 * File created on December 18, 2010, 12:47 PM
 */

#include <cstring>
#include <cmath>

#include "Matrix4.hpp"
#include "Vector4.hpp"
#include "BasicMath.hpp"

namespace Math {

Matrix4::Matrix4()
{
  memset(m, 0, sizeof(Scalar) * 16);
}

Matrix4::~Matrix4()
{
  memset(m, 0, sizeof(Scalar) * 16);
}

Matrix4::Matrix4(const Matrix4& rhs)
{
  memcpy(m, rhs.m, sizeof(Scalar) * 16);
}

void Matrix4::loadIdentity()
{
  memset(m, 0, sizeof(Scalar) * 16);
  m[0] = 1.0;
  m[5] = 1.0;
  m[10] = 1.0;
  m[15] = 1.0;
}

void Matrix4::transpose()
{
  Vector4 l;
  Matrix4 m;
  for(int i = 0; i < 4; i++)
  {
    l = getLine(i);
    m.setColumn(i, l);
  }
  (*this) = m;
}

Matrix4& Matrix4::operator =(const Matrix4& rhs) {
  assert(this != &rhs);
  memcpy(m, rhs.m, sizeof(Scalar) * 16);
  return *this;
}

Matrix4 Matrix4::operator +(const Matrix4& rhs) {
  Matrix4* sum = new Matrix4();
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      (*sum)[i][j] = (*this)[i][j] + rhs[i][j];
  return *sum;
}

Matrix4 Matrix4::operator -(const Matrix4& rhs) {
  Matrix4* diff = new Matrix4();
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      (*diff)[i][j] = (*this)[i][j] - rhs[i][j];
  return *diff;
}

Matrix4& Matrix4::operator -() {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      (*this)[i][j] = -(*this)[i][j];
  return *this;
}

Matrix4 Matrix4::operator *(const Matrix4& rhs) {
  Matrix4* prod = new Matrix4();
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      for(int k = 0; k < 4; k++)
        (*prod)[i][j] += (*this)[i][k] * rhs[k][j];
  return *prod;
}

Vector4 Matrix4::operator *(Vector4& rhs) {
  Vector4* prod = new Vector4(0.0, 0.0, 0.0, 0.0);
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      (*prod)[i] += (*this)[i][j] * rhs[j];
  return *prod;
}

bool Matrix4::operator ==(const Matrix4& rhs) {
  return (
    (*this)[0][0] == rhs[0][0] && (*this)[0][1] == rhs[0][1] && (*this)[0][2] == rhs[0][2] && (*this)[0][3] == rhs[0][3] &&
    (*this)[1][0] == rhs[1][0] && (*this)[1][1] == rhs[1][1] && (*this)[1][2] == rhs[1][2] && (*this)[1][3] == rhs[1][3] &&
    (*this)[2][0] == rhs[1][0] && (*this)[2][1] == rhs[2][1] && (*this)[2][2] == rhs[2][2] && (*this)[2][3] == rhs[2][3] &&
    (*this)[3][0] == rhs[2][0] && (*this)[3][1] == rhs[3][1] && (*this)[3][2] == rhs[3][2] && (*this)[3][3] == rhs[3][3]
  );
}

bool Matrix4::operator !=(const Matrix4& rhs) {
  return (!(*this == rhs));
}

Matrix4 rotate(Scalar angle, Vector4 axis)
{
  axis.normalize();
  Matrix4 tmp;
  tmp.loadIdentity();
  Scalar c = Cosine(angle);
  Scalar s = Sine(angle);
  tmp[0][0] = axis[0] * axis[0] * (1 - c) + c;
  tmp[0][1] = axis[0] * axis[1] * (1 - c) - axis[2] * s;
  tmp[0][2] = axis[0] * axis[2] * (1 - c) + axis[1] * s;
  tmp[1][0] = axis[0] * axis[1] * (1 - c) + axis[2] * s;
  tmp[1][1] = axis[1] * axis[2] * (1 - c) + c;
  tmp[1][2] = axis[1] * axis[2] * (1 - c) - axis[0] * s;
  tmp[2][0] = axis[0] * axis[2] * (1 - c) - axis[1] * s;
  tmp[2][1] = axis[1] * axis[2] * (1 - c) + axis[0] * s;
  tmp[2][2] = axis[2] * axis[2] * (1 - c) + c;
  return tmp;
}

Matrix4 translate(Scalar x, Scalar y, Scalar z)
{
  Matrix4 tmp;
  tmp.loadIdentity();
  tmp[0][3] = x;
  tmp[1][3] = y;
  tmp[2][3] = z;
  return tmp;
}

Matrix4 scale(Scalar sx, Scalar sy, Scalar sz)
{
  Matrix4 tmp;
  tmp.loadIdentity();
  tmp[0][0] = sx;
  tmp[1][1] = sy;
  tmp[2][2] = sz;
  return tmp;
}

Matrix4 perspective(Scalar fovy, Scalar aspectRatio, Scalar near, Scalar far)
{
  Scalar xMax, yMax;
  yMax = near * Tangent(DegToRad(fovy / 2));
  xMax = yMax * aspectRatio;
  return frustum(-xMax, xMax, -yMax, yMax, near, far);

}

Matrix4 frustum(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far)
{
  Matrix4 tmp;
  tmp[0][0] = 2.f * near / (right - left);
  tmp[0][2] = (right + left) / (right - left);
  tmp[1][1] = 2.f * near / (top - bottom);
  tmp[1][2] = (top + bottom) / (top - bottom);
  tmp[2][2] = (-far - near) / (far - near);
  tmp[2][3] = (-2.f * far * near) / (far - near);
  tmp[3][2] = -1.0;
  tmp[3][3] = 0;
  return tmp;
}

Matrix4 ortho(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far)
{
  Matrix4 tmp;
  tmp.loadIdentity();
  tmp[0][0] = 2.f / (right - left);
  tmp[0][3] = -(right + left) / (right - left);
  tmp[1][1] = 2.f / (top - bottom);
  tmp[1][3] = -(top + bottom) / (top - bottom);
  tmp[2][2] = -2.f / (far - near);
  tmp[2][3] = -(far + near) / (far - near);
  return tmp;
}

Matrix4 lookAt(Scalar eyeX, Scalar eyeY, Scalar eyeZ, Scalar centerX, Scalar centerY, Scalar centerZ, Scalar upX, Scalar upY, Scalar upZ)
{
  Matrix4 tmp;
  tmp.loadIdentity();

  Vector4 forward(centerX - eyeX, centerY - eyeY, centerZ - eyeZ);
  Vector4 up(upX, upY, upZ);
  Vector4 right;

  forward.normalize();
  right = forward ^ up;
  right.normalize();
  up = right ^ forward;

  tmp[0][0] = right[0];
  tmp[0][1] = right[1];
  tmp[0][2] = right[2];
  tmp[1][0] = up[0];
  tmp[1][1] = up[1];
  tmp[1][2] = up[2];
  tmp[2][0] = forward[0];
  tmp[2][1] = forward[1];
  tmp[2][2] = forward[2];
  tmp[0][3] = -eyeX;
  tmp[1][3] = -eyeY;
  tmp[2][3] = -eyeZ;

  return tmp;
}

}
