/*
Projeto: Minifoguete de 50 m (adaptável)
Descrição: Este código controla um minifoguete utilizando sensores para monitorar dados ambientais e ativar um paraquedas quando a altitude for inferior a 50 metros. Os dados são registrados em um cartão SD.
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP180.h>
#include <MPU6050.h>
#include <SD.h>
#include <Servo.h>

// Definições de pinos
#define BMP180_SDA 21
#define BMP180_SCL 22
#define SERVO_PIN 27

// Instâncias de sensores e atuadores
Adafruit_BMP180 bmp;
MPU6050 mpu;
Servo servo;

// Estrutura para armazenar dados dos sensores
class SensorData {
  public:
    float temperature; // Temperatura em graus Celsius
    float pressure;    // Pressão em Pascals
    float altitude;    // Altitude em metros
    float gyroX;      // Aceleração no eixo X
    float gyroY;      // Aceleração no eixo Y
    float gyroZ;      // Aceleração no eixo Z

    // Construtor da classe
    SensorData(float t, float p, float a, float gx, float gy, float gz) 
      : temperature(t), pressure(p), altitude(a), gyroX(gx), gyroY(gy), gyroZ(gz) {}
};

// Classe para gerenciar o registro de dados no cartão SD
class SDLogger {
  public:
    // Inicializa o cartão SD
    bool begin() {
      if (!SD.begin()) {
        Serial.println("Falha na inicialização do cartão SD!");
        return false;
      }
      return true;
    }

    // Loga os dados do sensor no arquivo CSV
    bool logData(const SensorData& data, uint32_t time) {
      File file = SD.open("data.csv", FILE_WRITE);

      if (!file) {
        Serial.println("Falha ao abrir o arquivo!");
        return false;
      }

      // Escreve os dados no formato CSV
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

      file.close(); // Fecha o arquivo
      return true;
    }
};

// Classe para gerenciar o paraquedas
class Parachute {
  public:
    // Aciona o paraquedas
    void deploy() {
      servo.write(180); // Aciona o servo motor para abrir o paraquedas
      delay(5000);      // Aguarda 5 segundos
      servo.write(0);   // Aciona o servo motor para fechar o paraquedas
    }
};

// Instância da classe SDLogger
SDLogger sdLogger;
Parachute parachute;

// Função de configuração
void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(BMP180_SDA, BMP180_SCL); // Inicializa a comunicação I2C
  bmp.begin(); // Inicializa o sensor BMP180
  mpu.initialize(); // Inicializa o sensor MPU6050
  servo.attach(SERVO_PIN); // Conecta o servo motor ao pino definido

  // Verifica se o cartão SD foi inicializado corretamente
  if (!sdLogger.begin()) {
    Serial.println("Erro ao inicializar o logger de dados.");
    while (true); // Para a execução se a inicialização falhar
  }
}

// Função principal de loop
void loop() {
  uint32_t time = millis(); // Marca o tempo atual

  // Coleta os dados dos sensores
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();
  float gyroX, gyroY, gyroZ;
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);

  // Armazena os dados dos sensores em um objeto
  SensorData data(temperature, pressure, altitude, gyroX, gyroY, gyroZ);

  // Registra os dados no cartão SD
  if (!sdLogger.logData(data, time)) {
    Serial.println("Erro ao registrar os dados.");
  }

  // Ativa o paraquedas se a altitude for inferior a 50 metros
  if (altitude < 50) {
    parachute.deploy();
  }

  delay(1000); // Aguarda 1 segundo antes de coletar mais dados
}
