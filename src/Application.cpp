#include "Application.h"
#include "GLCanvas.hpp"

Application::Application(void) : Kernel()
{
  setWindowSize(1245, 835);
  lockWindowSize(false);
  setFramesPerSecond(60);

  setWindowTitle("TCA-T1: Convex Hull");
}

Application::~Application(void)
{
  delete m_pMainPanel;
}

void Application::init(void)
{
  m_pMainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(1198, 795));

  addComponent(m_pMainPanel);

  scv::InternalFrame *internalFrame0 = new scv::InternalFrame(220, 792, "Controls");
  internalFrame0->setAbsolutePosition(scv::Point(1000, 0));
  addComponent(internalFrame0);

  scv::InternalFrame *internalFrame1 = new scv::InternalFrame(978, 792, "Canvas");
  addComponent(internalFrame1);
  GLCanvas *canvas0 = new GLCanvas(scv::Point(0,0), scv::Point(978, 792));
  canvas0->setParent(internalFrame1->getPanel());
}

void Application::onMouseClick(const scv::MouseEvent &evt)
{
}

void Application::onMouseHold(const scv::MouseEvent &evt)
{
}

void Application::onMouseOver(const scv::MouseEvent &evt)
{
}

void Application::onMouseUp(const scv::MouseEvent &evt)
{
}

void Application::onMouseWheel(const scv::MouseEvent &evt)
{
}

void Application::onKeyPressed(const scv::KeyEvent &evt)
{
  std::cout << evt.keycode << std::endl;
  switch(evt.keycode)
  {
  case 27:
    Kernel::destroyInstance();
    exit(0);
    break;
  }
}

void Application::onKeyUp(const scv::KeyEvent &evt)
{
}

void Application::onSizeChange(void)
{
   m_pMainPanel->setSize(getWidth(), getHeight());
}

void Application::onPositionChange(void)
{
}
