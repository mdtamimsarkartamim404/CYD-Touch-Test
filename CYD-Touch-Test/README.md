# ESP32 CYD (Cheap Yellow Display) - Calibrated Touch Test

This repository provides a fully corrected and calibrated Touch Test sketch for the **ESP32-2432S028 (Cheap Yellow Display / CYD)** operating in landscape mode (`tft.setRotation(1)`).

It bypasses library-level rotation mismatches by using custom manual SPI coordinate mapping directly to pixel positions.

---

## 🛠 Calibration Map

| Screen Position | Raw X Value | Raw Y Value |
|---|---|---|
| **Top-Left** | `483` | `547` |
| **Top-Right** | `3634` | `461` |
| **Bottom-Left** | `396` | `3548` |
| **Bottom-Right** | `3502` | `3575` |
| **Center** | `1990` | `2089` |

### **Mapping Formula Used:**
```cpp
x = map(rawX, 396, 3634, 0, 319);
y = map(rawY, 461, 3575, 0, 239);









⚡ Hardware Pinout ReferenceFunctionESP32 GPIOTFT BacklightGPIO 21Touch SCLKGPIO 25Touch MISOGPIO 39Touch MOSIGPIO 32Touch CSGPIO 33Touch IRQGPIO 36📦 Required LibrariesMake sure you have installed these libraries in Arduino IDE:TFT_eSPI (Configured with CYD user setup rules)XPT2046_Touchscreen by Paul Stoffregen🚀 Getting StartedOpen CYD-Touch-Test.ino in Arduino IDE.Select target board: ESP32 Dev Module.Set Serial Monitor baud rate to 115200.Upload to your board and verify corners and center points.