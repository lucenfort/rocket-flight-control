# Controle de Mini Foguete com Sistema de Recuperação e Obtenção de Dados

Este projeto tem como objetivo controlar um mini foguete durante seu vôo, ejetando um paraquedas para sua recuperação e obtendo dados de pressão, temperatura e altitude durante todo o processo. O sistema utiliza um sensor MPU6050 para identificar o lançamento do foguete e controlar a ejeção do paraquedas por meio de um micro servo motor de rotação contínua. Além disso, um sensor BMP180 é utilizado para obtenção dos dados de pressão, temperatura e altitude, que são gravados em um cartão SD para posterior análise.

## Diagrama de Conexão

O diagrama de conexão abaixo representa como os componentes devem ser conectados ao microcontrolador:

```
 MPU6050      BMP180       Servo Motor      SD Card
+--------+   +--------+   +-----------+   +--------+
|        |   |        |   |           |   |        |
| SDA    +---+ SDA    |   |           |   | MOSI   |
|        |   |        +---+ Control   +---+        |
| SCL    +---+ SCL    |   |           |   | SCK    |
|        |   |        |   |           |   |        |
+--------+   +--------+   +-----------+   +--------+
```


## Requisitos

Para a realização deste projeto, você vai precisar dos seguintes componentes:

- Microcontrolador ESP32
- Sensor MPU6050
- Sensor BMP180
- Micro Servo Motor de Rotação Contínua
- Cartão microSD

## Instalação

1. Clone este repositório em sua máquina local.
2. Abra o arquivo `controle_foguete.ino` no Arduino IDE.
3. Instale as bibliotecas necessárias (MPU6050, BMP180, Servo, SD) utilizando o gerenciador de bibliotecas da Arduino IDE.
4. Conecte os componentes de acordo com o diagrama de conexão.
5. Compile e envie o código para o microcontrolador.

## Uso

1. Alimente o microcontrolador com uma fonte de alimentação adequada.
2. Lance o foguete para iniciar a obtenção dos dados.
3. Aguarde o fim do vôo para coletar o cartão microSD e realizar a análise dos dados obtidos.
