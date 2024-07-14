#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Personal-401 2.4GHz";
const char* password = "D454C15401";
// const char* serverUrl = "http://tu_dominio.com/guardar_datos.php";

const int sensorPin = A0; // Pin analógico para el sensor de humedad
const int relayPin = D1; // Pin digital para el relay (controla la bomba)
const int buzzerPin = D2; // Pin digital para el buzzer

const int humidityThreshold = 500;
const int pumpDuration = 5000;

WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");
}

void loop() {
  int humedad = analogRead(sensorPin);
  Serial.print("Humedad: ");
  Serial.println(humedad);

  if (humedad > humidityThreshold) {
    digitalWrite(relayPin, HIGH);
    tone(buzzerPin, 1000);
    delay(pumpDuration);
    digitalWrite(relayPin, LOW);
    noTone(buzzerPin);
    delay(8000);
  } else {
    delay(5000);
  }

  // if (WiFi.status() == WL_CONNECTED) {
  //   HTTPClient http;
  //   http.begin(wifiClient, serverUrl);
  //   http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  //   String postData = "humedad=" + String(humedad) + "&voltaje=0"; // Asegúrate de enviar el voltaje correcto si tienes el sensor de voltaje conectado

  //   int httpResponseCode = http.POST(postData);

  //   if (httpResponseCode > 0) {
  //     String response = http.getString();
  //     Serial.println(httpResponseCode);
  //     Serial.println(response);
  //   } else {
  //     Serial.println("Error en la petición HTTP");
  //   }

  //   http.end();
  // }

  delay(1000);
}
