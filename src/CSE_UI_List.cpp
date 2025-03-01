
//============================================================================================//
/*
  Filename: CSE_UI_List.cpp
  Description: List support source file for the CSE_UI Arduino library.
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 0.0.8
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_CST328
  Last Modified: +05:30 01:06:45 AM 02-03-2025, Sunday
 */
//============================================================================================//

#include "CSE_UI.h"

//============================================================================================//

// listClass:: listClass (CSE_UI* ui, buttonClass* list, int count) {
//   uiParent = ui;
//   itemList = list;
//   itemCount = count;
// }

listClass:: listClass (CSE_UI* ui) {
  uiParent = ui;
}

//============================================================================================//

void listClass:: initialize (int16_t x, int16_t y, int w, int h, uint16_t fgcolor, uint16_t bgcolor, uint16_t focusfg, uint16_t focusbg) {
  listX = x;
  listY = y;
  itemWidth = w;
  itemHeight = h;
  itemFgColor = fgcolor;
  itemBgColor = bgcolor;
  itemFocusFgColor = focusfg;
  itemFocusBgColor = focusbg;
  itemHoverFgColor = focusfg;
  itemHoverBgColor = focusbg;
  itemVisibleCount = itemCount;
  currentItem = 0;
  visible = true;
}

//============================================================================================//

void listClass:: addItem (buttonClass* item, String label) {
  itemList.push_back (item);

  itemList [itemCount]->initialize (listX, listY + (itemCount * itemHeight), itemWidth, itemHeight, itemBgColor, itemFgColor, label);
  itemList [itemCount]->radius = 0;

  itemCount++;
}

//============================================================================================//

void listClass:: reset() {
  currentItem = 0;
  prevItem = -1;
  currentVisibleItem = 0;
  scrollPosition = 0;

  for (int i = 0; i < itemCount; i++) {
    itemList [i]->reset();
  }
}

//============================================================================================//

void listClass:: show() {
  visible = true;
}

//============================================================================================//

void listClass:: hide() {
  visible = false;
}

//============================================================================================//

void listClass:: triggerStateChange() {
  for (int i = 0; i < itemCount; i++) {
    itemList [i]->reset();
  }
}

//============================================================================================//

void listClass:: setCurrentItem (int item) {
  currentItem = item;
}

//============================================================================================//

int listClass:: getCurrentItem() {
  return currentItem;
}

//============================================================================================//

void listClass:: toNextItem() {
  if (currentItem < (itemCount - 1)) {
    currentItem++;
  }
  else {
    currentItem = 0;
  }
  triggerStateChange();
}

//============================================================================================//

void listClass:: toPrevItem() {
  if (currentItem > 0) {
    currentItem--;
  }
  else {
    currentItem = itemCount - 1;
  }
  triggerStateChange();
}

//============================================================================================//
/**
 * @brief Sets the alignement of the text (label) with respect to the button (box).
 * Datum can be 0 = Center, 1 = Top Center, 2 = Right Center, 3 = Bottom Center, 4 = Left Center
 * 
 * @param datum 
 */

void listClass:: setTextAlign (int datum) {
  for (int i = 0; i < itemCount; i++) {
    itemList [i]->labelAlign = datum;
  }
}

//============================================================================================//

void listClass:: setTextPadding (int xPad, int yPad) {
  for (int i = 0; i < itemCount; i++) {
    itemList [i]->labelOffsetX = xPad;
    itemList [i]->labelOffsetY = yPad;
  }
}

//============================================================================================//

void listClass:: scrollDown() {
  if (currentItem < itemCount - 1) {
    currentItem++;
    if (currentItem - scrollPosition >= itemVisibleCount) {
      // Scroll down only when currentItem exceeds the bottom of visible window
      scrollPosition++;
    }
    currentVisibleItem = currentItem - scrollPosition;
  }
  if (prevItem != currentItem) {
    triggerStateChange();
  }
  prevItem = currentItem;
}

//============================================================================================//

void listClass:: scrollUp() {
  if (currentItem > 0) {
    currentItem--;
    if (currentItem < scrollPosition) {
      // Scroll up only when currentItem goes above the top of visible window
      scrollPosition--;
    }
    currentVisibleItem = currentItem - scrollPosition;
  }
  if (prevItem != currentItem) {
    triggerStateChange();
  }
  prevItem = currentItem;
}

//============================================================================================//

void listClass:: draw() {
  if (!visible) return;
  
  for (int i = 0; i < itemVisibleCount; i++) {
    // Compute the real index of the item taking into account the scroll position
    int realIndex = scrollPosition + i;

    // Stop drawing when there's no more items to show
    if (realIndex >= itemCount) break;

    if (i == currentVisibleItem) {
      itemList[realIndex]->fillColor = itemFocusBgColor;
      itemList[realIndex]->labelColor = itemFocusFgColor;
    }
    else {
      itemList[realIndex]->fillColor = itemBgColor;
      itemList[realIndex]->labelColor = itemFgColor;
    }

    itemList[realIndex]->setXY (listX, listY + (i * itemHeight));
    itemList[realIndex]->draw();
  }
}


//============================================================================================//
