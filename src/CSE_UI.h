
//============================================================================================//
/*
  Filename: CSE_UI.h
  Description: Main header file for the CSE_UI Arduino library.
  Framework: Arduino, PlatformIO
  Author: Vishnu Mohanan (@vishnumaiea, @vizmohanan)
  Maintainer: CIRCUITSTATE Electronics (@circuitstate)
  Version: 0.0.8
  License: MIT
  Source: https://github.com/CIRCUITSTATE/CSE_CST328
  Last Modified: +05:30 20:26:32 PM 05-05-2025, Monday
 */
//============================================================================================//

#ifndef CSE_UI_LIBRARY
#define CSE_UI_LIBRARY

//============================================================================================//

#include <CSE_Touch.h>
#include <TFT_eSPI.h>

#if defined(ARDUINO_ARCH_AVR)
  #include <ArduinoSTL.h>
#else
  #include <vector>
#endif

//============================================================================================//

#define   CSEUI_BUTTON_DEF_RADIUS                   3
#define   CSEUI_BUTTON_DEF_BORDER_COLOR             TFT_WHITE
#define   CSEUI_BUTTON_DEF_BORDER_HOVER_COLOR       TFT_BLACK
#define   CSEUI_BUTTON_DEF_FILL_HOVER_COLOR         TFT_YELLOW
#define   CSEUI_BUTTON_DEF_LABEL_HOVER_COLOR        TFT_BLACK
#define   CSEUI_BUTTON_DEF_ICON_COLOR               TFT_WHITE
#define   CSEUI_BUTTON_DEF_ICON_HOVER_COLOR         TFT_BLACK
#define   CSEUI_BUTTON_DEACTIVATE_FG_COLOR          TFT_BLACK
#define   CSEUI_BUTTON_DEACTIVATE_BG_COLOR          TFT_BLACK

// Only the center alignment options are given. Other alignments can be achieved by
// adding X/Y offset values.
#define   CSEUI_BUTTON_ALIGN_TC                     1   // Top Center
#define   CSEUI_BUTTON_ALIGN_RC                     2   // Right Center
#define   CSEUI_BUTTON_ALIGN_BC                     3   // Bottom Center
#define   CSEUI_BUTTON_ALIGN_LC                     4   // Left Center
#define   CSEUI_BUTTON_ALIGN_MC                     5   // Middle Center

#define   CSEUI_TOUCH_PRESSURE_THRESHOLD            0

//============================================================================================//

class CSE_UI {
  public:
    TFT_eSPI* lcdParent;
    CSE_Touch* tsParent;
  
    CSE_UI (TFT_eSPI* lcd, CSE_Touch* ts);
    int currentPage;
    int prevPage;
};

//============================================================================================//

class pageClass {
  private:
    bool pageActive;
    typedef void (*funcPtr)();
    funcPtr drawFunction;
    funcPtr initFunction;
  public:
    CSE_UI* uiParent;
    int pageNum;

    pageClass (CSE_UI* ui, int page);
    void setInitFunction (funcPtr func);
    void setDrawFunction (funcPtr func);
    bool isActive();
    bool setActive();
    bool setInactive();
    bool init();
    bool draw();
};

//============================================================================================//

class lcdString {
  private:
    CSE_UI* uiParent;
  public:
    uint16_t stringX; //x coordinate
    uint16_t stringY; //y coordinate
    // fontClass* stringFont; //font used
    String currentString; //the currently displayed string
    String prevString; //prev string which is used to clear the text area faster than filling a rectangle
    uint16_t stringColor;
    uint16_t stringBgColor; //bg color will be used to clear the text area
    uint8_t* font;

    bool stateChange; //set true to trigger a state change and thus causing the text to be redrawn
    bool stringVisibility; //show or hide the text
    bool prevState; //used to detect if the text was displayed before hiding it

    lcdString (CSE_UI* ui); //constructor
    void initialize (String str, int x, int y, uint16_t fcolor, uint16_t bcolor, bool visibility, uint8_t* font = NULL); //initilizes the object. call this from first function executed after restart
    void draw(); //draw the text to LCD
    void show(); //show the text
    void hide(); //hide the text. if text was previously drawn, the text area will be cleared with bg color
    void update(); //triggers a state change and redraws the text
    void update (String); //update the text with a new string and redraw it
};

//============================================================================================//

class boxClass {
  private:
    CSE_UI* uiParent;
  public:
    int boxX;
    int boxY;
    int width;
    int height;
    int radius;
    uint16_t boxBorderColor;
    uint16_t boxFillColor;
    uint16_t boxHoverColor;
    bool boxVisible;
    bool borderVisible;
    bool hoverEnabled;
};

