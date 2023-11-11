#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 1;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'}
};
byte rowPins[ROWS] = {9};
byte colPins[COLS] = {10, 11, 12};
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
const int fotoresistorPin1 = A0;
const int fotoresistorPin2 = A1;
const int ledPin1 = 8;
const int ledPin2 = 13;
float distancia = 0.136;

unsigned long tiempoInicio = 0;
unsigned long tiempoDuracion = 0;

int estadoFoto1 = 1;
int estadoFoto2 = 1;

bool primeraVez = true;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gravimetro JCVC");
  delay(5000);  // Espera 5 segundos antes de mostrar el siguiente mensaje
}

void mostrarMensaje(String mensaje) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mensaje);
}

void loop() {
  char key = myKeypad.getKey();

  if (primeraVez) {
    mostrarMensaje("(1) Empezar");
    if (key == '1') {
      primeraVez = false;
      mostrarMensaje("Lanza el objeto!");
    }
    delay(1000);  // Pequeña pausa para evitar la detección accidental del botón
  } else {
    // Leer el valor de las fotorresistencias
    int valor1 = analogRead(fotoresistorPin1);
    int valor2 = analogRead(fotoresistorPin2);

    // Determinar el estado de las fotorresistencias
    if (valor1 < 500) {
      estadoFoto1 = 0;
    } else {
      estadoFoto1 = 1;
    }
    if (valor2 < 800) {
      estadoFoto2 = 0;
    } else {
      estadoFoto2 = 1;
    }

    // Controlar los LEDs (siempre están encendidos)
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);

    // Iniciar o detener el temporizador
    if (estadoFoto1 == 0) {
      if (tiempoInicio == 0) {
        tiempoInicio = millis();
      }
    } else if (estadoFoto2 == 0) {
      if (tiempoInicio > 0) {
        tiempoDuracion = millis() - tiempoInicio;
        float tiempoSegundos = tiempoDuracion / 1000.0;
        float gravedad = (distancia) / (tiempoSegundos * tiempoSegundos);
        mostrarMensaje("Gravedad: " + String(gravedad, 2));
        tiempoInicio = 0;
        delay(5000);  // Espera 5 segundos antes de mostrar el siguiente mensaje
        mostrarMensaje("Lanza el objeto!");
      }
    }
  }
}
