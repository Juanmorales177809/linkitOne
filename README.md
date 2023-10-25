---
title: LinkIt ONE
category: LinkIt
bzurl: https://www.seeedstudio.com/LinkIt-ONE-p-2017.html
oldwikiname: LinkIt_ONE
prodimagename: 500px-Linkit-one-page.jpg
sku: 102030002
---

![enter image description here](https://raw.githubusercontent.com/SeeedDocument/Linkit_ONE/master/image/500px-Linkit-one-page.jpg)





## Features
--------------
- Includes ARM7 EJ-S™, GSM, GPRS, Wi-Fi, Bluetooth BR/EDR/BLE, GPS, Audio codec, and SD card connector on a single development board.
- Pin-out similar to Arduino boards, including Digital I/O, Analog I/O, PWM, I2C, SPI, UART and power supply, compatible with Arduino.
- Provides various interfaces for connecting to most sensors, peripherals, Groves, and other widgets.
- You are what you wear. Using LinkIt ONE together with MediaTek LinkIt SDK (for Arduino) you will be able to easily turn your ideas into practical prototypes and make them a reality with the Seeed productization and agile manufacturing service.


## specifications
------------------
|Parameter   |Value          |
|:------|:-----------------|
|Chipset|	MT2502A (Aster, ARM7 EJ-S (TM) )|
|Clock Speed|	260MHz|
|Dimensions|	3.3x2.1 inches|
|Flash|	16MB|
|RAM|	4MB|
|DC Current Per I/O Pin|	1mA|
|Analog Pins|	3|
|Digital Output	|3.3V|
|Analog Input|	5V|
|UART|	Software based(**Serial**) ,also known as USB Modem Port and Hardware Serial(**Serial1**, D0&D1)|
|SD Card|	Up to 32GB(Class 10)|
|Positioning|	GPS(MT3332)|
|GSM|	850/900/1800/1900 MHz|
|GPRS|	Class 12|
|Wi-Fi|	802.11 b/g/n|
|Bluetooth|	BR/EDR/BLE(Dual Mode)|

##Application Ideas
--------------------
* Internet of Things
* Smart House
* Wearable Designe
* Industrial
* Sensor Hub
* Automation & Transportation


|Switch No.|	Functionality|	Position 1 - Functionality|	Position 2 - Functionality|
|:------|:-----------------|:-----------------|:-----------------|
|1|	Program Mode|	**MS**： In this position, when connected to PC, LinkIt One board will be shown as 10MB USB drive. The program will not execute in this mode. Any file that is copied to this drive can be read via the code.|	UART：This position is used to set the board to program mode. Firmware can be uploaded in this mode.|
|2|	Power|	**BAT**： Board powered by Li-ion Battery. To charge battery, set the switch to this position and connect the board to PC.|	**USB**：Board powered by USB port. Set the switch to this position when there is no battery connected to program the board.|
|3|	SD/SPI|	**SPI**：This position allows access of external SPI pins (D10 - D13)	|**SD**：This position allows the code to access SD card. This mode also disables access of SPI pins (D10-D13).|

## Getting started

### Procedure Overview
|No.|	Step	|Read more|
|:------|:-----------------|:-----------------|
|1|	Install Arduino IDE 1.8.13  (Windows version)
|2|	Install [ LinkIt SDK]
|3|	Install LinkIt ONE drivers.
|6|	Update the on-board firmware version.
|7| Add folder Linklt at C:\Users\<your user>\AppData\Local\Arduino15\packages
|7|	Open Arduino IDE, Select LinkIt ONE board and start coding.



### Installing Mediatek LinkIt ONE SDK
- Download [  LinkIt SDK for Arduin](https://github.com/Juanmorales177809/linkitOne).At the time of writing this guide, **v1.1.11** Windows SDK  was used.
- Extract the downloaded files to Arduino IDE folder.
- Double-Click the .EXE file and install.
- With the installation of LinkIt ONE SDK, Arduino IDE works a LinkIt ONE IDE.

### Installing Drivers

- Download driver (https://github.com/Juanmorales177809/linkitOne)
- Put the MS/UART slide switch to UART position and connect LinkIt ONE to PC.
- Open Device Manager, the following COM ports will be displayed.

![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/LinkIt_ONE_Wiki_Temp1.jpg)

- Install driver from ..\LinkIt_ONE_IDE\drivers\mtk folder.
- After installing drivers, Device Manger should display the following two ports:

   **MTK USB Debug Port** used for uploading code.
 
  **MTK USB Modem Port** used for printing message, such as Serial.println()
  
![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/LinkIt_ONE_Wiki_Temp2.jpg)  


### Updating Firmware
The firmware of LinkIt ONE board needs to be updated once in a while. Latest LinkIt ONE SDK comes with a version of firmware. 

- Before starting the firmware update, make sure the slide switches are in proper position ( **MS/UART** should be in **MS** position. **USB/BAT** in **USB** position):

![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/LinkItONEUpdateFirmware2.jpg)  

- Run FirmwareUpdater.exe application from ..[  LinkIt UPDATER](https://github.com/Juanmorales177809/linkitOne/tree/main/LinkIt/tools/linkit_tools/1.1.23).

![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/400px-LinkItONEUpdateFirmware.jpg)  

- Click the button and then connect LinkIt ONE to PC. Wait for 1 minutes for the update to complete successfully.

![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/400px-LinkItONEUpdateFirmware_ok.jpg)  
### Uploading Code (ANY)

- The slide switches should be configured for firmware upload (i.e Put MS/UART in UART position and Power switch in USB position).

![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/LinkIt_ONE_Wiki_Temp3.jpg) 

- Open **File** -> **Examples** -> **Basics** -> **Blink** in LinkIt ONE IDE.
- Select the COM Port number corresponding to **MTK USB Debug port** in **Tools** -> **Port**.
- Compile and upload the code.
- LED marked **L** should blink.

### Connecting Antennae
There are three antennae provided with LinkIt ONE. They are used for:

- GSM/GPRS
- Wi-Fi/BT
- GPS

Connect the antenna as the following image.

![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/400px-Linkit_one_antenna.jpg) 

!!!Note
    - While pulling the antenna from board, do it with care. Please Do not use brute force.
    - Try to use the force perpendicular to the direction of the board, otherwise you might damage the antenna pad.

### Inserting SIM Card and SD Card

LinkIt ONE accepts standard size SIM Card and Micro SD Card. Insert them as per the following image:

![](https://raw.githubusercontent.com/SeeedDocument/Linkit-ONE/master/image/LinkItONE_SIM_SDCard_Insert.jpg) 

### Exploring LinkIt ONE SDK Examples
LinkIt ONE SDK comes with many examples / sample code to use peripherals like GSM, GPRS, WiFi, BT, Audio, GPS etc. Explore them first and read about API documentation. API documentation are available in [  User Guide ](http://labs.mediatek.com/fileMedia/download/5fed7907-b2ba-4000-bcb2-016a332a49fd) and [  API References site ](https://labs.mediatek.com/site/znch/developer_tools/mediatek_linkit/api_references/Core_Digital.gsp)



## Tutorial of Sidekick Basic Kit for LinkIt ONE

![enter image description here](https://raw.githubusercontent.com/SeeedDocument/Linkit_ONE/master/image/350px-LinkitONESidebox.jpg)

The Sidekick Basic Kit for LinkIt ONE is designed to be used with your LinkIt ONE board. This kit will help you quickly get along well with the platform of LinkIt. It includes many of the most popular accessories for DIY projects : like Breadboard, Jumper wires, Color LEDs, Resistors, Buzzer, etc. All these come in a handy box, which is easy to transport and mimimises clutter. The kit includes a complete guide that will familiarize you with a wide range of electronic components while you create small, simple, and easy-to-assemble circuits. There are 10 different courses outlined that will offer a best way for beginner to get familiar with LinkIt ONE.

- [The Basics](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_The_Basics)
- [Hello World](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Hello_World)
- [Push Button](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Push_Button)
- [Marquee](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Marquee)
- [Colorful World](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Colorful_World)
- [Analog Interface](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Analog_Interface)
- [Mini Servo](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Mini_Servo)
- [Light Sensor](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Light_Sensor)
- [SMS Control the LED](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_SMS_control_the_LED)
- [Get Temperature with Webpage](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Get_temperature_with_Webpage)

- [Github Repo for Sidekick Basic Kit for LinkIt ONE](http://www.seeedstudio.com/wiki/LinkIt_ONE_Tutorial_-_Get_temperature_with_Webpage)

## Resources
**Schematic / Design Files:**

- [LinkIt ONE V1.0 Eagle File](https://github.com/SeeedDocument/Linkit_ONE/raw/master/resource/202000437_PCBA%20Linkit%20ONE_PDF.zip)
- [LinkIt ONE V1.0 Schematic in PDF](https://github.com/SeeedDocument/Linkit_ONE/raw/master/resource/%5B202000437%5DLinkIt%20ONE-V1_Eagle.zip)

**Software:**

- [MediaTek_LinkIt_SDK_for_Ardunio](http://labs.mediatek.com/site/znch/developer_tools/mediatek_linkit/sdk_intro/index.gsp)

**Datasheets and User Guides:**

- [LinkIt_ONE_Hardware_Reference_Design_v1_0](https://github.com/Juanmorales177809/linkitOne)
- [LinkIt ONE_Pinout Diagram_v1.0【PDF】](https://github.com/SeeedDocument/Linkit-ONE/blob/master/resource/LinkIt_ONE_Pinout_Diagram_v1_0.pdf)
- [MediaTek_LinkIt_Developers_Guide_v1_0【PDF】](https://github.com/SeeedDocument/Linkit-ONE/blob/master/resource/MediaTek_LinkIt_ONE_Developers_Guide_v1_3.pdf)
- [MediaTek_MT2502A_SOC_Data_Sheet_v1_0【PDF】](https://github.com/SeeedDocument/Linkit-ONE/blob/master/resource/MediaTek_MT2502A_SOC_Data_Sheet_v1_0.pdf)
- [MediaTek_MT5931_Wi-Fi_Data_Sheet_v1_0【PDF】](https://github.com/SeeedDocument/Linkit-ONE/blob/master/resource/MediaTek_MT5931_Wi-Fi_Data_Sheet_v1_0.pdf)
- [MediaTek_MT3332_GPS_Data_Sheet_v1_0【PDF】](https://github.com/SeeedDocument/Linkit-ONE/blob/master/resource/MediaTek_MT3332_GPS_Data_Sheet_v1_0.pdf)

**Getting Help**

- [Seeedstudio LinkIt ONE Forum](http://www.seeed.cc/discover.html?t=linkit)


**More**
