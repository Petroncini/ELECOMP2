#include <WiFi.h>

// Defina o SSID e a senha da rede do seu celular
const char *ssid = "Galazy A12 D5AA";
const char *password = "snsn0116";

// Defina os pinos para controlar os motores
const int motor1Pin1 = 23;
const int motor1Pin2 = 22;
const int motor2Pin1 = 21;
const int motor2Pin2 = 19;
const int pinoled = 2;

WiFiServer server(80);

// Variáveis para armazenar o estado atual dos motores
bool movingForward = false;
bool movingBackward = false;

void setup() {
  Serial.begin(115200);

  // Configuração dos pinos dos motores como saída
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(pinoled, OUTPUT);

  // Conectar-se à rede Wi-Fi
  Serial.println("Conectando-se à rede Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Tentando conectar...");
  }

  Serial.println("Conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicia o servidor
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Controle do carrinho
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

    if (request.indexOf("/FORWARD") != -1 && !movingBackward) {
      forward();
    } else if (request.indexOf("/BACKWARD") != -1 && !movingForward) {
      backward();
    } else if (request.indexOf("/LEFT") != -1) {
      left();
    } else if (request.indexOf("/RIGHT") != -1) {
      right();
    } else if (request.indexOf("/STOP") != -1) {
      stop();
    }

    // Envia uma resposta ao cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println("");
    client.println("OK");
    client.stop();
    //entrada = 
    if (Serial.available() > 0) {
    // Lê a string do monitor serial
    String inputString = Serial.readStringUntil('\n');
    inputString.trim(); // Remove qualquer espaço em branco no início e fim da string
    
    // Verifica a entrada e responde de acordo
    if (inputString.equalsIgnoreCase("frente")) {
      Serial.println("Movendo para frente");
    } else if (inputString.equalsIgnoreCase("tras")) {
      Serial.println("Movendo para trás");
    } else if (inputString.equalsIgnoreCase("esquerda")) {
      Serial.println("Virando para a esquerda");
    } else if (inputString.equalsIgnoreCase("direita")) {
      Serial.println("Virando para a direita");
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