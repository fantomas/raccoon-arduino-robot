Raccoon robot
=====================
###### An ultrasonic arduino robot for following a wall and exiting a labyrinth

Arduino robot for passing through labyrinths. It uses Ultrasonic sensor and follows one of the walls. The current robot has a static ultrasonic sensor attached 45 degrees on the front left side.
I built that robot for a competition at [iengineer.bg](http://iengineer.bg/). The competition is 3D labyrinth. More info about the rules and the organizers at [roboleague.bg](http://roboleague.bg/index.php/main/rules).

![](./assets/DSC_0439.jpg =920x)

### Parts used:

1. [Ultra Sonic range measurement module - 21lv](http://www.seeedstudio.com/depot/Ultra-Sonic-range-measurement-module-p-626.html)
2. [Arduino mini - 36lv](http://www.robotev.com/product_info.php?products_id=419&osCsid=ad8an77rb67tupsu7m3f0jssm1)
3. [FTDI Basic Breakout - 5V - 30lv](http://www.robotev.com/product_info.php?products_id=268)
4. [DC Dual Motor Driver 30V 4A - 27lv](http://www.robotev.com/product_info.php?cPath=1_40_39&products_id=173)
5. [Robot 3 wheel kit - 27lv](https://www.olimex.com/Products/RobotParts/Chassis/ROBOT-3-WHEEL-KIT/)
6. [Battery holder 4xAA - 1lv](https://www.olimex.com/Products/RobotParts/Misc/BAT-HOLDER-4XAA/)
7. [Breadboard - 6lv](http://www.robotev.com/product_info.php?products_id=134)
8. [Jumper Wires M/M and M/F - 10lv](http://www.robotev.com/product_info.php?products_id=378)

**Total cost:** 158lv.

### Description

I used Arduino Mini only because I had one. Arduino Uno could be used also. FTDI Basic Breakout is used for uploading the code to the mini. The wiring is:

|FTDI Basic | Arduino|
|:------------- |:------------- | 
|DTR | Reset |
|TXO | RXI |
|RXI | TXO |
|3V3 | +5V (it's mislabeled; only 3.3V when you flip the solder switch from default 5V) |
|CTS | GND (pull low) |
|GND | GND |

**Important:** For a breadboard arduino, connect DTR from the FTDI basic to a 100nF capacitor to Reset. Also, connect a 10k resistor from reset on arduino to +5V.

### Conclusion

Only one ultrasonic sensor is not enough. The caster wheel is not good, as moving backward the robot has a random trajectory due to it.

