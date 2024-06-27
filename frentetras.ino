#include <WiFi.h>
#include <WebServer.h>

#define LED_BUILTIN 2

const char* ssid = "YourSSID";  // Substitua com seu SSID
const char* password = "YourPassword";  // Substitua com sua senha
const int motor1Pin1 = 23;
const int motor1Pin2 = 22;
const int motor2Pin1 = 21;
const int motor2Pin2 = 19;

WebServer server(80);  // Inicializa o servidor web na porta 80

// Função para lidar com a requisição GET na URL "/ligar"
void handleLigar() {
  digitalWrite(LED_BUILTIN, LOW);  // Liga o LED (LOW porque o LED é ativo baixo)digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  server.send(200, "text/plain", "LED ligado");
}

// Função para lidar com a requisição GET na URL "/desligar"
void handleDesligar() {
  digitalWrite(LED_BUILTIN, HIGH);  // Desliga o LED (HIGH porque o LED é ativo baixo)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  server.send(200, "text/plain", "LED desligado");
}

// Função para lidar com a requisição GET na URL raiz
void handleRoot() {
  String html = "<html><body>"
                "<h1>Controle do LED</h1>"
                "<p><a href=\"/ligar\">Ligar LED</a></p>"
                "<p><a href=\"/desligar\">Desligar LED</a></p>"
                "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
 
  // Configurar o LED embutido como saída
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Certificar-se de que o LED está desligado inicialmente
 
  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Imprimir o endereço IP
  Serial.println(WiFi.localIP());

  // Definir os handlers para as URLs específicas
  server.on("/", handleRoot);  // Handler para a URL raiz
  server.on("/ligar", handleLigar);  // Handler para a URL /ligar
  server.on("/desligar", handleDesligar);  // Handler para a URL /desligar

  // Iniciar o servidor
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Manter o servidor rodando
  server.handleClient();
}
