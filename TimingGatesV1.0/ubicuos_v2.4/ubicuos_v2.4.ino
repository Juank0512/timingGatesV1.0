#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "Juank0512";
const char* password = "91051227340";

const int utcOffsetInSeconds = -18000;  // Ajusta esto en -18000 segundos que es la zona horaria de colombia

const int ldrPin = 2;  // Pin analógico donde está conectado el fotosensor

const char* host = "192.168.167.11"; //"192.168.167.11";      // Dirección IP local o remota, del Servidor Web
const int   port = 80;            // Puerto, HTTP es 80 por defecto, cambiar si es necesario.
const int   watchdog = 2000;        // Frecuencia del Watchdog
unsigned long previousMillis = millis(); 
unsigned long tiempoInicial = millis();
String line;
int hora =0;
int minutos=0;
int segundos=0;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int estadoAnterior = LOW;
unsigned long tiempoCambio = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Conectando al WiFi...");
  }

  timeClient.begin();
  timeClient.update();
  Serial.print("Hora actual: ");
  Serial.println(timeClient.getFormattedTime());

  pinMode(ldrPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  int estadoActual = digitalRead(ldrPin);

  if (estadoActual != estadoAnterior) {
    if (estadoActual == HIGH) {
      // Se detectó luz
      tiempoCambio = millis();
      timeClient.update();
      hora = timeClient.getHours();
      minutos = timeClient.getMinutes();
      segundos = timeClient.getSeconds();
      Serial.print("Cambio a luz. Hora: ");
      Serial.print(hora);
      Serial.print("  minutos: ");
      Serial.print(minutos);
      Serial.print(" segundos: ");
      Serial.print(segundos);
      Serial.print(", Milisegundos: ");
      Serial.println(tiempoCambio);
      if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
  if (!client.connect(host, port)) {
    Serial.println("Conexión falló...");
    return;
  }
  String url = "/TimingGates/tiempo_final.php?hora_final=";
  url += hora;
  url += "&minutos_final=";
  url += minutos;
  url += "&segundos_final=";
  url += segundos;
  url += "&milesimas_final=";
  url += tiempoCambio;

  // Envío de la solicitud al Servidor
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" + 
             "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Superado tiempo de espera!");
      client.stop();
      return;
    }
  }
  // Lee respuesta del servidor
    while(client.available()){
      line = client.readStringUntil('\r');
      Serial.print(line);
    }
      Serial.print("Dato ENVIADO");
      Serial.print(" \t");
      delay(100);

  }
    } /*else {
      // Se quedó a oscuras
      tiempoCambio = millis();
      timeClient.update();
      Serial.print("Cambio a oscuridad. Hora: ");
      Serial.print(timeClient.getFormattedTime());
      Serial.print(", Milisegundos: ");
      Serial.println(tiempoCambio);
    }*/
  }

  estadoAnterior = estadoActual;
  delay(100);  // pausa para evitar rebotes del ldr
  
}
