# Conway's Game of Life on TFT Display

This project implements Conway's Game of Life using an ESP32 and an ILI9341 TFT display, driven by the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library. The grid is displayed in real-time on a 320x240 screen and evolves every 3 seconds based on the standard Game of Life rules.

## Features

- Grid cell size: 8x8 pixels (can be adjusted accordingly)
- Grid resolution: 40x30 cells (based on 320x240 display)
- Random initial grid state (TO-DO: Add pre-existing good seeds to allow the animation to last longer.)
- Efficient bitmap drawing for live cell rendering
- Display delay: 3 seconds between generations to allow the user to note cell positions

## Hardware Required

- ESP32
- ILI9341-based 320x240 TFT display
- SPI-compatible wiring
- PlatformIO-compatible development environment
