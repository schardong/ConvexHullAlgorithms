#include <Vector4.hpp>
#include <Scalar.hpp>
#include <BasicMath.hpp>
#include "SCV/Point.h"
#include "GLCanvas.hpp"

#include "Edge.hpp"

GLCanvas::GLCanvas(scv::Point p1, scv::Point p2) : scv::Canvas(p1, p2)
{
  m_bMouseHeld = false;
  m_pSelectedPoint = NULL;
  glPointSize(g_pointRadius);
}

GLCanvas::~GLCanvas()
{
  m_vPoints.clear();
  m_vEdges.clear();
  m_pSelectedPoint = NULL;
  m_bMouseHeld = false;
}

std::vector<Math::Vector4>::iterator GLCanvas::collisionTest(Math::Vector4 p)
{
  
  for(auto it = m_vPoints.begin(); it != m_vPoints.end(); it++)
    if(p[0] > (*it)[0] - g_pointRadius && p[0] < (*it)[0] + g_pointRadius && p[1] > (*it)[1] - g_pointRadius && p[1] < (*it)[1] + g_pointRadius)
      return it;
  return m_vPoints.end();
}

Math::Scalar GLCanvas::ccw(Math::Vector4 v0, Math::Vector4 v1, Math::Vector4 v2)
{
  return (v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]);
}

std::vector<int> GLCanvas::giftWrap(std::vector<Math::Vector4> points)
{
  std::vector<int> chPointsIdx;

  if(points.size() > 2)
  {
    Math::Scalar y = (Math::Scalar) getHeight();
    int idx = -1;
    
    //Finds the upmost point of the set.
    for(int i = 0; i < points.size(); i++)
    {
      if(points[i][1] < y)
      {
        y = points[i][1];
        idx = i;
      }
    }
    //Add the point found to the convex hull vector.
    chPointsIdx.push_back(idx);

    Math::Vector4 pivotPoint(-1, 0);
    do
    {
      idx = -1;
      Math::Scalar smlAngle = 2 * Math::PI;

      for(int i = 0; i < points.size(); i++)
      {
        Math::Vector4 currPoint = points[i] - points[chPointsIdx[chPointsIdx.size() - 1]];
        currPoint.normalize();
        Math::Scalar angle = Math::ArcCosine(pivotPoint * currPoint);

        //If the angle between the vectors is less than 0, we jump to the next iteration.
        if(currPoint[1] * pivotPoint[0] > currPoint[0] * pivotPoint[1])
          continue;
        
        //If the angle is smaller than the smallest angle so far and the points are not collinear
        //we store the index of the point, for he is convexHull good candidate to be in the convex hull.
        if(angle < smlAngle && angle != 0.0 && angle != Math::PI && angle != 2 * Math::PI)
        {
          smlAngle = angle;
          idx = i;
        }
      }

      //If we found convexHull vaild point for the convex hull, we add it to the vector and chose convexHull new pivot
      //point based on him and the last point added.
      if(idx >= 0 && idx < points.size())
      {
        chPointsIdx.push_back(idx);
        pivotPoint = (points[idx] - points[chPointsIdx[chPointsIdx.size() - 2]]).normalized();
      }

    } while(points.size() > chPointsIdx.size() && points[chPointsIdx[chPointsIdx.size() - 1]] != points[chPointsIdx[0]]);
    
  }
  return chPointsIdx;
}

std::vector<int> GLCanvas::grahamScan(std::vector<Math::Vector4> points)
{
  std::vector<int> chPointsIdx;
  std::vector<int> pointsIdx;
  std::vector<Math::Vector4> sortedPoints = points;
  int i;

  if(points.size() > 2)
  {
    Math::Scalar y = (Math::Scalar) getHeight();
    int idx = -1;

    for(i = 0; i < points.size(); i++)
    {
      pointsIdx.push_back(i);
      sortedPoints[i][1] = y - sortedPoints[i][1];
    }

    //Finds the upmost point of the set.
    for(i--; i >= 0; i--)
    {
      if(sortedPoints[i][1] < y)
      {
        y = sortedPoints[i][1];
        idx = i;
      }
    }

    //Sort the points by their angle with the X axis.
    //Bubble sort for simplicity sake.
    Math::Vector4 xVector(1, 0);
    for(i = 0; i < sortedPoints.size(); i++)
    {
      Math::Scalar iAng = xVector * sortedPoints[i].normalized();
      for(int j = i + 1; j < sortedPoints.size(); j++)
      {
        Math::Scalar jAng = xVector * sortedPoints[j].normalized();
        if(jAng >= iAng)
        {
          Math::Vector4 auxVec = sortedPoints[i];
          sortedPoints[i] = sortedPoints[j];
          sortedPoints[j] = auxVec;
          int auxInt = pointsIdx[i];
          pointsIdx[i] = pointsIdx[j];
          pointsIdx[j] = auxInt;
        }
      }
    }

    chPointsIdx.push_back(pointsIdx[0]);
    chPointsIdx.push_back(pointsIdx[1]);

    std::cout << "First points. " << chPointsIdx[0] << ", " << chPointsIdx[1] << std::endl;
    std::cout << "Sorted points indices. ";
    for(i = 0; i < pointsIdx.size(); i++)
      std::cout << pointsIdx[i] << " ";
    std::cout << std::endl;

    i = 2;
    do
    {
      if(chPointsIdx.size() < 2)
        break;

      Math::Scalar area = ccw(sortedPoints[chPointsIdx[chPointsIdx.size() - 2]], sortedPoints[chPointsIdx[chPointsIdx.size() - 1]], sortedPoints[i]);
      if(area > 0)
        chPointsIdx.push_back(i);
      else
      {
        chPointsIdx.erase(chPointsIdx.end() - 1);
        chPointsIdx.push_back(i);
      }
      i++;
    } while(chPointsIdx[chPointsIdx.size() - 1] != chPointsIdx[0]);

  }

  //Sorting the result to build the convex polygon correctly.
  /*for(i = 0; i < chPointsIdx.size() - 1; i++)
  {
    for(int j = i + 1; j < chPointsIdx.size(); j++)
    {
      if(chPointsIdx[i] > chPointsIdx[j])
      {
        int aux = chPointsIdx[i];
        chPointsIdx[i] = chPointsIdx[j];
        chPointsIdx[j] = aux;
      }
    }
  }*/

  std::cout << "Convex hull indices. ";
  for(i = 0; i < chPointsIdx.size(); i++)
    std::cout << chPointsIdx[i] << " ";
  std::cout << std::endl;

  return chPointsIdx;
}

