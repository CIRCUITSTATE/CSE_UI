
//============================================================================================//
/*
  Filename: CSE_UI.cpp
  Description: Main source file for the CSE_UI Arduino library.
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 0.0.8
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_CST328
  Last Modified: +05:30 01:05:25 AM 02-03-2025, Sunday
 */
//============================================================================================//

#include "CSE_UI.h"

//============================================================================================//

CSE_UI:: CSE_UI (TFT_eSPI* lcd, CSE_Touch* ts) {
  lcdParent = lcd;
  tsParent = ts;
  currentPage = -1;
  prevPage = -1;
}

//============================================================================================//

pageClass:: pageClass (CSE_UI* ui, int page) {
  uiParent = ui;
  pageNum = page;
}

//============================================================================================//

void pageClass:: setInitFunction (funcPtr func) {
  initFunction = func;
}

//============================================================================================//

void pageClass:: setDrawFunction (funcPtr func) {
  drawFunction = func;
}

//============================================================================================//

bool pageClass:: init() {
  if (initFunction != NULL) {
    initFunction();
    return true;
  }
  return false;
}

//============================================================================================//

bool pageClass:: draw() {
  if (pageActive) {
    drawFunction();
    return true;
  }
  return false;
}

//============================================================================================//

bool pageClass:: isActive() {
  return pageActive;
}

//============================================================================================//

bool pageClass:: setActive() {
  pageActive = true;
  return pageActive;
}

//============================================================================================//

bool pageClass:: setInactive() {
  pageActive = false;
  return pageActive;
}

//============================================================================================//
