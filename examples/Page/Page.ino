
//============================================================================================//

#include <Arduino.h>  // Standard libraries
#include <SPI.h>
#include <Wire.h>

#include <TFT_eSPI.h> // TFT LCD library
#include <CSE_CST328.h> // Touch controller
#include <CSE_UI.h>

//============================================================================================//

#define  CST328_PIN_RST     4
#define  CST328_PIN_INT     16

#define  LCD_ROTATION       3   // The LCD panel rotation
#define  TS_ROTATION        3   // The touch panel rotation

//============================================================================================//
// Globals

TFT_eSPI LCD = TFT_eSPI(); // Create a new TFT driver instance

// Add your touch controller here.
// This is written for the Waveshare 2.8" Capacitive LCD with CST328 touch controller.
// Create a new instance of the CST328 class.
// Parameters: Width, Height, &Wire, Reset pin, Interrupt pin
CSE_Touch* tsPanel = CSE_Touch_Driver:: createDriver (CSE_TOUCH_CST328, 240, 320, &Wire, TFT_RST);

// UI objects.
CSE_UI myui (&LCD, tsPanel);

// Pages
pageClass first_page (&myui, 0);
pageClass second_page (&myui, 1);

//============================================================================================//
// Forward Declarations

void setup (void);
void loop (void);

bool initWire (void);
bool initLCD (void);
bool initTouch (void);

void first_page_init (void);
void first_page_draw (void);

void second_page_init (void);
void second_page_draw (void);

//============================================================================================//
/**
 * @brief Setup runs once.
 * 
 */
void setup() {
  Serial.begin (115200);
  delay (2000);

  Serial.println();
  Serial.println (F("=== CSE_UI - Page Example ==="));

  // Initialize everything.
  initWire();
  initTouch();
  initLCD();

  Serial.println (F("setup [INFO]: System initialization complete."));
  Serial.println();

  delay (1000);
}

//============================================================================================//
/**
 * @brief Infinite loop.
 * 
 */
void loop() {
  Serial.println();
  first_page.draw();
  delay (50);
}

//============================================================================================//
/**
 * @brief Initialize the I2C/Wire interface.
 * 
 * @return true Initialization successful.
 * @return false Initialization failed.
 */
bool initWire (void) {
  Serial.print (F("initWire [INFO]: Initializing I2C.. "));
  Wire.begin();
  Serial.println (F("Done."));

  return true;
}

//============================================================================================//
/**
 * @brief Initializes the touch panel.
 * 
 * @return true Initialization successful.
 * @return false Initialization failed.
 */
bool initTouch (void) {
  Serial.print (F("initTouch [INFO]: Initializing touch panel.."));
  tsPanel->begin();
  tsPanel->setRotation (TS_ROTATION);

  // Attach the interrupt function.
  // attachInterrupt (digitalPinToInterrupt (CST328_PIN_INT), touchISR, FALLING);
  
  Serial.println (F("Done."));

  return true;
}

//============================================================================================//
/**
 * @brief Initializes the LCD.
 * 
 * @return true Initialization successful.
 * @return false Initialization failed.
 */
bool initLCD (void) {
  Serial.print (F("initLCD [INFO]: Initializing LCD.. "));

  pinMode (TFT_BL, OUTPUT);
  digitalWrite (TFT_BL, LOW); // Turn off the backlight
  
  LCD.begin();
  LCD.setRotation (LCD_ROTATION);
  LCD.setFreeFont();
  LCD.fillScreen (TFT_BLACK); // Clear the screen
  delay (50);

  first_page.setInitFunction (first_page_init);
  first_page.setDrawFunction (first_page_draw);
  first_page.init();
  first_page.setActive();
  
  Serial.println (F("Done."));
  digitalWrite (TFT_BL, HIGH); // Turn on the backlight

  return true;
}

//============================================================================================//

void first_page_init (void) {
  // Add your UI elements initialization here.
  return;
}

//============================================================================================//

void first_page_draw (void) {
  if (first_page.isActive()) {
    if (myui.prevPage != first_page.pageNum) {
      first_page.uiParent->lcdParent->fillScreen (TFT_WHITE);
      myui.currentPage = first_page.pageNum;
      myui.prevPage = first_page.pageNum;
    }
  }
}

//============================================================================================//

void second_page_init (void) {
  // Add your UI elements initialization here.
  return;
}

//============================================================================================//

void second_page_draw (void) {
  if (second_page.isActive()) {
    if (myui.prevPage != second_page.pageNum) {
      second_page.uiParent->lcdParent->fillScreen (TFT_BLUE);
      myui.currentPage = second_page.pageNum;
      myui.prevPage = second_page.pageNum;
    }
  }
}

//============================================================================================//




