
//============================================================================================//
/*
  Filename: CSE_UI_Button.cpp
  Description: Button support source file for the CSE_UI Arduino library.
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 0.0.8
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_CST328
  Last Modified: +05:30 01:08:48 AM 02-03-2025, Sunday
 */
//============================================================================================//

#include "CSE_UI.h"

//============================================================================================//
/**
 * @brief Constructor for the buttonClass object. It accepts a pointer to the UI
 * parent. You should create a UI object before calling this constructor.
 * 
 * @param ui A UI parent of type CSE_UI.
 * @return buttonClass:: 
 */
buttonClass:: buttonClass (CSE_UI* ui) {
  uiParent = ui;
}

//============================================================================================//
/**
 * @brief Initializes a button object. Call this after the constructor. Only the most
 * important parameters are required here. Other parameters are initilized to default
 * values. They can be changed later if needed.
 * 
 * @param x X-coordinate of top-left of the button.
 * @param y Y-coordinate of top-left of the button.
 * @param w Width of the button in pixels.
 * @param h Height of the button in pixels.
 * @param flcolor Button fill color. Not the same as background color (bgcolor).
 * @param lbcolor Button label color (foreground color or text color).
 * @param label Button label as a String.
 */
void buttonClass:: initialize (int16_t x,int16_t y, int16_t w, int16_t h, uint16_t flcolor, uint16_t lbcolor, String label) {
  buttonX = x;
  buttonY = y;
  buttonWidth = w;
  buttonHeight = h;
  radius = CSEUI_BUTTON_DEF_RADIUS;
  borderColor = CSEUI_BUTTON_DEF_BORDER_COLOR;
  borderHoverColor = CSEUI_BUTTON_DEF_BORDER_HOVER_COLOR;
  fillColor = flcolor;
  fillHoverColor = CSEUI_BUTTON_DEF_FILL_HOVER_COLOR;
  labelString = label;
  labelOffsetX = 0;
  labelOffsetY = 0;
  labelAlign = CSEUI_BUTTON_ALIGN_MC;
  icon = NULL;  // No icon by default.
  iconOffsetX = 0;
  iconOffsetY = 0;
  iconAlign = CSEUI_BUTTON_ALIGN_MC;
  labelColor = lbcolor;
  labelHoverColor = CSEUI_BUTTON_DEF_LABEL_HOVER_COLOR;
  iconColor = CSEUI_BUTTON_DEF_ICON_COLOR;
  iconHoverColor = CSEUI_BUTTON_DEF_ICON_HOVER_COLOR;
  buttonVisible = true;
  buttonEnabled = true;
  borderVisible = false;
  fillVisible = true;
  labelVisible = true;
  iconVisible = false;
  buttonHoverEnabled = true;
  borderHoverEnabled = false;
  fillHoverEnabled = true;
  labelHoverEnabled = true;
  iconHoverEnabled = false;
  currentTouchState = false;
  prevTouchState = false;
  stateChange = true; // So that icon will be drawn the first time
  activeState = false;
}

//============================================================================================//
/**
 * @brief Draws the button on the screen. The button is drawn only if there is a state
 * change. This is to avoid flickering from continuous redrawing. A state change can
 * be triggered by updating the label string or touching the button, for example.
 * Parts of the button are drawn accoring to their visibility settings.
 * 
 */
