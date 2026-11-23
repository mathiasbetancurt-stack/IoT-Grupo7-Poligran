# Entrega 2 – Control de LED por Bluetooth (enlace serial)

**Módulo:** Internet de las Cosas – Politécnico Grancolombiano · **Grupo 7 IoT**

Un Arduino UNO recibe comandos de un celular a través de un módulo Bluetooth HC-05 y controla dos LED.

## Archivos

| Archivo | Contenido |
|---|---|
| `sketch.ino` | Código fuente del Arduino |
| `diagram.json` | Circuito para el simulador Wokwi |
| `evidencias/` | Capturas de las pruebas |

**Proyecto en Wokwi:** https://wokwi.com/projects/481313878647659521

## Circuito

| Elemento | Pin del Arduino |
|---|---|
| LED verde + resistencia 220 Ω | D8 |
| LED rojo + resistencia 220 Ω | D9 |
| HC-05 TXD | RX (D0) |
| HC-05 RXD (con divisor 1 kΩ / 2 kΩ) | TX (D1) |
| HC-05 VCC / GND | 5V / GND |

Enlace serial: **9600 baudios, 8N1** (configuración de fábrica del HC-05).

## Comandos

| Comando | Acción |
|---|---|
| `V` | Enciende el LED verde |
| `R` | Enciende el LED rojo |
| `T` | Enciende los dos |
| `A` | Apaga los dos |
| `P` | Modo parpadeo alterno (500 ms) |
| `E` | Informa el estado |
| `?` | Muestra la ayuda |

Acepta mayúsculas y minúsculas. Un carácter no válido responde `ERROR: comando no reconocido`.

## Nota sobre la simulación

Wokwi no simula Bluetooth. El HC-05 es un puente transparente entre Bluetooth y el puerto serial, así que para el Arduino solo existe el enlace serial. En la simulación, el Monitor serie de Wokwi está conectado a ese mismo puerto (pines 0 y 1) y cumple el papel del celular.
