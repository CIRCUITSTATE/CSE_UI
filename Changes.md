

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