void buttonClass:: draw() {
  if (buttonVisible) {
    if (buttonHoverEnabled && (!stateChange) && (buttonEnabled) && isTouched()) {
      if (stateChange) { // Only draw if there is a state change
        if (fillVisible) {
          if (fillHoverEnabled) {
            if (buttonEnabled) {
              uiParent->lcdParent->fillSmoothRoundRect (buttonX, buttonY, buttonWidth, buttonHeight, radius, fillHoverColor);
            }
            else {
              uiParent->lcdParent->fillSmoothRoundRect (buttonX, buttonY, buttonWidth, buttonHeight, radius, CSEUI_BUTTON_DEACTIVATE_BG_COLOR);
            }
          }
          else {
            if (buttonEnabled) {
              uiParent->lcdParent->fillSmoothRoundRect (buttonX, buttonY, buttonWidth, buttonHeight, radius, fillColor);
            }
            else {
              uiParent->lcdParent->fillSmoothRoundRect (buttonX, buttonY, buttonWidth, buttonHeight, radius, CSEUI_BUTTON_DEACTIVATE_BG_COLOR);
            }
          }
        }
        if (borderVisible) {
          if (borderHoverEnabled) {
            if (buttonEnabled) {
              uiParent->lcdParent->drawSmoothRoundRect (buttonX, buttonY, radius, radius-1, buttonWidth, buttonHeight, borderHoverColor);
            }
            else {
              uiParent->lcdParent->drawSmoothRoundRect (buttonX, buttonY, radius, radius-1, buttonWidth, buttonHeight, CSEUI_BUTTON_DEACTIVATE_FG_COLOR);
            }
          }
          else {
            if (buttonEnabled) {
              uiParent->lcdParent->drawSmoothRoundRect (buttonX, buttonY, radius, radius-1, buttonWidth, buttonHeight, borderColor);
            }
            else {
              uiParent->lcdParent->drawSmoothRoundRect (buttonX, buttonY, radius, radius-1, buttonWidth, buttonHeight, CSEUI_BUTTON_DEACTIVATE_FG_COLOR);
            }
          }
        }

        if (iconVisible) {
          icon->getSize();

          if (iconHoverEnabled) {
            if (iconAlign == CSEUI_BUTTON_ALIGN_TC) { //top center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY - icon->glyphY, iconHoverColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else if (iconAlign == CSEUI_BUTTON_ALIGN_RC) { //right center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int(buttonWidth - icon->glyphWidth)), buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconHoverColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int(buttonWidth - icon->glyphWidth)), buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else if (iconAlign == CSEUI_BUTTON_ALIGN_BC) { //bottom center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int(buttonHeight - icon->glyphHeight)) - icon->glyphY, iconHoverColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int(buttonHeight - icon->glyphHeight)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else if (iconAlign == CSEUI_BUTTON_ALIGN_LC) { //left center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconHoverColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else { //center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconHoverColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
          }
          else {
            if (iconAlign == CSEUI_BUTTON_ALIGN_TC) { //top center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY - icon->glyphY, iconColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else if (iconAlign == CSEUI_BUTTON_ALIGN_RC) { //right center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int(buttonWidth - icon->glyphWidth)), buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int(buttonWidth - icon->glyphWidth)), buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else if (iconAlign == CSEUI_BUTTON_ALIGN_BC) { //bottom center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int(buttonHeight - icon->glyphHeight)) - icon->glyphY, iconColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int(buttonHeight - icon->glyphHeight)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else if (iconAlign == CSEUI_BUTTON_ALIGN_LC) { //left center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
            else { //center
              if (buttonEnabled) {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconColor);
              }
              else {
                icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
              }
            }
          }
        }

        if (labelVisible) {
          // int16_t stringWidth = uiParent->lcdParent->textWidth (labelString);
          
          // Decide the colors for the label
          if (labelHoverEnabled) { // For hover state
            if (buttonEnabled) { // For functional state
              uiParent->lcdParent->setTextColor (labelHoverColor, fillHoverColor);
            }
            else { // For disabled state
              uiParent->lcdParent->setTextColor (CSEUI_BUTTON_DEACTIVATE_FG_COLOR, CSEUI_BUTTON_DEACTIVATE_BG_COLOR);
            }
          }
          else { // If not hovered/touched
            uiParent->lcdParent->setTextColor (labelColor, fillHoverColor);
          }

          // Start determinging the alignement and draw the strings accordingly

          if (labelAlign == CSEUI_BUTTON_ALIGN_TC) { //top center
            uiParent->lcdParent->setTextDatum (TC_DATUM); // Set the string alignment to Top-Center
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + (int(buttonWidth/2)), buttonY + labelOffsetY);
          }

          else if (labelAlign == CSEUI_BUTTON_ALIGN_RC) { //right center
            uiParent->lcdParent->setTextDatum (MR_DATUM); // Set the string alignment to Middle-Right
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + buttonWidth, buttonY + labelOffsetY + (int(buttonHeight/2)));
          }

          else if (labelAlign == CSEUI_BUTTON_ALIGN_BC) { //bottom center
            uiParent->lcdParent->setTextDatum (BC_DATUM); // Set the string alignment to Bottom-Center
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + (int(buttonWidth/2)), buttonY + labelOffsetY + buttonHeight);
          }

          else if (labelAlign == CSEUI_BUTTON_ALIGN_LC) { //left center
            uiParent->lcdParent->setTextDatum (ML_DATUM); // Set the string alignment to Middle-Left
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX, buttonY + labelOffsetY + (int(buttonHeight/2)));
          }
          else { //center
            uiParent->lcdParent->setTextDatum (MC_DATUM); // Set the string alignment to Middle-Center
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + (int(buttonWidth/2)), buttonY + labelOffsetY + (int(buttonHeight/2)));
          }
        }
        updateState (false);
      }
    }

    else {
      if (stateChange) {
        if (fillVisible) {
          if (buttonEnabled) {
            uiParent->lcdParent->fillSmoothRoundRect (buttonX, buttonY, buttonWidth, buttonHeight, radius, fillColor);
          }
          else {
            uiParent->lcdParent->fillSmoothRoundRect (buttonX, buttonY, buttonWidth, buttonHeight, radius, CSEUI_BUTTON_DEACTIVATE_BG_COLOR);
          }
        }

        if (borderVisible) {
          if (buttonEnabled) {
            uiParent->lcdParent->drawSmoothRoundRect (buttonX, buttonY, radius, radius-1, buttonWidth, buttonHeight, borderColor);
          }
          else {
            uiParent->lcdParent->drawSmoothRoundRect (buttonX, buttonY, radius, radius-1, buttonWidth, buttonHeight, CSEUI_BUTTON_DEACTIVATE_BG_COLOR);
          }
        }

        if (iconVisible) {
          icon->getSize();
          if (iconAlign == CSEUI_BUTTON_ALIGN_TC) { //top center
            if (buttonEnabled) {
              icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY - icon->glyphY, iconColor);
            }
            else {
              icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
            }
          }
          else if (iconAlign == CSEUI_BUTTON_ALIGN_RC) { //right center
            if (buttonEnabled) {
              icon->draw (buttonX + iconOffsetX + (int(buttonWidth - icon->glyphWidth)), buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconColor);
            }
            else {
              icon->draw (buttonX + iconOffsetX + (int(buttonWidth - icon->glyphWidth)), buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
            }
          }
          else if (iconAlign == CSEUI_BUTTON_ALIGN_BC) { //bottom center
            if (buttonEnabled) {
              icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int(buttonHeight - icon->glyphHeight)) - icon->glyphY, iconColor);
            }
            else {
              icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int(buttonHeight - icon->glyphHeight)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
            }
          }
          else if (iconAlign == CSEUI_BUTTON_ALIGN_LC) { //left center
            if (buttonEnabled) {
              icon->draw (buttonX + iconOffsetX - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconColor);
            }
            else {
              icon->draw (buttonX + iconOffsetX - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
            }
          }
          else { //center
            if (buttonEnabled) {
              icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, iconColor);
            }
            else {
              icon->draw (buttonX + iconOffsetX + (int((buttonWidth - icon->glyphWidth)/2)) - icon->glyphX, buttonY + iconOffsetY + (int((buttonHeight - icon->glyphHeight)/2)) - icon->glyphY, CSEUI_BUTTON_DEACTIVATE_FG_COLOR); //no need of bgcolor color
            }
          }
        }

        if (labelVisible) {
          // Determine the colors of the label
          if (buttonEnabled) { // For functional state
            uiParent->lcdParent->setTextColor (labelColor, fillColor);
          }
          else { // For disabled state
            uiParent->lcdParent->setTextColor (CSEUI_BUTTON_DEACTIVATE_FG_COLOR, CSEUI_BUTTON_DEACTIVATE_BG_COLOR);
          }

          // Determine the alignment of the lable and start drawing
          if (labelAlign == CSEUI_BUTTON_ALIGN_TC) { //top center
            uiParent->lcdParent->setTextDatum (TC_DATUM); // Set the string alignment to Top-Center
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + (int(buttonWidth/2)), buttonY + labelOffsetY);
          }
          else if (labelAlign == CSEUI_BUTTON_ALIGN_RC) { //right center
            uiParent->lcdParent->setTextDatum (MR_DATUM); // Set the string alignment to Middle-Right
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + buttonWidth, buttonY + labelOffsetY + (int(buttonHeight/2)));
          }
          else if (labelAlign == CSEUI_BUTTON_ALIGN_BC) { //bottom center
            uiParent->lcdParent->setTextDatum (BC_DATUM); // Set the string alignment to Bottom-Center
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + (int(buttonWidth/2)), buttonY + labelOffsetY + buttonHeight);
          }
          else if (labelAlign == CSEUI_BUTTON_ALIGN_LC) { //left center
            uiParent->lcdParent->setTextDatum (ML_DATUM); // Set the string alignment to Middle-Left
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX, buttonY + labelOffsetY + (int(buttonHeight/2)));
          }
          else { //center
            uiParent->lcdParent->setTextDatum (MC_DATUM); // Set the string alignment to Middle-Center
            // Now draw the string
            uiParent->lcdParent->drawString (labelString, buttonX + labelOffsetX + (int(buttonWidth/2)), buttonY + labelOffsetY + (int(buttonHeight/2)));
          }
        }
        updateState (false);
      }
    }

    // if(buttonPressed()) {
    //   Serial.print("Pressed ");
    //   Serial.println(labelString);
    // }
  }
}

