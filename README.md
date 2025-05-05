
![CSE_UI](https://socialify.git.ci/CIRCUITSTATE/CSE_UI/image?description=1&font=KoHo&forks=1&issues=1&logo=https%3A%2F%2Fwww.circuitstate.com%2Fwp-content%2Fuploads%2F2024%2F05%2FCIRCUITSTATE-R-Emblem-20052024-2.svg&name=1&pattern=Circuit%20Board&pulls=1&stargazers=1&theme=Auto)

# CSE_UI

[**CSE_UI**](https://github.com/CIRCUITSTATE/CSE_UI) is an Arduino library from [*CIRCUITSTATE Electronics*](https://www.circuitstate.com/). It helps you design basic **Graphical User Interface (GUI)** on various small LCD screens that can be interfaced with Arduino boards. The library is built on top of the [**TFT_eSPI**](https://github.com/Bodmer/TFT_eSPI) graphics library. Therefore, all displays supported by the TFT_eSPI library are also supported by CSE_UI. Touch functionality is implemented through the [**CSE_Touch**](https://github.com/CIRCUITSTATE/CSE_Touch) library. Currently, it supports [CST328](https://github.com/CIRCUITSTATE/CSE_CST328) and [FT6206](https://github.com/CIRCUITSTATE/CSE_FT6206) capacitive touch controllers. The touch support can be extended easily.

## Installation

This library is available from the official **Arduino Library Manager**. Open the Arduino IDE, search for "CSE_UI" and install the latest version of the library.

Additionally, you can download the latest release package from the GitHub repository and install it manually. To do so, open the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library…` and select the downloaded file.

Another method is to clone the GitHub repository directly into your `libraries` folder. The development branch will have the latest features, bug fixes and other changes. To do so, navigate to your `libraries` folder (usually located at `Documents/Arduino/libraries` on Windows and `~/Documents/Arduino/libraries` on macOS) and execute the following command:

```
git clone https://github.com/CIRCUITSTATE/CSE_UI.git
```

[**Git**](https://git-scm.com) should be installed on your computer.

The library can also be installed via [**PlatformIO**](https://platformio.org). All officially listed Arduino listed libraries are automatically fetched by PlatformIO. Use the [`lib_deps`](https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_deps.html) search option to install the library.

## Dependencies

This library depends on the following libraries:

- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) - The graphics library used by CSE_UI.
- [CSE_Touch](https://github.com/CIRCUITSTATE/CSE_Touch) - The touch library used by CSE_UI.
  - [CSE_CST328](https://github.com/CIRCUITSTATE/CSE_CST328) - For CST328 capacitive touch controllers.
  - [CSE_FT6206](https://github.com/CIRCUITSTATE/CSE_FT6206) - For FT6206 capacitive touch controllers.

Make sure to install them as well.

## Example

Find the examples in the [examples](examples) folder.

  - [**Read-Touch-Polling**](examples/Read-Touch-Polling/Read-Touch-Polling.ino)
  - [**Fast-Read-Touch-Polling**](examples/Fast-Read-Touch-Polling/Fast-Read-Touch-Polling.ino)
  - [**Read-Touch-Interrupt**](examples/Read-Touch-Interrupt/Read-Touch-Interrupt.ino)

## API Reference

Please see the [API.md](/docs/API.md) file for the API reference.

## References

- [**Adafruit_FT6206 Library**](https://github.com/adafruit/Adafruit_FT6206_Library) - Where this library took inspiration from.
- [**TouchLib**](https://github.com/mmMicky/TouchLib/tree/main) - An alternate library for the CST328.
- [**Waveshare 2.8" Capacitive Touch LCD**](https://www.waveshare.com/wiki/2.8inch_Capacitive_Touch_LCD)
