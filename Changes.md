
# Changes

#
### **+05:30 08:31:21 PM 05-05-2025, Monday**

  - `lcdString:: initialize()` now accepts a `font` parameter of type `uint8_t`.
    - `font` is initialized with `NULL` for backward compatibility.
  - `lcdString:: draw()` loads the font if it not `NULL`.
  - This allows the user to set a font for the string and not worry about loading it every time when drawing the string.
  - Added `API.md` and `Manual.md` files.
  - Added `Page.ino` example.
  - Updated `Readme.md` file.

#
### **+05:30 01:16:02 AM 02-03-2025, Sunday**

  - Added file descriptions.
  - Updated Readme.

#
### **+05:30 03:30:18 PM 01-03-2025, Saturday**

  - Updated `buttonClass:: isTouched()`.
    - Removed commented out code.
    - The touch issue was fixed.

#
### **+05:30 12:25:00 PM 01-03-2025, Saturday**

  - Added Changes.md file.
  - Changed `CSE_FT6206.h` include to `CSE_Touch.h`.
    - We will use the new unified touch library for the UI implementation.
  - Replaced `CSE_FT6206*` pointers with `CSE_Touch*` pointers.
  - Added Arduino library specification files.
  - Added Arduino vector library.
  - 🐞 The `buttonClass:: isTouched()` is producing an error.
    - The button coordinates are randomly overwritten when the touch panel is touched.
    - Added debug lines to print the touch coordinates and the button coordinates.
    - Removed the rotation since this is now handled in the CSE_Touch library.
  - 🆕 Bumped up the version to `v0.0.8`

