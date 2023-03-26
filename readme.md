# Remington iLight Reset
Remington iLight cartridges provide 1,500 flashes before they are disabled by a counter.
This program will reset the counter so you can keep using it. However, you should only reset it 2-3
times since the bulb and performance does degrade.

## Cartridge
* counter: Dallas DS2431
* bulb: Still don't know where to get one of these.

## Supplies
* [Arduino Uno R3](https://store-usa.arduino.cc/collections/boards/products/arduino-uno-rev3) -
you need some kind of micro controller to reset the counter. I'm using an Arduino UNO R3,
which is more than you need but it's a nice board to have for various projects
* [Small breadboard](https://www.amazon.com/gp/product/B07LFD4LT6/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) - for connecting everything
* [Breadboard Connectors](https://www.amazon.com/EDGELEC-Breadboard-Optional-Assorted-Multicolored/dp/B07GD2BWPY/ref=sr_1_3?crid=1RBUWJZ3UI2OB&keywords=breadboard%2Bconnectors&qid=1679836820&s=electronics&sprefix=breadboard%2Bconnectors%2Celectronics%2C109&sr=1-3&th=1) - for connecting the breadboard to
the arduino
* [USB A](https://www.amazon.com/AmazonBasics-USB-2-0-Cable-Male/dp/B00NH11KIK/ref=sr_1_3?crid=1LLUP1W6PNBKT&keywords=usb+a&qid=1679836976&s=industrial&sprefix=usb+a%2Cindustrial%2C130&sr=1-3) - printer cable;
for connecting the arduino to your computer
* [4.7k Resister](https://www.amazon.com/EDGELEC-Resistor-Tolerance-Multiple-Resistance/dp/B07QJB3LGN/ref=sr_1_4?keywords=4.7k+ohm+resistor&qid=1679837113&s=industrial&sprefix=4.7k+re%2Cindustrial%2C151&sr=1-4) -
part of the one wire circuit
* Computer with a usb port

## Arduino Setup
* [Download](https://www.arduino.cc/en/software) and install the Arduino IDE
* Go to tools, manage libraries and install:
    * DS2431 by Tom Magnier
    * MAX31850 OneWire by Adafruit
* Connect the usb to the Arduino
* Download [remington_read_write.ino](remington_read_write.ino) and open in Arduino IDE
* Click the verify check mark button (top left of screen)
* Click the upload arrow button (next to verify check)

Your Arduino is now programmed and ready to reset the ilight counter.

## Wiring
Maker sure you're ready to reset the cartridge before connecting it the counter overwrite cannot be
undone.

Wire the circuit as shown:

<img alt="Wiring" src="https://github.com/bluekiwi6/ilight_reset/blob/main/images/circuit.png" width="700" />

![Connection1](images/connected1.jpeg)

![Connection2](images/connected2.jpeg)

![Connection3](images/connected3.jpeg)

## Reset the counter
The reset program runs when the uno starts up, so there are three ways to start it:
* Run the program upload again
* Disconnect and reconnect the usb
* Press the reset button on the arduino

The output will be shown in the serial monitor.