
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
  Last Modified: +05:30 01:07:36 AM 02-03-2025, Sunday
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
}

//============================================================================================//

void lcdString:: initialize (String str, int x, int y, uint16_t fcolor, uint16_t bcolor, bool visibility) {
  stringX = x;
  stringY = y;
  currentString = str;
  prevString = str;
  stringColor = fcolor;
  stringBgColor = bcolor;

  stateChange = true;
  stringVisibility = visibility;
  prevState = false;
}

//============================================================================================//

void lcdString:: draw() {
  if ((stateChange || (!prevState)) && stringVisibility) {
    if (prevState) {
      uiParent->lcdParent->setTextColor (stringBgColor, stringBgColor);
      uiParent->lcdParent->drawString (prevString, stringX, stringY); //clear the text area with prev string
    }

    uiParent->lcdParent->setTextColor (stringColor, stringBgColor);
    uiParent->lcdParent->drawString (currentString, stringX, stringY); //print the current string
    prevString = currentString; //previous and current strings are same now
    stateChange = false; //so that it won't drawn again
    prevState = true; //now the state is active
  }

  if (!stringVisibility) { //if it is hidden
    if (prevState) { //if the text was drawn before
      uiParent->lcdParent->setTextColor (stringBgColor, stringBgColor);

      if (stateChange) { //if the state was changed along with visibility
        uiParent->lcdParent->drawString (prevString, stringX, stringY); //clear the text area with prev string
      }
      else {
        uiParent->lcdParent->drawString (currentString, stringX, stringY); //clear the text area with prev string
      }

      prevState = false; //now the text has disappeared, and so set this to false
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
