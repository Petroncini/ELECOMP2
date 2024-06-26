#include <WiFi.h>

const int motor1Pin1 = 23;
const int motor1Pin2 = 22;
const int motor2Pin1 = 21;
const int motor2Pin2 = 19;

bool movingForward = false;
bool movingBackward = false;

void setup() {
  Serial.begin(115200);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

    if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim(); 
    
    if (inputString.equalsIgnoreCase("frente")) {
      forward();
    } else if (inputString.equalsIgnoreCase("tras")) {
      backward();
    } else if (inputString.equalsIgnoreCase("esquerda")) {
      left();
    } else if (inputString.equalsIgnoreCase("direita")) {
      right();
    } else {
      Serial.println("Comando inválido. Por favor, digite: frente, tras, esquerda ou direita");
    }
    }
    else{
      forward();
      delay(1000);
      backward();
      delay(1000);
      right();
      delay(1000);
      left();
      delay(1000);
      stop();
      delay(3000);
    }
}

void forward() {
  movingForward = true;
  movingBackward = false;
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin1, HIGH);
}

void backward() {
  movingForward = false;
  movingBackward = true;
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin2, HIGH);
}

void left() {
  movingForward = false;
  movingBackward = false;
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
}

void right() {
  movingForward = false;
  movingBackward = false;
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin2, HIGH);
}

void stop() {
  movingForward = false;
  movingBackward = false;
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
