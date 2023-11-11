
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


### Configuracion Inicial
```c++
unsigned long tiempoInicio = 0;
unsigned long tiempoDuracion = 0;

int estadoFoto1 = 1;
int estadoFoto2 = 1;

bool primeraVez = true;
```

Aquí se definen variables para gestionar el tiempo de caída (`tiempoInicio` y `tiempoDuracion`), el estado de las fotorresistencias (`estadoFoto1` y `estadoFoto2`), y una bandera (`primeraVez`) para controlar la primera ejecución.


### void setup()
```c++
void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gravimetro JCVC");
  delay(5000);  // Espera 5 segundos antes de mostrar el siguiente mensaje
}
```

Aquí se realiza la configuración inicial en la función `setup()`. Se establecen los pines de los LEDs como salidas, se inicia la comunicación con la pantalla LCD y se muestra un mensaje de bienvenida durante 5 segundos.


### void mostrarMensaje()
```c++
void mostrarMensaje(String mensaje) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mensaje);
}
```

Esta función se utiliza para mostrar mensajes en la pantalla LCD. Borra la pantalla, posiciona el cursor en la esquina superior izquierda y muestra el mensaje proporcionado.Esta función se utiliza para mostrar mensajes en la pantalla LCD. Borra la pantalla, posiciona el cursor en la esquina superior izquierda y muestra el mensaje proporcionado.


### void loop()
```c++
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
    ...
  }
}
```

Si es la primera vez, se muestra un mensaje para iniciar (`(1) Empezar`). Si se presiona la tecla '1', se cambia `primeraVez` a `false` y se muestra otro mensaje.
Después de la primera vez, se lee el valor de las fotorresistencias y se determina su estado.


```c++
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
    ...
  }
```

Aqui se leen los valores de las fotoresistencias y se determina el estado de cada una. Y uego se enciende/prenden los leds.
Se inicia o detiene el temporizador según el estado de la primera fotorresistencia (`estadoFoto1`). Si se detecta el estado de la segunda fotorresistencia (`estadoFoto2`) en "bajo" (la luz es bloqueada), se realiza el cálculo de la gravedad y se muestra en la pantalla LCD.


```c++
if (estadoFoto2 == 0) {
  if (tiempoInicio > 0) {
    tiempoDuracion = millis() - tiempoInicio;
    float tiempoSegundos = tiempoDuracion / 1000.0;
    float gravedad = (distancia) / (tiempoSegundos * tiempoSegundos);
    mostrarMensaje("Gravedad: " + String(gravedad, 2));
    tiempoInicio = 0;
    delay(5000);
    mostrarMensaje("Lanza el objeto!");
  }
}
```

Si se detecta el estado de la segunda fotorresistencia en "bajo" y el temporizador se ha iniciado, se calcula la duración de la caída (`tiempoDuracion`) y se utiliza para calcular la gravedad. Se muestra el resultado en la pantalla LCD y se espera 5 segundos antes de mostrar el mensaje para lanzar el objeto nuevamente.
