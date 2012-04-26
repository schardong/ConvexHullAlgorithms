/*

SCV - Simple Components for Visual
Developed at Federal University of Santa Maria - UFSM
LaCA - Computer Applied Laboratory - Laborat�rio de Computa��o Aplicada
www.inf.ufsm.br/~pozzer/scv/
2007-2012 

*/

#ifndef __SCV_H__
#define __SCV_H__

#ifdef _WIN32
   #ifdef _MSC_VER
      #pragma warning(disable:4018)
   #endif // _WIN32
#endif // _MSC_VER

#define SCV_VERSION 4.0

#include "stdafx.h"

#include "Kernel.h"

#include "Button.h"
#include "Canvas.h"
#include "CheckBox.h"
#include "ColorPicker.h"
#include "ComboBox.h"
#include "ContextMenu.h"
#include "FileOpen.h"
#include "GlslShader.h"
#include "Image.h"
#include "InternalFrame.h"
#include "InternalFrameHolder.h"
#include "Label.h"
#include "Mathematic.h"
#include "MenuBar.h"
#include "ProgressBar.h"
#include "RadioButton.h"
#include "ScrollComponent.h"
#include "Separator.h"
#include "Singleton.h"
#include "Slider.h"
#include "StateButton.h"
#include "TabbedPane.h"
#include "Table.h"
#include "util.h"
#include "GenericTree.h"
#include "GenericNode.h"

#include "GroupLayout.h"
#include "SequentialGroup.h"
#include "ParallelGroup.h"

#endif // __SCV_H__