//============================================================================================//

class iconClass {
  private:
    CSE_UI* uiParent;
  public:
    // friend class fontClass;
    friend class buttonClass;
    friend class boxClass;

    const char* fontArray;
    int fontWidth; //width of each char (don't worry; char widths are still variable)
    int fontHeight; //font height
    int charByteLength; //count of bytes for each char
    int verticalByteCount; //no. of vertical bytes needed for a char
    int glyphWidth;
    int glyphHeight;
    int glyphX;
    int glyphY;
    uint32_t unicodeId;
    String name;

    //------------------------------------------------------------------------//

    iconClass (CSE_UI* ui);
    void initialize (const char* array, int w, int h, int byteLen, int byteCount, uint32_t unicode, String str);
    void initialize (const char* font, uint32_t unicode, String name);
    void draw (int16_t x, int16_t y, uint16_t color);
    void getSize(); //calculates the absolute width and height of an icon
};

//============================================================================================//
/**
 * @brief Class for creating rectangular and rounded-rectangular buttons. Buttons can
 * have custom fill color, hover color, border, text, icon, etc. The buttonClass can
 * also be used for creating other items such as checkboxes, radio buttons, titles,
 * text box etc.
 * 
 */
class buttonClass {
  private:
    CSE_UI* uiParent; // Pointer to the parent CSE_UI object
  public:
    // friend class fontClass;
    friend class iconClass;
    friend class boxClass;

    int16_t buttonX;  // X-coordinate of the button
    int16_t buttonY; // Y-coordinate of the button
    int16_t buttonWidth; // Width of the button
    int16_t buttonHeight; // Height of the button
    int16_t radius; // Radius of the button corners
    uint16_t borderColor; // Color of the button border
    uint16_t borderHoverColor; // Color of the button border when hovered
    uint16_t fillColor; // Color of the button fill. This is not the same as a background color which should be behind the button.
    uint16_t fillHoverColor;  // Color of the button fill when hovered
    String labelString; // Text to be displayed on the button
    // fontClass* labelFont;
    int labelAlign; // Alignment of the text on the button
    int labelOffsetX; // X-offset of the text from the alignment point
    int labelOffsetY; // Y-offset of the text from the alignment point
    iconClass* icon;  // Pointer to the icon object
    int iconAlign;  // Alignment of the icon on the button
    int iconOffsetX;  // X-offset of the icon from the alignment point
    int iconOffsetY;  // Y-offset of the icon from the alignment point
    uint16_t labelColor;  // Color of the text
    uint16_t labelHoverColor; // Color of the text when hovered
    uint16_t iconColor; // Color of the icon
    uint16_t iconHoverColor;  // Color of the icon when hovered
    bool buttonVisible; // Show or hide the button
    bool buttonEnabled; // Enable or disable the button, when it is still visible
    bool borderVisible; // Show or hide the button border
    bool fillVisible; // Show or hide the button fill
    bool labelVisible;  // Show or hide the button text
    bool iconVisible;  // Show or hide the button icon
    bool buttonHoverEnabled; // Enable or disable the hover effect
    bool borderHoverEnabled;  // Enable or disable the hover effect on the border
    bool fillHoverEnabled;  // Enable or disable the hover effect on the fill
    bool labelHoverEnabled; // Enable or disable the hover effect on the text
    bool iconHoverEnabled;  // Enable or disable the hover effect on the icon
    bool prevTouchState;  // Previous touch state
    bool currentTouchState; // Current touch state
    bool stateChange; // Set true to trigger a state change and thus causing the button to be redrawn

    // A button can enter an intermediate state after touched. This can be used to toggle the
    // state of the button, for example change the color after touched. But you have to do that manually.
    bool activeState;

    //------------------------------------------------------------------------//
    // Function descriptions can be found in the .cpp file

    buttonClass (CSE_UI* ui);
    void initialize (int16_t x,int16_t y, int16_t w, int16_t h, uint16_t fcolor, uint16_t lcolor, String label);

    void draw();
    void show();
    void hide();
    void enable();
    void disable();
    void reset();
    void clear (uint32_t);
    void setXY (int, int);
    void hoverEnable();
    void hoverDisable();
    void showBorder();
    void hideBorder();
    void borderHoverDisable();
    void borderHoverEnable();
    void showFill();
    void hideFill();
    void fillHoverEnable();
    void fillHoverDisable();
    void showLabel();
    void hideLabel();
    void labelHoverEnable();
    void labelHoverDisable();
    void showIcon();
    void hideIcon();
    void iconHoverEnable();
    void iconHoverDisable();
    bool isTouched();
    bool isPressed();
    void updateState (bool);
    bool getState();
    void activate();
    void deactivate();
    void toggleState();
    // void toggleState (bool);
};

