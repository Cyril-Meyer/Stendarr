# Stendarr
Raspberry Pi + ESP32-CAM = Open Source Video Surveillance System

# How does it works ?
The goal of the stendarr project is to provide an open source video surveillance system that is easy to set up and inexpensive.
* The Raspberry Pi acts as a server for the video surveillance system, and uses [motionEyeOS](https://github.com/ccrisan/motionEyeOS).
* ESP32-CAMs act as wifi ip cameras, and uses [Housecarl](https://github.com/Cyril-Meyer/Stendarr/tree/main/Housecarl).

# Setup guide
## Server
Install motionEyeOS as described on the [motionEyeOS wiki](https://github.com/ccrisan/motioneyeos/wiki/Installation)

## Cameras
Install Housecarl
TODO

# How much does it cost ?
The price is a very important point for us, we want to offer a solution "as cheap as possible".

Here is the price of an example configuration with 4 cameras :
* Raspberry Pi 3 Model B + 64 Go SD + power supply : 30€
* ESP32-CAM board + OV2640 Camera + Antenna + power supply : 6.5€/pcs
  * 4 pcs = 26€
* FTDI programmer : 4€
Total = 60€