//============================================================================================//
/**
 * @brief Check if the button is currently being touched.
 * 
 * @return true 
 * @return false 
 */
bool buttonClass:: isTouched() {
  if (uiParent->tsParent->isTouched (0)) { // Check if lcd is being touched
    CSE_TouchPoint p = uiParent->tsParent->getPoint(); // Get the touched point

    // Serial.print ("X = ");
    // Serial.print (p.x);
    // Serial.print (", Y = ");
    // Serial.print (p.y);
    // Serial.print (", Z = ");
    // Serial.print (p.z);
    // Serial.print (", Bx = ");
    // Serial.print (buttonX);
    // Serial.print (", By = ");
    // Serial.println (buttonY);

    if ((p.x >= buttonX) && (p.x < (buttonX + buttonWidth)) && (p.y >= buttonY) && (p.y < (buttonY + buttonHeight)) && (p.z >= CSEUI_TOUCH_PRESSURE_THRESHOLD)) {
      // Serial.println ("Button Touched");
      stateChange = currentTouchState ? false: true;
      currentTouchState = true;
      prevTouchState = true;
      return true;
    }
  }
  stateChange = currentTouchState ? true: false;
  currentTouchState = false;
  return false;
}

//============================================================================================//
/**
 * @brief Check if the button is pressed once. Pressing the butto requires touching the
 * button and then releasing it.
 * 
 * @return true 
 * @return false 
 */
