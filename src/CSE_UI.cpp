
//===================================================================================//

#include "CSE_UI.h"

//===================================================================================//

CSE_UI:: CSE_UI (TFT_eSPI* lcd, CSE_Touch* ts) {
  lcdParent = lcd;
  tsParent = ts;
  currentPage = -1;
  prevPage = -1;
}

//===================================================================================//

pageClass:: pageClass (CSE_UI* ui, int page) {
  uiParent = ui;
  pageNum = page;
}

//===================================================================================//

void pageClass:: setInitFunction (funcPtr func) {
  initFunction = func;
}

//===================================================================================//

void pageClass:: setDrawFunction (funcPtr func) {
  drawFunction = func;
}

//===================================================================================//

bool pageClass:: init() {
  if (initFunction != NULL) {
    initFunction();
    return true;
  }
  return false;
}

//===================================================================================//

bool pageClass:: draw() {
  if (pageActive) {
    drawFunction();
    return true;
  }
  return false;
}

//===================================================================================//

bool pageClass:: isActive() {
  return pageActive;
}

//===================================================================================//

bool pageClass:: setActive() {
  pageActive = true;
  return pageActive;
}

//===================================================================================//

bool pageClass:: setInactive() {
  pageActive = false;
  return pageActive;
}

//===================================================================================//
