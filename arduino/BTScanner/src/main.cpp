#include <Arduino.h>
#include <ArduinoBLE.h>

// Adapted from BLE library examples

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  // begin initialization
  if (!BLE.begin())
  {
    Serial.println("D starting BLE failed!");
    while (1)
      ;
  }

  // start scanning for peripherals
  BLE.scan();
}

void loop()
{
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  // Serial.println(peripheral.localName());

  if (peripheral)
  {
    // see if peripheral found is my Thunderboard
    if (peripheral.localName() == "TUNITemp")
    {
      // stop scanning
      BLE.stopScan();

      if (peripheral.connect())
      {
        Serial.println("D Connected");

        peripheral.discoverAttributes();

        BLECharacteristic tempCharacteristic = peripheral.characteristic("2a1c");
        Serial.println("D Subscribing to temperature characteristic ...");
        if (!tempCharacteristic)
        {
          Serial.println("D no temperature characteristic found!");
          peripheral.disconnect();
        }
        else if (!tempCharacteristic.canSubscribe())
        {
          Serial.println("D temperature characteristic is not subscribable!");
          peripheral.disconnect();
        }
        else if (!tempCharacteristic.subscribe())
        {
          Serial.println("D subscription failed!");
          peripheral.disconnect();
        }

        if (peripheral.connected())
        {
          while (1)
          {
            // check if the value of the simple key characteristic has been updated
            if (tempCharacteristic.valueUpdated())
            {
              byte buffer[5];

              tempCharacteristic.readValue(buffer, tempCharacteristic.valueLength());

              /*
              Serial.print(buffer[0], HEX);
              Serial.print(", ");
              Serial.print(buffer[1], HEX);
              Serial.print(", ");
              Serial.print(buffer[2], HEX);
              Serial.print(", ");
              Serial.print(buffer[3], HEX);
              Serial.print(", ");
              Serial.println(buffer[4], HEX);

              Serial.print("mantissa: ");
              Serial.println(mantissa);
              */

              // This is simplification from the full IEEE-11073 spec
              int mantissa = buffer[3] << 16 | buffer[2] << 8 | buffer[1];
              float temp = mantissa / 10.0f;
              Serial.println(temp);
            }

            delay(100);
          }
        }
      }

      // peripheral disconnected, we are done
      while (1)
        ;
    }
  }
}