bool buttonClass:: isPressed() {
  if ((!currentTouchState) && (prevTouchState)) {
    prevTouchState = false;
    return true;
  }
  else return false;
}

//============================================================================================//
/**
 * @brief Make the button visible. This operation does not trigger a state change.
 * The button will be drawn on the screen in the next draw() call.
 * 
 */
void buttonClass:: show() {
  buttonVisible = true;
}

//============================================================================================//
/**
 * @brief Hide the button. This operation does not trigger a state change.
 * You have to clear the button area with a background color manually.
 * 
 */
void buttonClass:: hide() {
  buttonVisible = false;
}

//============================================================================================//
/**
 * @brief A button can be enabled or disabled when it is still visible on the screen.
 * A disabled button will not respond to touch events. It will also have a different
 * color, usually grey.
 * 
 */
void buttonClass:: disable() {
  buttonEnabled = false;
}

//============================================================================================//
/**
 * @brief Enable the button. This is the default state of a button.
 * 
 */
void buttonClass:: enable() {
  buttonEnabled = true;
}

//============================================================================================//
/**
 * @brief Resets the states of the button. This is usually called when the button has
 * to be redrawn, for example when a page is changed.
 * 
 */
void buttonClass:: reset() {
  currentTouchState = false;
  prevTouchState = false;
  stateChange = true;
  // activeState = false;
}

//============================================================================================//
/**
 * @brief Clears the button area with a background color.
 * 
 * @param bgColor 
 */
void buttonClass:: clear (uint32_t bgColor) {
  uiParent->lcdParent->fillSmoothRoundRect (buttonX, buttonY, buttonWidth, buttonHeight, radius, bgColor, bgColor);
}

//============================================================================================//
/**
 * @brief Sets the XY coordinates of the button.
 * 
 * @param x 
 * @param y 
 */
void buttonClass:: setXY (int x, int y) {
  buttonX = x;
  buttonY = y;
}

