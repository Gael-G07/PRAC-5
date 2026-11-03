/*
  Práctica: Control automático de ventilación
  Placa: Arduino UNO
  Entrada: Sensor de temperatura LM35 (pin A0)
  Salida: LED que simula el ventilador (pin 8, con resistencia de 220 ohm)
  Comunicación: Monitor serial a 9600 baudios

  Conexiones:
    LM35  pin 1 (+Vs)  -> 5V
    LM35  pin 2 (Vout) -> A0
    LM35  pin 3 (GND)  -> GND
    LED ánodo (+) -> resistencia 220 ohm -> pin 8
    LED cátodo (-) -> GND
*/

const int PIN_SENSOR = A0;       // Entrada analógica del LM35
const int PIN_LED = 8;           // Salida que simula el ventilador
const float LIMITE = 30.0;       // Temperatura límite en °C

float temperatura = 0.0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  Serial.begin(9600);
  Serial.println("Sistema de control automatico de ventilacion");
  Serial.println("--------------------------------------------");
}

float leerTemperatura() {
  // Promedio de 10 lecturas para reducir ruido
  long suma = 0;
  for (int i = 0; i < 10; i++) {
    suma += analogRead(PIN_SENSOR);
    delay(10);
  }
  float lectura = suma / 10.0;

  // LM35: 10 mV por °C, referencia de 5 V, resolución de 10 bits
  float voltaje = lectura * (5.0 / 1023.0);
  return voltaje * 100.0;
}

void loop() {
  // 1. Leer temperatura
  temperatura = leerTemperatura();

  // 2. Procesar la información y 3. Controlar el actuador
  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" C -> ");

  if (temperatura > LIMITE) {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("Encender motor (LED ON)");
  } else {
    digitalWrite(PIN_LED, LOW);
    Serial.println("Apagar motor (LED OFF)");
  }

  delay(1000);
}
