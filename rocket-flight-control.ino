/*

*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP180.h>
#include <MPU6050.h>
#include <SD.h>
#include <Servo.h>

#define BMP180_SDA 21
#define BMP180_SCL 22
#define SERVO_PIN 27

Adafruit_BMP180 bmp;
MPU6050 mpu;
Servo servo;

void setup() {
  Wire.begin(BMP180_SDA, BMP180_SCL);
  bmp.begin();
  mpu.initialize();
  servo.attach(SERVO_PIN);
}

class SensorData {
  public:
    SensorData(float t, float p, float a, float gx, float gy, float gz) {
      temperature = t;
      pressure = p;
      altitude = a;
      gyroX = gx;
      gyroY = gy;
      gyroZ = gz;
    }
    
    float temperature;
    float pressure;
    float altitude;
    float gyroX;
    float gyroY;
    float gyroZ;
};

class SDLogger {
  public:
    SDLogger() {}

    bool begin() {
      if (!SD.begin()) {
        Serial.println("SD card initialization failed!");
        return false;
      }

      return true;
    }

    bool logData(SensorData data, uint32_t time) {
      File file = SD.open("data.csv", FILE_WRITE);

      if (!file) {
        Serial.println("Failed to open file!");
        return false;
      }

      file.print(time);
      file.print(",");
      file.print(data.temperature);
      file.print(",");
      file.print(data.pressure);
      file.print(",");
      file.print(data.altitude);
      file.print(",");
      file.print(data.gyroX);
      file.print(",");
      file.print(data.gyroY);
      file.print(",");
      file.println(data.gyroZ);

      file.close();
      return true;
    }
};

class Parachute {
  public:
    Parachute() {}

    void deploy() {
      servo.write(180); // aciona o servo motor para abrir o paraquedas
      delay(5000); // aguarda 5 segundos
      servo.write(0); // aciona o servo motor para fechar o paraquedas
    }
};

void loop() {
  uint32_t time = millis();

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);

  SensorData data(temperature, pressure, altitude, gyroX, gyroY, gyroZ);

  sdLogger.logData(data, time);

  if (altitude < 50) { // ativa o paraquedas quando a altitude for inferior a 50 metros
    parachute.deploy();
  }

  delay(1000); // aguarda 1 segundo antes de coletar mais dados
}
