# Controle de Mini Foguete com Sistema de Recuperação e Obtenção de Dados

# Controle de Voo de Foguete

Este é um projeto de controle de voo de foguete que usa uma placa ESP32, sensores BMP180 e MPU6050 e um servo motor de rotação contínua para acionar um paraquedas. O sistema de controle tem duas funções principais: recuperação por meio da injeção de um paraquedas e aquisição de dados salvando dados de sensores em arquivo CSV dentro de um cartão SD em função do tempo de operação em milissegundos.

O código está escrito em C++ e pode ser compilado usando a IDE do Arduino. O código é bem documentado, modularizado e orientado a objetos.

## Montagem do Circuito

Para montar o circuito, siga o esquema abaixo:

```
ESP32    BMP180    MPU6050    Micro Servo
-------------------------------------------
3V3      VCC       VCC        VCC
GND      GND       GND        GND
D21/SCL  SCL
D22/SDA  SDA
D18              SCL
D19              SDA
          AD0       AD0
                     PWM
```

## Requisitos

Para a realização deste projeto, você vai precisar dos seguintes componentes:

- Microcontrolador ESP32
- Sensor MPU6050
- Sensor BMP180
- Micro Servo Motor de Rotação Contínua
- Cartão microSD

## Instalação

Para instalar o código na placa ESP32, siga estes passos:

1. Baixe e instale a IDE do Arduino.
2. Abra a IDE do Arduino e vá em "File" -> "Preferences". Na seção "Additional Boards Manager URLs", adicione o seguinte URL: `https://dl.espressif.com/dl/package_esp32_index.json`.
3. Vá em "Tools" -> "Board" -> "Boards Manager". Pesquise por "esp32" e instale o pacote.
4. Selecione a placa "ESP32 Dev Module" em "Tools" -> "Board".
5. Conecte a placa ESP32 ao computador usando um cabo USB.
6. Abra o arquivo "rocket-flight-control.ino" na IDE do Arduino.
7. Clique em "Upload" para enviar o código para a placa ESP32.

## Uso

Ao ligar a placa ESP32, ela começará a coletar dados dos sensores e salvará esses dados em um arquivo CSV no cartão SD. Quando a altitude for inferior a 50 metros, o paraquedas será acionado.