//============================================================================================//
/**
 * @brief Class for creating interactive and scrollable lists of items. Each list item
 * will be a button object. Any number of items can be added dynamically.
 * 
 */
class listClass {
  private:
    CSE_UI* uiParent;
    // buttonClass* itemList;
  public:
     // A dynamic list of button objects. You can create list items on the fly and add it to this list.
    std::vector<buttonClass*> itemList;

    int itemCount;  // The total number of items in the list.
    int16_t listX; // The top-left X-coordinate of the list
    int16_t listY; // The top-left Y-coordinate of the list
    int currentItem; // The global index of the currently selected/highlighted/focused item
    int prevItem; // The global index of the previously selected/highlighted item
    int currentVisibleItem; // The local index of the currently selected/highlighted/focused item
    int itemWidth;  // The global width of each item
    int itemHeight; // The global height of each item
    int itemVisibleCount; // The number of items that can be displayed at once
    int scrollPosition; // The current scroll position of the list
    uint16_t itemFgColor; // The color of the item text
    uint16_t itemBgColor; // The color of the item background/fill
    uint16_t itemFocusFgColor;  // The color of the item text/icon when focused
    uint16_t itemFocusBgColor;  // The color of the item background/fill when focused
    uint16_t itemHoverFgColor;  // The color of the item text/icon when hovered
    uint16_t itemHoverBgColor;  // The color of the item background/fill when hovered
    bool visible; // Show or hide the list

    // Function descriptions can be found in the .cpp file

    listClass (CSE_UI* ui);
    void initialize (int16_t x, int16_t y, int w, int h, uint16_t fgcolor, uint16_t bgcolor, uint16_t focusfg, uint16_t focusbg);
    void addItem (buttonClass* item, String label);
    void reset();
    void triggerStateChange();
    void setCurrentItem (int item);
    int getCurrentItem();
    void toNextItem();
    void toPrevItem();
    void scrollUp();
    void scrollDown();
    void setTextAlign (int datum);
    void setTextPadding (int xPad, int yPad);
    void draw();
    void show();
    void hide();
};

//============================================================================================//

class textAreaClass {
  private:
    CSE_UI* uiParent;
  public:
    int areaX;
    int areaY;
    int areaSecX; // Secondary area (viewport)
    int areaSecY;
    int areaWidth;
    int areaHeight;
    int areaSecWidth;
    int areaSecHeight;
    int paddingLeft;
    int paddingTop;
    int paddingRight;
    int paddingBottom;
    int borderThickness;
    String name;
    String text;
    String prevText;
    bool textEnabled;
    uint16_t areaFgColor;
    uint16_t areaFgHoverColor;
    uint16_t areaBgColor;
    uint16_t areaBgHoverColor;
    uint16_t areaBorderColor;
    uint16_t areaBorderHoverColor;
    bool areaVisible;
    bool stateChanged;

    textAreaClass (CSE_UI* ui);
    void initialize (int x, int y, int w, int h, uint16_t fgcolor, uint16_t bgcolor, uint16_t brcolor, String n);
    void open();
    void close();
    void draw();
    void update();
    void reset();
    void enableText();
    void disableText();
    void setText (String str);
    void appendText (String str);
    void clearText();

    void setAreaPadding (int l = 0, int t = 0, int r = 0, int b = 0);
};

//============================================================================================//
/**
 * @brief Class for creating a pagination indicator as "currentValue/maxValue".
 * This is useful for lists with selectable items such as menu options. This class
 * uses the buttonClass to create UI element.
 * 
 */
class paginationClass {
  private:
    CSE_UI* uiParent;
  public:
    buttonClass button; // A parent button object
    int startValue; // The starting value of the pagination indicator
    int maxValue; // The maximum value (last value) of the pagination indicator
    int currentValue; // The current value of the pagination indicator

    // Function descriptions can be found in the .cpp file
    paginationClass (CSE_UI* ui);
    void initialize (int x, int y, int w, int h, int max, uint16_t flcolor, uint16_t lbcolor, uint16_t brcolor);
    void show();
    void hide();
    void enable();
    void disable();
    void draw();
    void setCurrentValue (int val);
    int getCurrentValue();
    void setMaxValue (int val);
    int getMaxValue();
    void setStartValue (int val);
    int getStartValue();
    void increment();
    void decrement();
    void reset();
    String getString();
};

//============================================================================================//

#endif // CSE_UI_LIBRARY
