#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    uint8_t b;
} struct_message;

// Create a struct_message called myData
struct_message myData;

void runsequence();

int Blue = 16;
int Red = 7;
int Green = 15;


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Series: ");
  Serial.println(myData.b);
  runsequence();
}
 
void setup() {


  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  digitalWrite(Red, LOW);
  digitalWrite(Green, LOW);
  digitalWrite(Blue, LOW);

  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}

void runsequence() {
  switch (myData.b) {
    case 0:
      break;
    case 1: //sport pistol
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(3000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(3000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(3000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(3000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(3000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(10000);
      digitalWrite(Red, LOW);
      break;
    
    case 3: // Standard pistol
      break;
    
    case 4: //rapid 4s
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(4000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(10000);
      digitalWrite(Red, LOW);
      break;

    case 6: //rapid 6s
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(6000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(10000);
      digitalWrite(Red, LOW);
      break;

    case 8://rapid fire 8s
      digitalWrite(Red, HIGH);
      delay(7000);
      digitalWrite(Red, LOW);
      digitalWrite(Green, HIGH);
      delay(8000);
      digitalWrite(Green, LOW);
      digitalWrite(Red, HIGH);
      delay(10000);
      digitalWrite(Red, LOW);
      break;
  }
}