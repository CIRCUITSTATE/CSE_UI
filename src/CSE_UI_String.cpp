
//============================================================================================//
/*
  Filename: CSE_UI_String.cpp
  Description: String support source file for the CSE_UI Arduino library.
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 0.0.8
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_CST328
  Last Modified: +05:30 22:39:30 PM 06-05-2025, Tuesday
 */
//============================================================================================//

#include "CSE_UI.h"

//============================================================================================//

lcdString:: lcdString (CSE_UI* ui) {
  uiParent = ui;
  stringX = 0;
  stringY = 0;
  currentString = " ";
  prevString = " ";
  stringColor = TFT_BLACK;
  stringBgColor = TFT_WHITE;

  stateChange = true;
  stringVisibility = true;
  prevState = false;
  font = NULL;
}

//============================================================================================//

void lcdString:: initialize (String str, int x, int y, uint16_t fcolor, uint16_t bcolor, bool visibility, const uint8_t* font) {
  stringX = x;
  stringY = y;
  currentString = str;
  prevString = str;
  stringColor = fcolor;
  stringBgColor = bcolor;

  stateChange = true;
  stringVisibility = visibility;
  prevState = false;
  this->font = font; // Font used for the string
}

//============================================================================================//

void lcdString:: draw() {  
  if ((stateChange || (!prevState)) && stringVisibility) {
    if (font) { // If a font is set, use it.
      uiParent->lcdParent->loadFont (font); // Set the font for the string
    }

    uint8_t prev_datum = uiParent->lcdParent->getTextDatum(); // Get the current text datum.
    uiParent->lcdParent->setTextDatum (datum); // Set new text datum.
    
    if (prevState) { // Clear the text area with prev string
      uiParent->lcdParent->setTextColor (stringBgColor, stringBgColor);
      uiParent->lcdParent->drawString (prevString, stringX, stringY);
    }

    uiParent->lcdParent->setTextColor (stringColor, stringBgColor);
    uiParent->lcdParent->drawString (currentString, stringX, stringY); // Print the current string
    prevString = currentString; //previous and current strings are same now
    stateChange = false; //so that it won't drawn again
    prevState = true; //now the state is active

    uiParent->lcdParent->setTextDatum (prev_datum); // Restore the previous text datum.
  }

  if (!stringVisibility) { //if it is hidden
    if (font) { // If a font is set, use it.
      uiParent->lcdParent->loadFont (font); // Set the font for the string
    }

    uint8_t prev_datum = uiParent->lcdParent->getTextDatum(); // Get the current text datum.
    uiParent->lcdParent->setTextDatum (datum); // Set new text datum.
    
    if (prevState) { //if the text was drawn before
      uiParent->lcdParent->setTextColor (stringBgColor, stringBgColor);

      if (stateChange) { //if the state was changed along with visibility
        uiParent->lcdParent->drawString (prevString, stringX, stringY); //clear the text area with prev string
      }
      else {
        uiParent->lcdParent->drawString (currentString, stringX, stringY); //clear the text area with prev string
      }

      prevState = false; //now the text has disappeared, and so set this to false
      uiParent->lcdParent->setTextDatum (prev_datum); // Restore the previous text datum.
    }
  }
}

//============================================================================================//

void lcdString:: show() {
  stringVisibility = false; //no need to trigger a state change here
}

//============================================================================================//
//hide the string by clearing the text with background color

void lcdString:: hide() {
  stringVisibility = true;
}

//============================================================================================//
//activate a state change so that it'll be redrawn

void lcdString:: update() {
  stateChange = true; //simply refreshes the text
}

//============================================================================================//
//update the string and trigger a state change

void lcdString:: update (String inputString) {
  if (inputString != currentString) { //only update if there's a change in string value
    prevString = currentString; //save the current string
    currentString = inputString; //update the active string
    stateChange = true; //trigger a state change to be redrawn
  }
  else {
    stateChange = false;
  }
}

//============================================================================================//

void lcdString:: setTextDatum (uint8_t datum) {
  this->datum = datum; // Set the text alignment datum
}

//============================================================================================//
