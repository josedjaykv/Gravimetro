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
float gravedad = 0;
const int fotoresistorPin2 = A1;
const int ledPin2 = 13; 
float L = 0.09;
unsigned long tiempoInicio = 0;
unsigned long tiempoDuracion = 0;
int contador = -1;
int estadoFoto2Anterior = 1;  
bool enProceso = false;
bool mostrarGravedad = false;

void setup() {
  pinMode(ledPin2, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gravimetro JCVC");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("(1) Empezar");
}

void mostrarGravedadLCD(float gravedad, int contador) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gravedad:");
  lcd.setCursor(0, 1);
  lcd.print(gravedad, 2);
  lcd.print(" - ");
  lcd.print(contador);
}

void loop() {
  char key = myKeypad.getKey();

  if (key == '1' && !enProceso) {
    enProceso = true;
    contador = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Procesando...");
  }

  if (enProceso) {
    digitalWrite(ledPin2, HIGH);
    int valor2 = analogRead(fotoresistorPin2);

    if (valor2 < 800 && estadoFoto2Anterior == 1) {
      estadoFoto2Anterior = 0;
    } else if (valor2 >= 800 && estadoFoto2Anterior == 0) {
      estadoFoto2Anterior = 1;
      contador++;
      mostrarGravedadLCD(gravedad, contador); // Muestra el contador cada vez que cambia
    }

    if (contador == 1) {
      if (tiempoInicio == 0) {
        tiempoInicio = millis();
      }
    } else if (contador == 20) {
      if (tiempoInicio > 0) {
        tiempoDuracion = millis() - tiempoInicio;
        float tiempoSegundos = tiempoDuracion / 1000.0;
        float T = tiempoSegundos / 10;        

        gravedad = (4 * PI * PI * L) / (T * T);
        mostrarGravedad = true;
        tiempoInicio = 0;
      }
    }
  }

  if (mostrarGravedad) {
    mostrarGravedadLCD(gravedad, contador);
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("(2) Volver intentar");
    mostrarGravedad = false;
    enProceso = false;
  }
  
  if (key == '2' && !enProceso) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("(1) Empezar");
  }
}
