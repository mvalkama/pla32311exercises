#include <Arduino.h>
#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("IMU init failed!");

    while (1);
  }

  Serial.print("Gyro samplerate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second, acceleration in G's");
  Serial.println("X\tY\tZ\tx\ty\tz");
}

void loop() {
  float x, y, z;
  float a, b, c;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(z);
  }

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(a, b, c);
    Serial.print("\t");
    Serial.print(a);
    Serial.print("\t");
    Serial.print(b);
    Serial.print("\t");
    Serial.print(c);
  }

  Serial.println();

  delay(50);
}