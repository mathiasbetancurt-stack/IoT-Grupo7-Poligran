# Evidencias de las pruebas – Entrega 2

Capturas de la simulación en Wokwi. Cada imagen corresponde a una figura o a un caso de la tabla de pruebas del artículo.

## Figuras del artículo

| Archivo | Contenido |
|---|---|
| `fig1_arquitectura.png` | Diagrama de bloques: celular → HC-05 → Arduino UNO → LED |
| `fig2_circuito_wokwi.png` | Circuito en Wokwi: Arduino UNO, LED verde y rojo, resistencias de 220 Ω |
| `fig3_monitor_serie.png` | Monitor serie con la secuencia de comandos y sus respuestas |
| `fig4_leds_V.png`, `fig4_leds_R.png`, `fig4_leds_T.png` | LED verde encendido, rojo encendido y los dos encendidos |

## Casos de prueba

Escribir cada entrada en el Monitor serie de Wokwi y guardar la captura como `P<n>.png`.

| ID | Entrada | Resultado esperado |
|---|---|---|
| P1 | (inicio) | Bienvenida, ayuda y estado: verde OFF, rojo OFF, parpadeo NO, 0 comandos |
| P2 | `V` | `OK: LED verde encendido`. Verde ON, rojo OFF |
| P3 | `R` | `OK: LED rojo encendido`. Verde OFF, rojo ON |
| P4 | `T` | `OK: todos los LED encendidos` |
| P5 | `A` | `OK: todos los LED apagados` |
| P6 | `P` | `OK: modo parpadeo activado`. Los LED alternan cada 500 ms |
| P7 | `V` (en parpadeo) | Sale del parpadeo y queda solo el verde encendido |
| P8 | `E` | Muestra el estado sin cambiar los LED |
| P9 | `?` | Muestra la lista de comandos |
| P10 | `v` (minúscula) | Igual que `V` |
| P11 | `X` | `ERROR: comando no reconocido`. No cambia los LED ni el contador |
| P12 | `vra` | Procesa V, R y A en orden; al final los dos apagados y el contador sube en 3 |
