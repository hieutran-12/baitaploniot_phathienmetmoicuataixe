#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Hieu_ne";       // Thay bằng WiFi của bạn
const char* password = "thuycute"; 

ESP8266WebServer server(80);  // Khởi tạo Web Server

#define BUZZER_PIN 14  // Chân D5 (GPIO14) cho còi
#define RELAY_PIN 12   // Chân D6 (GPIO12) cho relay phun nước

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
    
    digitalWrite(BUZZER_PIN, LOW);  // Ban đầu tắt còi
    digitalWrite(RELAY_PIN, LOW);   // Ban đầu tắt relay

    // Chờ kết nối WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
    Serial.print("ESP IP Address: ");
    Serial.println(WiFi.localIP());

    // Khai báo endpoint
    server.on("/alert", handleAlert);
    server.on("/normal", handleNormal);
    server.on("/spray", handleSpray);
    
    server.begin();
}

void loop() {
    server.handleClient();
}

// 🔊 Bật còi báo động
void handleAlert() {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("🚨 Cảnh báo: Bật còi!");
    server.send(200, "text/plain", "Buzzer ON");
}

// ✅ Tắt còi báo động
void handleNormal() {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("✅ Trạng thái bình thường: Tắt còi.");
    server.send(200, "text/plain", "Buzzer OFF");
}

// 💦 Kích hoạt phun nước trong 15s
void handleSpray() {
    Serial.println("💦 Kích hoạt phun nước trong 15 giây!");
    digitalWrite(RELAY_PIN, HIGH);
    delay(15000);  // Giữ relay bật 15 giây
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("💧 Tắt phun nước.");
    server.send(200, "text/plain", "Spray Activated");
}
