# Stendarr
Raspberry Pi + ESP32-CAM = Open Source Video Surveillance System

# How does it works ?
The goal of the stendarr project is to provide an open source video surveillance system that is easy to set up and inexpensive.
* The Raspberry Pi acts as a server for the video surveillance system, and uses [motionEyeOS](https://github.com/ccrisan/motionEyeOS).
* ESP32-CAMs act as wifi ip cameras, and uses [Housecarl](https://github.com/Cyril-Meyer/Stendarr/tree/main/Housecarl).

# Setup guide
## Server
Install motionEyeOS as described on the [motionEyeOS wiki](https://github.com/ccrisan/motioneyeos/wiki/Installation).

## Cameras
In this section we assume you are using the same peripherals as us, i.e. the cheapest "made in china" ftdi programmer and ESP32-CAM boards. We also assume that you are using a Windows 10 computer.
### FTDI and Arduino IDE setup
* install ftdi [drivers](https://ftdichip.com/drivers/vcp-drivers/) using the windows device manager.
* Arduino IDE
  * add this url to the additional board manager URLs : https://dl.espressif.com/dl/package_esp32_index.json
  * install esp32 **1.0.4** in the boards manager .
    * if problem with resolution : check version, 1.0.5 and 1.0.6 have issues.
  * select "AI Thinker ESP32-CAM" board.
### Housecarl upload
* open [Housecarl](https://github.com/Cyril-Meyer/Stendarr/tree/main/Housecarl) project.
* change the network configuration to suit your local network (configuration.h file).
* for each ESP32-CAN you have, change the hostname and IP address (each ESP32-CAM must be unique).
* upload.

# How much does it cost ?
The price is a very important point for us, we want to offer a solution "as cheap as possible".

Here is the price of an example configuration with 4 cameras :
* Raspberry Pi 3 Model B + 64 Go SD + power supply : 30€
* ESP32-CAM board + OV2640 Camera + Antenna + power supply : 6.5€/pcs
  * 4 pcs = 26€
* FTDI programmer : 4€
Total = 60€

# Troubleshooting
* Changing a camera resolution, will make motionEyeOS stop to receive and process the video.
  * Restart motionEyeOS will fix the problem.
    * setup a crontab for reboot, e.g. : '00 10 * * * reboot'.

# Known bugs and fix
* After a few days, weeks, or months, the cameras seem to stop responding, this is an ongoing issue.
  * This is also a problem when the camera is "overused", such as during setup or testing.
    * Overheat problem ?
  * [d9b2845b04ecbaa721366e679154ba31bebc4820](https://github.com/Cyril-Meyer/Stendarr/commit/d9b2845b04ecbaa721366e679154ba31bebc4820) added a daily reset system, need to see if it works.
* Sometimes, the camera work (web page and /capture) but motionEyeOS still doesn't get images, even after restart.
  * TODO ? : add a manual restart button for Housecarl ?
