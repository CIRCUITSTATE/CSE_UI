
//============================================================================================//
/*
  Filename: CSE_UI_TextArea.cpp
  Description: Text area support source file for the CSE_UI Arduino library.
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 0.0.8
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_CST328
  Last Modified: +05:30 01:08:04 AM 02-03-2025, Sunday
 */
//============================================================================================//

#include "CSE_UI.h"

//============================================================================================//

textAreaClass:: textAreaClass (CSE_UI* ui) {
  uiParent = ui;
}

//============================================================================================//

void textAreaClass:: initialize (int x, int y, int w, int h, uint16_t fgcolor, uint16_t bgcolor, uint16_t brcolor, String n) {
  name = n;
  areaX = x;
  areaY = y;
  areaWidth = w;
  areaHeight = h;
  areaFgColor = fgcolor;
  areaBgColor = bgcolor;
  areaBorderColor = brcolor;
  areaFgHoverColor = CSEUI_BUTTON_DEF_LABEL_HOVER_COLOR;
  areaBgHoverColor = CSEUI_BUTTON_DEF_FILL_HOVER_COLOR;
  areaBorderHoverColor = CSEUI_BUTTON_DEF_BORDER_HOVER_COLOR;
  text = "";
  areaVisible = true;
  borderThickness = 2;
  textEnabled = true;
  stateChanged = true;
}

//============================================================================================//

void textAreaClass:: draw() {
  if (areaVisible) {
    if (textEnabled) {
      if ((text != prevText) || stateChanged) { // Only redraw if the text has changed
        // First draw the main viewport
        uiParent->lcdParent->setViewport (areaX, areaY, areaWidth, areaHeight);
        uiParent->lcdParent->fillScreen (areaBgColor);
        uiParent->lcdParent->frameViewport (areaBorderColor, borderThickness);

        // Then draw the secondary viewport
        uiParent->lcdParent->setViewport (areaSecX, areaSecY, areaSecWidth, areaSecHeight);

        if (text.length() > 0) {
          uiParent->lcdParent->setTextColor (areaFgColor, areaBgColor);
          uiParent->lcdParent->print (text);
        }

        prevText = text;

        if (stateChanged) {
          stateChanged = false;
        }

        close();
      }
    }
  }
}

//============================================================================================//

void textAreaClass:: open() {
  if (areaVisible) {
    // Redraw the area if the state has changed
    // First draw the main viewport
    uiParent->lcdParent->setViewport (areaX, areaY, areaWidth, areaHeight);
    uiParent->lcdParent->fillScreen (areaBgColor);
    uiParent->lcdParent->frameViewport (areaBorderColor, borderThickness);

    // Then draw the secondary viewport
    uiParent->lcdParent->setViewport (areaSecX, areaSecY, areaSecWidth, areaSecHeight);
  }
}

//============================================================================================//

void textAreaClass:: update() {
  stateChanged = true;
}

//============================================================================================//

void textAreaClass:: reset() {
  stateChanged = true;
  close();
}

//============================================================================================//

void textAreaClass:: close() {
  uiParent->lcdParent->resetViewport();
}

//============================================================================================//
/**
 * @brief Enable the built-in text. This does not affect manual text drawing.
 * 
 */
void textAreaClass:: enableText() {
  textEnabled = true;
}

//============================================================================================//
/**
 * @brief Disable the built-in text. This does not affect manual text drawing.
 * 
 */
void textAreaClass:: disableText() {
  textEnabled = false;
}

//============================================================================================//
/**
 * @brief Set the built-in text. This does not affect manual text drawing.
 * 
 * @param str 
 */
void textAreaClass:: setText (String str) {
  if (str != text) {
    prevText = text;
    text = str;
    // stateChanged = true;
  }
}

//============================================================================================//
/**
 * @brief Append text to the built-in text. This does not affect manual text drawing.
 * 
 * @param str 
 */
void textAreaClass:: appendText (String str) {
  if (text != (text + str)) {
    prevText = text;
    text = text + str;
    // stateChanged = true;
  }
}

//============================================================================================//
/**
 * @brief Clear the built-in text. This does not affect manual text drawing.
 * 
 */
void textAreaClass:: clearText() {
  if (text != "") {
    prevText = text;
    text = "";
    // stateChanged = true;
  }
}

//============================================================================================//

void textAreaClass:: setAreaPadding (int l, int t, int r, int b) {
  paddingLeft = l;
  paddingTop = t;
  paddingRight = r;
  paddingBottom = b;

  if (paddingLeft > 0) {
    areaSecX = areaX + paddingLeft;
    areaSecWidth = areaWidth - paddingLeft;
  } else {
    areaSecX = areaX;
    areaSecWidth = areaWidth;
  }

  if (paddingTop > 0) {
    areaSecY = areaY + paddingTop;
    areaSecHeight = areaHeight - paddingTop;
  } else {
    areaSecY = areaY;
    areaSecHeight = areaHeight;
  }

  if (paddingRight > 0) {
    areaSecWidth = areaSecWidth - paddingRight;
  }

  if (paddingBottom > 0) {
    areaSecHeight = areaSecHeight - paddingBottom;
  }
}

//============================================================================================//
