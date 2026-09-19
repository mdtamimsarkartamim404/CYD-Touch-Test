# 🎯 ESP32 CYD (Cheap Yellow Display) - Calibrated Touch Test

This repository provides a fully corrected and calibrated Touch Test sketch for the **ESP32-2432S028 (Cheap Yellow Display / CYD)** board running in landscape orientation (`tft.setRotation(1)`).

It addresses and resolves the common **inverted/flipped touch axis bug** where touching one corner triggers the opposite side. Instead of relying on buggy library-level rotation settings, this project directly maps raw XPT2046 SPI hardware coordinates to precise screen pixel values.

---

## 📌 Features
- **Precise Coordinate Mapping:** Direct translation from raw touch SPI data to $320 \times 240$ display coordinates.
- **Visual Feedback:** Real-time red/white targets drawn directly under the touch contact point.
- **On-Screen Diagnostic Overlay:** Live readout displaying mapped `SCREEN X`, `SCREEN Y`, and `PRESSURE (Z)` values.
- **Serial Debugging Output:** Outputs both RAW SPI values and mapped screen coordinates to the Serial Monitor at 115200 baud.

---

## 🛠 Calibration Map

| Screen Position | Raw X Value | Raw Y Value | Target Pixel Coordinate |
|---|---|---|---|
| **Top-Left** | `483` | `547` | $(0, 0)$ |
| **Top-Right** | `3634` | `461` | $(319, 0)$ |
| **Bottom-Left** | `396` | `3548` | $(0, 239)$ |
| **Bottom-Right** | `3502` | `3575` | $(319, 239)$ |
| **Center** | `1990` | `2089` | $(160, 120)$ |

### 📐 Mapping Logic Used:
```cpp
// Direct mapping formula for landscape mode (Rotation 1)
x = map(rawX, 396, 3634, 0, 319);
y = map(rawY, 461, 3575, 0, 239);

x = constrain(x, 0, 319);
y = constrain(y, 0, 239);
