/*
Remington cartridge reset

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include <DS2431.h>
#include <OneWire.h>

// One Wire pin, change according to your needs. A 4.7k pull up resistor is needed.
const int ONE_WIRE_PIN = 2;

OneWire oneWire(ONE_WIRE_PIN);
DS2431 eeprom(oneWire);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // wait for Serial to come up on USB boards

  // Search the 1-Wire bus for a connected device.
  byte serialNb[8];
  oneWire.target_search(DS2431::ONE_WIRE_FAMILY_CODE);
  if (!oneWire.search(serialNb))
  {
    Serial.println("No DS2431 found on the 1-Wire bus.");
    return;
  }

  // Check serial number CRC
  if (oneWire.crc8(serialNb, 7) != serialNb[7])
  {
    Serial.println("A DS2431 was found but the serial number CRC is invalid.");
    return;
  }

  Serial.print("DS2431 found with serial number : ");
  printBuffer(serialNb, 8);
  Serial.println("");

  // Initialize DS2431 object
  eeprom.begin(serialNb);

  // Read all memory content
  byte data[16];
  eeprom.read(8, data, sizeof(data));
  Serial.println("Memory contents : ");
  printLargeBuffer(data, sizeof(data));
  Serial.println("");

  // Write a 8-byte row
  byte row8[] = {0x4, 0x0, 0x25, 0x38, 0x2, 0x0, 0xDC, 0x89};
  byte row16[] = {0x59, 0x1, 0x0, 0x0, 0x0, 0x0, 0x37, 0x9C};
  if (eeprom.write(8, row8, sizeof(row8)) && eeprom.write(16, row16, sizeof(row16)))
  {
    Serial.print("Successfully wrote new data");
  }
  else
  {
    Serial.print("Failed to write data");
  }
  Serial.println("");

  // Read all memory content
  eeprom.read(8, data, sizeof(data));
  Serial.println("Memory contents : ");
  printLargeBuffer(data, sizeof(data));
  Serial.println("");
}

void loop()
{
  // Nothing to do
}

void printBuffer(const uint8_t *buf, uint8_t len)
{
  for (int i = 0; i < len - 1; i++)
  {
    Serial.print(buf[i], HEX);
    Serial.print(",");
  }
  Serial.println(buf[len - 1], HEX);
}

void printLargeBuffer(const uint8_t *buf, uint16_t len)
{
  uint8_t bytesPerLine = 8;

  for (int i = 0; i < len / bytesPerLine; i++)
  {
    Serial.print(i * bytesPerLine);
    Serial.print("\t\t:");
    printBuffer(buf + i * bytesPerLine, bytesPerLine);
  }
}