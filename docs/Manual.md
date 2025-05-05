

# CSE_UI - User Manual

This is the user manual for the CSE_UI Arduino library from CIRCUITSTATE Electronics. This document will provide information on the concepts and features of the library. If you are looking for functions and classes, please refer to the [API.md](API.md) file.

Following are the GUI features currently supported.

- Single line text strings in custom fonts.
- Multi-line text strings in custom-sized text boxes and fonts.
- Interactive buttons with text, icon, etc.
- Interactive lists with text, icon, etc.
- Interactive pagination.

## Design

The library is written on top of the [**TFT_eSPI**](https://github.com/Bodmer/TFT_eSPI) graphics library for Arduino. TFT_eSPI allows interfacing screens with different resolutions, controllers and interfaces, with various Arduino-compatible boards. It can draw primitive graphics such as rectangles, rounded rectangles, circles, lines, etc. CSE_UI makes use if these primitives to draw the GUI elements on the screen.

### Pages

In CSE_UI, a page is a set of elements shown on the display at a time. You can think of pages and groups of elements. You can create any number of pages and add any number of items to it, depending on the available memory. A page is displayed when it is in the active state. That means, only page can be active at a time. But you can have common elements between pages. The process of displaying of a page, or any elements inside it is called drawing. Every page and element have their own draw functions. Pages can be supplied with a unique page number to identify them.

The following code snippet shows how to create a page. This also includes the TFT_eSPI object and the touch controller, for completion.

```cpp
TFT_eSPI LCD = TFT_eSPI(); // Create a new TFT driver instance

// Create a new instance of the CST328 touch controller class.
// Parameters: Width, Height, &Wire, Reset pin, Interrupt pin
CSE_Touch* tsPanel = CSE_Touch_Driver:: createDriver (CSE_TOUCH_CST328, 240, 320, &Wire, TFT_RST);

// UI objects.
CSE_UI myui (&LCD, tsPanel);

// Pages
pageClass home_Page (&myui, 0);
```

We are first creating a new UI object called `myui` of type `CSE_UI` and supplying our LCD and touch controller objects. This means, `myui` will be drawn to the display indicated by the `LCD` object, and the touch data is acquired from the `tsPanel` object. This gives you flexibility in choosing any LCD screens with supported touch controllers. If a touch controller is not provided, the touch functions will not work.

Next, we are creating a new page called `home_Page` of type `pageClass`with a new page number `0`. After creating a new page, we need to pass it two functions - an initialization function and a draw function. Both the initialization and draw functions can be entirely implemented in your user code. We will create new sample functions for the page.

```cpp
// Forward declarations
void home_Page_Init (void);
void home_Page_Draw (void);
```

The return type and parameter type are important. You can only have `void` for both. The initialization function is usually only called once. The function takes care of adding other UI elements in the page and initialize them one by one. Since we did not add any UI elements to the page, our initialization function is empty.

```cpp
void home_Page_Init (void) {
  // Add UI elements here
}
```

Next, we will create a minimal draw function. Remember, this function is defined in your application code, not as part of the library.

```cpp
void home_Page_Draw() { 
  if (home_Page.isActive()) { // Only draw if the page is currently active
    if (myui.prevPage != home_Page.pageNum) { // Only redraw background if the page was changed
      home_Page.uiParent->lcdParent->fillScreen (TFT_WHITE);
      myui.currentPage = home_Page.pageNum; // Update the page numbers
      myui.prevPage = home_Page.pageNum;
    }
  }
}
```

This function simply fills the screen with a color. Drawing only happens if the page is set to active. You can use the `setActive()` function to set a page active. The next time you call this draw function, the background will be redrawn only if the page was changed. For example, if you have two pages with different background colors, the background will of the page will be redrawn only when you switch from the previous page. This saves CPU time. After the page is redrawn, the page number is updated to the current page. `myui` (`CSE_UI` object) has two variables `currentPage` and `prevPage` to keep track of the current and previous page.

Once the initialization and draw functions are defined, they can be passed to the `home_Page` (`pageClass` object) in the following way.

```cpp
home_Page.setInitFunction (home_Page_Init);
home_Page.setDrawFunction (home_Page_Draw);
```

The initialization and draw functions are passed as function pointers. The local functions can be invoked by calling the `init()` and `draw()` functions associated with the `home_Page` object. To initialize, call the following way.

```cpp
home_Page.init();
```

This will invoke the `home_Page_Init()` function through the function pointer. This is why it is important to keep the return type and the parameter type to `void` for such functions. Similarly for drawing, call it the following way. This will invoke the `home_Page_Draw()` function.

```cpp
home_Page.draw();
```

Following is a bare-minimum program that demonstrates the usage of the `pageClass`. This example does not show the complexity of initializing a `TFT_eSPI` driver. You should have configured it already.

```cpp
#include <TFT_eSPI.h> // TFT LCD library
#include <Wire.h>
#include <CSE_CST328.h> // Touch controller library
#include <CSE_UI.h>

TFT_eSPI LCD = TFT_eSPI(); // Create a new TFT driver instance

// Create a new instance of the CST328 class.
// Parameters: Width, Height, &Wire, Reset pin, Interrupt pin
CSE_Touch* tsPanel = CSE_Touch_Driver:: createDriver (CSE_TOUCH_CST328, 240, 320, &Wire, TFT_RST);

// UI objects.
CSE_UI myui (&LCD, tsPanel);

// Pages
pageClass home_Page (&myui, 0);

// Forward declarations
void setup (void);
void loop (void);
void home_Page_Init (void);
void home_Page_Draw (void);

// Setup runs once.
void setup() {
  LCD.begin();

  home_Page.setInitFunction (home_Page_Init);
  home_Page.setDrawFunction (home_Page_Draw);
  home_Page.init();
  home_Page.setActive();
}

// Infinite loop
void loop() {
  home_Page_Draw();
}

// Initialize the page
void home_Page_Init (void) {
  // Add UI elements here
}

// Draw the page
void home_Page_Draw() { 
  if (home_Page.isActive()) { // Only draw if the page is currently active
    if (myui.prevPage != home_Page.pageNum) { // Only redraw background if the page was changed
      home_Page.uiParent->lcdParent->fillScreen (TFT_WHITE);
      myui.currentPage = home_Page.pageNum; // Update the page numbers
      myui.prevPage = home_Page.pageNum;
    }
  }
}
```

## LCD String

In order to draw text on the screen, you can use the `lcdString` class. CSE_UI uses TFT_eSPI's `drawString()` function to draw the strings. The font and font size are determined by what you set in the LCD object. So before writing any strings, you should set the desired font and font size.

