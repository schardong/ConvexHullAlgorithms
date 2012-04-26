#ifndef __SCV_CONTEXT_MENU_H__
#define __SCV_CONTEXT_MENU_H__

#include "Label.h"
#include "Texture2D.h"

#include "PopupMenuStyle.h"

namespace scv {
class MenuHolder;

class ContextMenu {
friend class MenuHolder;
friend class MenuBar;
public:
   typedef std::deque<ContextMenu*> MenuList;

   ContextMenu(const std::string& name);
   virtual ~ContextMenu(void);

   virtual void onMenuAccessed(const std::deque<std::string> &address) {}
   virtual void onMouseClick(const scv::MouseEvent &evt, const std::deque<std::string> &address) {}
   virtual void onMouseOver(const scv::MouseEvent &evt, const std::deque<std::string> &address) {}
   virtual void onStatusChange(void) {}

   void addMenu(ContextMenu *menu);
   void removeMenu(ContextMenu *menu);
   void removeAllMenus();

   std::string getString(void);
   void setString(const std::string &label);

   void setPosition(const scv::Point &position);
   scv::Point getCurrPosition(void) const;

   bool getStatus(void) const;
   void setStatus(bool status);

   int getWidth(void) const;
   int getHeight(void) const;

   bool hasSubMenus(void) const;

   void setMenuStyle(const PopupMenuStyle* style);

   const MenuList& getMenus() const;

   bool processMouse(const scv::MouseEvent &evt);
   bool processKey(const scv::KeyEvent &evt);

   void display(void);

private:
   bool isInside(const Point &p);
   bool isInsideItem(const Point &p, int i) const;

   bool hasSubMenuActive(void) const;
      
   void setSubMenusStatus(bool status);
   void registerParentMenu(ContextMenu *parentMenu);
   void processMouseCallback(const MouseEvent &evt, std::deque<std::string> address);
   void processKeyboardCallback(const KeyEvent &evt, std::deque<std::string> address);

   bool _recentlyChange;
   bool _status;
   int _currSelectedMenu;

   MenuList _list;
   ContextMenu *_parentMenu;
   scv::Point _currPosition;
   std::string _label;
   const PopupMenuStyle* _style;
};

inline const ContextMenu::MenuList& ContextMenu::getMenus() const {
   return _list;
}

inline bool ContextMenu::hasSubMenus(void) const {
   return _list.size() > 0;
}

inline std::string ContextMenu::getString(void) {
   return _label;
}

inline void ContextMenu::setString(const std::string &label) {
   _label = label;
}

inline void ContextMenu::setPosition(const scv::Point &position) {
   _currPosition = position;
}

inline scv::Point ContextMenu::getCurrPosition(void) const {
   return _currPosition;
}

inline bool ContextMenu::getStatus(void) const {
   return _status;
}

inline int ContextMenu::getWidth(void) const {
   return _style->calculateWidth(this);
}

inline int ContextMenu::getHeight(void) const {
   return _style->calculateHeight(this);
}

inline bool ContextMenu::isInsideItem(const Point &p, int i) const {
   return _style->isInsideItem(this, p, i);
}

} // namespace scv


#endif // __SCV_CONTEXT_MENU_H__
