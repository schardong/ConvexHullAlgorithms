#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SCV/SCV.h>

class Application : public scv::Kernel
{
private:

protected:
  static const int s_defaultWindowWidth = 1280;
  static const int s_defaultWindowHeight = 720;
  scv::Panel* m_pMainPanel;
  scv::ButtonGroup* m_pAlgorithmSelector;

public:
  Application(void);
  virtual ~Application(void);

  void init(void);

  inline scv::ButtonGroup* getAlgorithmSelector()
  {
    return m_pAlgorithmSelector;
  }

  //SCVCallbacks
  virtual void onMouseClick(const scv::MouseEvent &evt);
  virtual void onMouseHold (const scv::MouseEvent &evt);
  virtual void onMouseOver (const scv::MouseEvent &evt);
  virtual void onMouseUp   (const scv::MouseEvent &evt);
  virtual void onMouseWheel(const scv::MouseEvent &evt);

  virtual void onKeyPressed(const scv::KeyEvent &evt);
  virtual void onKeyUp     (const scv::KeyEvent &evt);

  virtual void onSizeChange(void);
  virtual void onPositionChange(void);
};

#endif //__APPLICATION_H__