//============================================================================================//
/**
 * @brief Enables the hover effect for the whole button.
 * 
 */
void buttonClass:: hoverEnable() {
  buttonHoverEnabled = true;
}

//============================================================================================//
/**
 * @brief Disables the hover effect for the whole button.
 * 
 */
void buttonClass:: hoverDisable() {
  buttonHoverEnabled = false;
}

//============================================================================================//
/**
 * @brief Make the button border visible.
 * 
 */
void buttonClass:: showBorder() {
  borderVisible = true;
}

//============================================================================================//
/**
 * @brief Hide the button border.
 * 
 */
void buttonClass:: hideBorder() {
  borderVisible = false;
}

//============================================================================================//
/**
 * @brief Enable the hover effect for the button border.
 * 
 */
void buttonClass:: borderHoverDisable() {
  borderHoverEnabled = false;
}

//============================================================================================//
/**
 * @brief Disable the hover effect for the button border.
 * 
 */
void buttonClass:: borderHoverEnable() {
  borderHoverEnabled = true;
}

//============================================================================================//
/**
 * @brief Make the button fill visible.
 * 
 */
void buttonClass:: showFill() {
  fillVisible = true;
}

//============================================================================================//
/**
 * @brief Hide the button fill.
 * 
 */
void buttonClass:: hideFill() {
  fillVisible = false;
}

//============================================================================================//
/**
 * @brief Enable the hover effect for the button fill.
 * 
 */
void buttonClass:: fillHoverEnable() {
  fillHoverEnabled = true;
}

//============================================================================================//
/**
 * @brief Disable the hover effect for the button fill.
 * 
 */
void buttonClass:: fillHoverDisable() {
  fillHoverEnabled = false;
}

//============================================================================================//
/**
 * @brief Make the button label visible.
 * 
 */
void buttonClass:: showLabel() {
  labelVisible = true;
}

//============================================================================================//
/**
 * @brief Hide the button label.
 * 
 */
void buttonClass:: hideLabel() {
  labelVisible = false;
}

//============================================================================================//
/**
 * @brief Enable the hover effect for the button label.
 * 
 */
void buttonClass:: labelHoverEnable() {
  labelHoverEnabled = true;
}

//============================================================================================//
/**
 * @brief Disable the hover effect for the button label.
 * 
 */
void buttonClass:: labelHoverDisable() {
  labelHoverEnabled = false;
}

//============================================================================================//
/**
 * @brief Make the button icon visible, if there is one.
 * 
 */
void buttonClass:: showIcon() {
  iconVisible = true;
}

//============================================================================================//
/**
 * @brief Hide the button icon.
 * 
 */
void buttonClass:: hideIcon() {
  iconVisible = false;
}

//============================================================================================//
/**
 * @brief Enable the hover effect for the button icon.
 * 
 */
void buttonClass:: iconHoverEnable() {
  iconHoverEnabled = true;
}

//============================================================================================//
/**
 * @brief Disable the hover effect for the button icon.
 * 
 */
void buttonClass:: iconHoverDisable() {
  iconHoverEnabled = false;
}

//============================================================================================//
/**
 * @brief Updates the current state of the button. Used to trigger a state change, or
 * disable it after an operation.
 * 
 * @param state 
 */
void buttonClass:: updateState (bool state) {
  stateChange = state;
}

//============================================================================================//
/**
 * @brief Get the current state of the button.
 * 
 * @return true 
 * @return false 
 */
bool buttonClass:: getState() {
  return stateChange;
}

//============================================================================================//
/**
 * @brief A button can enter an intermediate state after touched. This can be used to
 * toggle the state of the button, for example change the color after touched. But you
 * have to do that manually.
 * 
 */
void buttonClass:: activate() {
  activeState = true;
}

//============================================================================================//
/**
 * @brief Deactivate the intermediate state of the button.
 * 
 */
void buttonClass:: deactivate() {
  activeState = false;
}

//============================================================================================//
/**
 * @brief Toggle the intermediate state of the button.
 * 
 */
void buttonClass:: toggleState() {
  activeState = activeState ? false: true;
}

//============================================================================================//
// /**
//  * @brief Set the intermediate state of the button.
//  * 
//  * @param toggle 
//  */
// void buttonClass:: toggleState (bool toggle) {
//   if (toggle) activeState = activeState ? false: true;
// }

//============================================================================================//