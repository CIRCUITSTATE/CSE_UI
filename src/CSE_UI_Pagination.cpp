
//===================================================================================//

#include "CSE_UI.h"

//===================================================================================//
/**
 * @brief Constructor for the paginationClass object. It accepts a pointer to the UI
 * parent and also initializes the button object with it.
 * 
 * @param ui 
 * @return paginationClass:: 
 */
paginationClass:: paginationClass (CSE_UI* ui) : button (ui) {
  uiParent = ui;
}

//===================================================================================//
/**
 * @brief Initializes a pagination object. Call this after the constructor.
 * A pagination object uses the buttonClass to display the page number.
 * 
 * @param x X-coordinate of top-left of the pagination.
 * @param y Y-coordinate of top-left of the pagination.
 * @param w Width in pixels.
 * @param h Height in pixels.
 * @param max Maximum pagination number.
 * @param flcolor Fill color.
 * @param lbcolor Label color.
 * @param brcolor Border color.
 */
void paginationClass:: initialize (int x, int y, int w, int h, int max, uint16_t flcolor, uint16_t lbcolor, uint16_t brcolor) {
  button.initialize (x, y, w, h, flcolor, lbcolor, "");
  button.borderColor = brcolor;
  maxValue = max;
  startValue = 1;
  currentValue = 1;
  button.labelString = String (currentValue) + "/" + String (maxValue);
}

//===================================================================================//
/**
 * @brief Make the pagination indicator visible.
 * 
 */
void paginationClass:: show() {
  button.show();
}

//===================================================================================//
/**
 * @brief Hide the pagination indicator.
 * 
 */
void paginationClass:: hide() {
  button.hide();
}

//===================================================================================//
/**
 * @brief Enable the pagination indicator.
 * 
 */
void paginationClass:: enable() {
  button.enable();
}

//===================================================================================//
/**
 * @brief Disable the pagination indicator. Disabling will cause the indicator to be
 * frozen.
 * 
 */
void paginationClass:: disable() {
  button.disable();
}

//===================================================================================//
/**
 * @brief Draw the pagination indicator. Call this in any loop function. The indicator
 * will only be redrawn if there is a state change such as incrementing or decrementing
 * the page number.
 * 
 */
void paginationClass:: draw() {
  button.draw();
}

//===================================================================================//
/**
 * @brief Set the current value of the pagination indicator.
 * 
 * @param value The value to be set. Must be between startValue and maxValue.
 */
void paginationClass:: setCurrentValue (int value) {
  if ((value < startValue) || (value > maxValue)) { // Check the value bounds
    return;
  }
  currentValue = value;
  button.labelString = String (currentValue) + "/" + String (maxValue);
  button.updateState (true);
}

//===================================================================================//
/**
 * @brief Returns the current value of the pagination indicator.
 * 
 * @return int 
 */
int paginationClass:: getCurrentValue() {
  return currentValue;
}

//===================================================================================//
/**
 * @brief Set the maximum value of the pagination indicator.
 * 
 * @param value 
 */
void paginationClass:: setMaxValue (int value) {
  if (value < startValue) { // Check the value bounds
    return;
  }
  maxValue = value;
  button.labelString = String (currentValue) + "/" + String (maxValue);
  button.updateState (true);
}

//===================================================================================//
/**
 * @brief Returns the maximum value of the pagination indicator.
 * 
 * @return int 
 */
int paginationClass:: getMaxValue() {
  return maxValue;
}

//===================================================================================//
/**
 * @brief Set the start value of the pagination indicator.
 * 
 * @param value 
 */
void paginationClass:: setStartValue (int value) {
  if (value > maxValue) { // Check the value bounds
    return;
  }
  startValue = value;
}

//===================================================================================//
/**
 * @brief Returns the start value of the pagination indicator.
 * 
 * @return int 
 */
int paginationClass:: getStartValue() {
  return startValue;
}

//===================================================================================//
/**
 * @brief Increment the pagination indicator by 1.
 * 
 */
void paginationClass:: increment() {
  if (currentValue < maxValue) {
    currentValue++;
    button.labelString = String (currentValue) + "/" + String (maxValue);
    button.updateState (true);
  }
}

//===================================================================================//
/**
 * @brief Decrement the pagination indicator by 1.
 * 
 */
void paginationClass:: decrement() {
  if (currentValue > startValue) {
    currentValue--;
    button.labelString = String (currentValue) + "/" + String (maxValue);
    button.updateState (true);
  }
}

//===================================================================================//
/**
 * @brief Reset the pagination indicator to the start value.
 * 
 */
void paginationClass:: reset() {
  currentValue = startValue;
  button.labelString = String (currentValue) + "/" + String (maxValue);
  button.updateState (true);
}

//===================================================================================//
/**
 * @brief Returns the pagination indicator as "currentValue/maxValue".
 * 
 * @return String 
 */
String paginationClass:: getString() {
  return button.labelString;
}

//===================================================================================//
