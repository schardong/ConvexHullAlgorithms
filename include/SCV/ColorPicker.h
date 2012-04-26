/*!
\file       ColorPicker.h
\brief      Implementation of a ColorPicker.
\author     SCV Team
*/

#ifndef __SCV_COLORPICKER_H__
#define __SCV_COLORPICKER_H__

#include "MatrixTemplate.h"
#include "ToggleButton.h"
#include "Panel.h"
#include "Spinner.h"

namespace scv {

class ColorPicker : public scv::Panel, public scv::MatrixTemplate<ColorRGBA> {
public:
   ColorPicker(const scv::Point &p);

   /*callback*/
   virtual void onColorChange(void) {}
   
   ColorRGBA getColor(void) const;   
   void setColor(const ColorRGBA &color);

   void processMouse(const scv::MouseEvent &evt);

   virtual void display(void);

protected:
   class EyeDropper : public ToggleButton {
   public:
      EyeDropper(ColorPicker *picker);
      void onMouseUp(const scv::MouseEvent &evt);
   private:
      ColorPicker *_picker;
   };

   void createTexture(void);

   void createColors(void);   
   void refreshColor(void);
   void setSpinsColor(void);

   Point foundHSL(void);

   Point _currentColorPosition;
   bool _pickerWaitingColor;

   double _saturation;
   ColorRGBA _currentColor, _currentPickerColor;

   Spinner *_rgbs[4];
   EyeDropper *_btPicker;

   ComponentTexture * _cpTexture;
};

} // namespace scv


#endif // __SCV_COLORPICKER_H__