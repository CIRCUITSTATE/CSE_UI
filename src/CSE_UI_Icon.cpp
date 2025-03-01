
//============================================================================================//
/*
  Filename: CSE_UI_Icon.cpp
  Description: Icon support source file for the CSE_UI Arduino library.
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 0.0.8
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_CST328
  Last Modified: +05:30 01:06:13 AM 02-03-2025, Sunday
 */
//============================================================================================//

#include "CSE_UI.h"

//============================================================================================//

iconClass:: iconClass (CSE_UI* ui) {
  uiParent = ui;
}

//============================================================================================//
/**
 * @brief Constructor for FontAwesome icon font, with LCD parent.
 * 
 * @param array The icon data array.
 * @param w Icon width.
 * @param h Icon height.
 * @param byteLen The number of bytes per character
 * @param byteCount The total number of vertical bytes needed.
 * @param unicode The Unicode ID of the icon.
 * @param n Name of the icon.
 * @param lcd Parent LCD object.
 * 
 * @return iconClass:: 
 */
void iconClass:: initialize (const char* array, int w, int h, int byteLen, int byteCount, uint32_t unicode, String n) {
  fontArray = array;
  fontWidth = w;
  fontHeight = h;
  charByteLength = byteLen;
  verticalByteCount = byteCount;
  unicodeId = unicode;
  name = n;
  glyphWidth = 0;
  glyphHeight = 0;
  glyphX = 0;
  glyphY = 0;
}

//============================================================================================//
/**
 * @brief Draws a FontAwesome icon to the screen without background color.
 * 
 * @param icon A FontAwesome icon.
 * @param x X coordinate of the icon (top-left).
 * @param y Y coordinate of the icon (top-left).
 * @param color 16-bit color value.
 */
void iconClass:: draw (int16_t x, int16_t y, uint16_t color) {

  char verticalByte = 0; //for vertical bytes

  //iterate through the _width of the glyph
  for (int i = 0; i < (fontArray [0]); i++) { //finds start of each set of vertical bytes
    //get a single set of vertical bytes
    for (int j = 0; j < verticalByteCount; j++) {
      verticalByte = fontArray [(j + 1) + (i * verticalByteCount)]; //copy the set of vertical bytes
      if (verticalByte != 0) { //don't display if a byte is zero
        for (int m = 0; m < 8; m++) { //iterates through each pixel of a byte
          if ((unsigned (verticalByte >> m)) & 0x1) { //check if a bit is 1
            uiParent->lcdParent->drawPixel ((x + i), y + m + (8 * j), color); //if a bit is 1, then draw pixel with color
          }
        }
      }
    }
  }
}

//============================================================================================//
/**
 * @brief Gets the width, height and offsets of a icon, char or string in pixels.
 * An offset is simply how many lines of empty pixels are before a valid black pixel.
 * The calculated values are stored in the global variables glyphWidth, glyphHeight,
 * glyphX and glyphY.
 * 
 */
void iconClass:: getSize() {
  char verticalByte = 0; //for vertical bytes

  bool areAllBytesZero = true; //whether all bytes in a verticl set are zero
  bool nonZeroByteFound = false; //whether any non-zero bytes found in any vertical set

  int glyphOffsetLeft = 0;
  int glyphOffsetTop = -1; //-1 so that we can have a start condition without conflicting with actual 0 offset value
  int glyphOffsetBottom = 0;
  int glyphOffsetRight = 0;

  //iterate through the width of the glyph
  for (int i = 0; i < (fontArray [0]); i++) { //finds start of each set of vertical bytes
    //get a single set of vertical bytes
    for (int j = 0; j < verticalByteCount; j++) {
      verticalByte = fontArray [(j + 1) + (i * verticalByteCount)]; //copy the set of vertical bytes
      if (verticalByte != 0) { //don't display if a byte is zero
        areAllBytesZero = false;
        nonZeroByteFound = true;
        glyphOffsetRight = i; //if there's a non-zero vertical byte in a cloumn, save it. This will eventually find the right-most pixel
        for (int m = 0; m < 8; m++) { //iterates through each pixel of a byte
          if ((unsigned (verticalByte >> m)) & 0x1) { //check if a bit is 1
            if (glyphOffsetTop < 0) glyphOffsetTop = (j * 8) + m; //assign the location of the first pixel found
            else if (glyphOffsetTop > ((j * 8) + m)) glyphOffsetTop = (j * 8) + m; //now check if any pixel higher than previous found
            if (glyphOffsetBottom < ((j * 8) + m)) glyphOffsetBottom = (j * 8) + m;
          }
        }
      }
    }

    if (areAllBytesZero && (!nonZeroByteFound)) {
      glyphOffsetLeft++;
    }
    areAllBytesZero = true;
  }

  if (glyphOffsetTop < 0) glyphOffsetTop = 0;

  glyphX = glyphOffsetLeft;
  glyphY = glyphOffsetTop;

  // glyphOffsetRight = fontWidth - (glyphOffsetRight + 1); //find the Right offset from right-most pixel location
  // glyphOffsetBottom = fontHeight - (glyphOffsetBottom + 1);

  glyphWidth = fontWidth - (glyphOffsetLeft + (fontWidth - (glyphOffsetRight + 1)));
  glyphHeight = fontHeight - (glyphOffsetTop + (fontHeight - (glyphOffsetBottom + 1)));

  // Serial.print("getSize(icon) - ");
  // Serial.println(name);
  // Serial.print("glyphWidth = ");
  // Serial.println(glyphWidth);
  // Serial.print("glyphHeight = ");
  // Serial.println(glyphHeight);
  // Serial.print("glyphX = ");
  // Serial.println(glyphX);
  // Serial.print("glyphY = ");
  // Serial.println(glyphY);
}