void GLCanvas::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glColor3d(0.f, 0.f, 0.f);
  for(int i = 0; i < m_vPoints.size(); i++)
  {
    glBegin(GL_POINTS);
      glVertex2f(m_vPoints[i][0], m_vPoints[i][1]);
    glEnd();
  }
  for(int i = 0; i < m_vEdges.size(); i++)
    m_vEdges[i].render();
}

void GLCanvas::update()
{
}

void GLCanvas::onMouseClick(const scv::MouseEvent &evt)
{
  //Insert new points on the canvas.
  if(evt.getButton() == evt.LEFT)
  {
    auto it = collisionTest(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
    if(it == m_vPoints.end())
      m_vPoints.push_back(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
  }

  //Erase points from the canvas.
  if(evt.getButton() == evt.RIGHT)
  {
    auto it = collisionTest(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
    if(it != m_vPoints.end())
    {
      if(m_pSelectedPoint == &*it)
      {
        m_pSelectedPoint = NULL;
        m_bMouseHeld = false;
      }
      m_vPoints.erase(it);
    }
  }

  m_vEdges.clear();
}

void GLCanvas::onMouseHold (const scv::MouseEvent &evt)
{
  //A point will be moved only if the left mouse button is held.
  if(evt.getButton() == evt.LEFT)
  {
    if(m_bMouseHeld == false)
    {
      if(evt.getButton() == evt.LEFT)
      {
        auto it = collisionTest(Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y));
        if(it != m_vPoints.end())
        {
          *it = Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y);
          m_pSelectedPoint = &*it;
        }
      }
      m_bMouseHeld = true;
    }
    else
    {
      if(m_pSelectedPoint != NULL)
        *m_pSelectedPoint = Math::Vector4((Math::Scalar) evt.getPosition().x, (Math::Scalar) evt.getPosition().y);
    }
  }

  m_vEdges.clear();
}

void GLCanvas::onMouseUp(const scv::MouseEvent &evt)
{
  m_pSelectedPoint = NULL;
  m_bMouseHeld = false;
}

void GLCanvas::onKeyPressed(const scv::KeyEvent& evt)
{
  std::vector<int> convexHull;
  switch(evt.keycode)
  {
  case GLUT_KEY_F1:
    convexHull = giftWrap(m_vPoints);
    m_vEdges.clear();
    if(convexHull.size() > 2)
    {
      for(int i = 1; i < convexHull.size(); i++)
        m_vEdges.push_back(Edge(m_vPoints[convexHull[i - 1]], m_vPoints[convexHull[i]]));
      m_vEdges.push_back(Edge(m_vPoints[convexHull[convexHull.size() - 1]], m_vPoints[convexHull[0]]));
    }
    break;
  case GLUT_KEY_F2:
    convexHull = grahamScan(m_vPoints);
    m_vEdges.clear();
    if(convexHull.size() > 2)
    {
      for(int i = 1; i < convexHull.size(); i++)
        m_vEdges.push_back(Edge(m_vPoints[convexHull[i - 1]], m_vPoints[convexHull[i]]));
      m_vEdges.push_back(Edge(m_vPoints[convexHull[convexHull.size() - 1]], m_vPoints[convexHull[0]]));
    }
    break;
  case GLUT_KEY_F3:
    for(int i = 0; i < m_vPoints.size(); i++)
      std::cout << m_vPoints[i] << std::endl;
    std::cout << std::endl;
    break;
  case GLUT_KEY_F4:
    m_vPoints.clear();
    m_vEdges.clear();
    system("cls");
    break;
  }
}