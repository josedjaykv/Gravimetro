
# Gravimetro
Por Jose David Jayk Vanegas, Camilo Valencia, Samuel Corrales y Diego Collazos


### Configuraion de pines y objetos
```c++
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
```

Se incluyen las bibliotecas necesarias (`Keypad` y `LiquidCrystal`).
Se configuran las dimensiones y el mapeo del teclado matricial.
Se crean objetos para representar el teclado (`myKeypad`) y la pantalla LCD (`lcd`).
Se definen pines para los fotoresistores, LEDs y se establece la distancia entre las fotorresistencias.
