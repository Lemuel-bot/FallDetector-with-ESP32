#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <HTTPClient.h>

Adafruit_MPU6050 mpu;

// Wi-Fi credentials (Only works on real ESP32)
const char* ssid = "Galaxy A13 C958";
const char* password = "iuma2020";

// Telegram Bot Credentials 
const char* telegramBotToken = "7775742203:AAGPh5-BJaZahAW4FRlX8_xyqCfmsOaRKe0";
const char* chatID = "6973280311";

#define BUZZER_PIN 5
#define LED_PIN 4
#define FALL_THRESHOLD 2.0  // Adjust sensitivity

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  if (!mpu.begin()) {
    Serial.println("MPU6050 initialization failed!");
    while (1);
  }
  Serial.println("MPU6050 initialized successfully!");

  // closing setup`
#ifdef WOKWI_SIMULATION
  Serial.println("\n⚠️ Running in Wokwi - Skipping Wi-Fi Connection...");
#else
  WiFi.begin(ssid, password);
  int timeout = 10; // Max wait time of 10 seconds
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
      delay(1000);
      Serial.print(".");
      timeout--;
  }
  if (timeout == 0) {
      Serial.println("\n❌ Wi-Fi Failed to Connect!");
  } else {
      Serial.println("\n✅ Wi-Fi Connected!");
  }
#endif
}  // Fix: Closing `setup()`

// Main loop (Reads acceleration and detects falls)
void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float accelMagnitude = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z));
  Serial.print("Acceleration Magnitude: ");
  Serial.println(accelMagnitude);

  if (accelMagnitude < FALL_THRESHOLD) {  
    Serial.println("⚠️ Fall Detected! Activating Buzzer & LED...");

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);

#ifdef WOKWI_SIMULATION
    Serial.println("📩 [SIMULATED] Telegram Alert: 🚨 Fall Detected!");
#else
    sendTelegramMessage("🚨 Fall Detected! Immediate attention required!");
#endif
    delay(5000);
  }

  delay(500);
}

// Telegram Message Function
void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + String(telegramBotToken) + "/sendMessage?chat_id=" + String(chatID) + "&text=" + message;
    
    http.begin(url);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.println("✅ Telegram Alert Sent!");
    } else {
      Serial.println("❌ Telegram Failed!");
    }
    
    http.end();
  }
}
