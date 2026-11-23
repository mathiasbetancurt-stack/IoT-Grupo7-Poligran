/*
===========================================================
   POLITECNICO GRANCOLOMBIANO - INTERNET DE LAS COSAS
   ENTREGA 2 - CONTROL DE LED POR BLUETOOTH (ENLACE SERIAL)
===========================================================
Grupo 7 IoT

DESCRIPCION
  El Arduino recibe comandos de un celular a traves de un
  modulo Bluetooth HC-05/HC-06 y enciende o apaga dos LED.

  El HC-05 funciona como un puente transparente: lo que el
  celular envia por Bluetooth, el modulo lo entrega al Arduino
  por su puerto serial (UART). Para el Arduino solo existe el
  enlace serial; por eso este programa se comunica con
  Serial.read() y Serial.print().

CONEXION FISICA DEL HC-05 (montaje real)
  HC-05 VCC -> 5V
  HC-05 GND -> GND
  HC-05 TXD -> RX  (pin 0 del Arduino)
  HC-05 RXD -> TX  (pin 1 del Arduino) a traves de un divisor
               de voltaje 1 kOhm / 2 kOhm, porque el RXD del
               HC-05 trabaja a 3.3 V.
  Nota: al cargar el programa por USB hay que desconectar los
  cables de los pines 0 y 1, porque el USB usa el mismo puerto.

SIMULACION EN WOKWI
  Wokwi no simula Bluetooth. El Monitor serie de Wokwi esta
  conectado al mismo puerto serial (pines 0 y 1) donde iria el
  HC-05, asi que cumple el papel del celular: lo que se escribe
  ahi llega al Arduino exactamente igual que si viniera del
  modulo Bluetooth.

ENLACE SERIAL
  9600 baudios, 8 bits de datos, sin paridad, 1 bit de parada
  (8N1). Es la configuracion de fabrica del HC-05 en modo datos.

SALIDAS
  LED verde -> pin 8 (resistencia de 220 Ohm)
  LED rojo  -> pin 9 (resistencia de 220 Ohm)

COMANDOS (una letra, mayuscula o minuscula)
  V : enciende el LED verde
  R : enciende el LED rojo
  T : enciende todos
  A : apaga todos
  P : modo parpadeo (los dos LED alternan cada 500 ms)
  E : informa el estado de los LED
  ? : muestra la lista de comandos
===========================================================
*/

// ----- Configuracion -----
const long BAUDIOS = 9600;            // Velocidad del enlace serial (HC-05).
const byte LED_VERDE = 8;
const byte LED_ROJO = 9;
const unsigned long PARPADEO_MS = 500;

// ----- Estado del sistema -----
bool verdeEncendido = false;
bool rojoEncendido = false;
bool modoParpadeo = false;
bool faseParpadeo = false;
unsigned long ultimoParpadeo = 0;
unsigned long comandosRecibidos = 0;

// Aplica el estado de las variables a los pines.
void actualizarLeds() {
  digitalWrite(LED_VERDE, verdeEncendido ? HIGH : LOW);
  digitalWrite(LED_ROJO, rojoEncendido ? HIGH : LOW);
}

// Escribe el tiempo transcurrido en segundos, como [12.3 s].
void marcaDeTiempo() {
  Serial.print('[');
  Serial.print(millis() / 1000.0, 1);
  Serial.print(" s] ");
}

void mostrarEstado() {
  Serial.print("Estado -> Verde: ");
  Serial.print(verdeEncendido ? "ON" : "OFF");
  Serial.print(" | Rojo: ");
  Serial.print(rojoEncendido ? "ON" : "OFF");
  Serial.print(" | Parpadeo: ");
  Serial.print(modoParpadeo ? "SI" : "NO");
  Serial.print(" | Comandos recibidos: ");
  Serial.println(comandosRecibidos);
}

void mostrarAyuda() {
  Serial.println("Comandos: V=verde  R=rojo  T=todos  A=apagar  P=parpadeo  E=estado  ?=ayuda");
}

// Interpreta un comando recibido por el enlace serial.
void procesarComando(char comando) {
  comandosRecibidos++;
  marcaDeTiempo();
  Serial.print("RX '");
  Serial.print(comando);
  Serial.print("' -> ");

  switch (comando) {
    case 'V':
      modoParpadeo = false;
      verdeEncendido = true;
      rojoEncendido = false;
      Serial.println("OK: LED verde encendido");
      break;
    case 'R':
      modoParpadeo = false;
      verdeEncendido = false;
      rojoEncendido = true;
      Serial.println("OK: LED rojo encendido");
      break;
    case 'T':
      modoParpadeo = false;
      verdeEncendido = true;
      rojoEncendido = true;
      Serial.println("OK: todos los LED encendidos");
      break;
    case 'A':
      modoParpadeo = false;
      verdeEncendido = false;
      rojoEncendido = false;
      Serial.println("OK: todos los LED apagados");
      break;
    case 'P':
      modoParpadeo = true;
      ultimoParpadeo = millis();
      Serial.println("OK: modo parpadeo activado");
      break;
    case 'E':
      Serial.println("OK: consulta de estado");
      break;
    case '?':
      Serial.println("OK: ayuda");
      mostrarAyuda();
      break;
    default:
      comandosRecibidos--;          // No se cuenta un comando invalido.
      Serial.println("ERROR: comando no reconocido. Envie ? para ver la ayuda");
      return;
  }

  actualizarLeds();
  mostrarEstado();
}

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  actualizarLeds();

  Serial.begin(BAUDIOS);
  Serial.println("=== ENTREGA 2 IoT: CONTROL DE LED POR BLUETOOTH ===");
  Serial.println("Enlace serial listo: 9600 baudios, 8N1 (HC-05 en pines 0 y 1)");
  mostrarAyuda();
  mostrarEstado();
}

void loop() {
  // 1. Leer los caracteres que llegan por el enlace serial.
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\r' || c == '\n' || c == ' ') continue;  // Ignora fin de linea y espacios.
    if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';       // Acepta minusculas.
    procesarComando(c);
  }

  // 2. Modo parpadeo sin detener el programa (millis, sin delay).
  if (modoParpadeo && millis() - ultimoParpadeo >= PARPADEO_MS) {
    ultimoParpadeo = millis();
    faseParpadeo = !faseParpadeo;
    verdeEncendido = faseParpadeo;
    rojoEncendido = !faseParpadeo;
    actualizarLeds();
  }
}
