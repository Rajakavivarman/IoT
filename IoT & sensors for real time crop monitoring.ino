// Include Libraries
#define BLYNK_TEMPLATE_ID "TMPL3pOiVHzEa"
#define BLYNK_TEMPLATE_NAME "crop monitoring"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Blynk Credentials
char auth[] = "wHP1AW066dZAw1JvXWwVDaEjr8l-ZKdl";  // Enter Blynk Auth Token
char ssid[] = "OC";  // Enter your WiFi name
char pass[] = "12345678";  // Enter your WiFi password

// Sensor Pins
#define DHTPIN 4         // DHT11 Data Pin
#define SOIL_PIN 35      // Soil Sensor Analog Pin
#define LDR_PIN 34       // LDR Analog Pin

// Initialize DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() {
  Blynk.run();
  readSensors();
  delay(1000);
}

void readSensors() {
  float temperature = dht.readTemperature();  // Read Temperature (Celsius)
  float humidity = dht.readHumidity();       // Read Humidity
  int soil_moisture = analogRead(SOIL_PIN);  // Read Soil Moisture
  int ldr_value = analogRead(LDR_PIN);       // Read Light Intensity

  // Convert Soil Moisture to Percentage (Adjust according to your sensor)
  int soil_percentage = map(soil_moisture, 4095, 1500, 0, 100);
  if (soil_percentage < 0) soil_percentage = 0;
  if (soil_percentage > 100) soil_percentage = 100;

  // Convert LDR to Percentage (Higher value = Darker)
  int light_percentage = map(ldr_value, 4095, 0, 0, 100);

  // Print values to Serial Monitor
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println("°C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println("%");
  Serial.print("Soil Moisture: "); Serial.print(soil_percentage); Serial.println("%");
  Serial.print("Light Intensity: "); Serial.print(light_percentage); Serial.println("%");
  Serial.println("---------------------");

  // Send data to Blynk (Virtual Pins)
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, soil_percentage);
  Blynk.virtualWrite(V4, light_percentage);
}