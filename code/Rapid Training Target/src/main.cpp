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

const int Blue = GPIO_NUM_6;
const int Green = GPIO_NUM_4;
const int Red = GPIO_NUM_5;
bool active = 0;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  runsequence();
  
}
 
void setup() {
  pinMode(GPIO_NUM_8, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  digitalWrite(Red, HIGH);
  digitalWrite(Green, HIGH);
  digitalWrite(Blue, HIGH);

  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    digitalWrite(GPIO_NUM_8, HIGH);
    return;
  }
  digitalWrite(GPIO_NUM_8, LOW);
  /*
  Serial.print("ESP Board BASE MAC Address:  ");
  Serial.println(WiFi.macAddress());
  

  uint8_t sta_mac[6];
  char buffer [6];
  esp_efuse_mac_get_default(sta_mac);

  esp_read_mac(sta_mac, ESP_MAC_WIFI_SOFTAP);

  Serial.print("SOFT AP MAC Address:  ");
  
  sprintf(buffer, "%02X:%02X:%02X:%02X:%02X:%02X", sta_mac[0], sta_mac[1], sta_mac[2], sta_mac[3], sta_mac[4], sta_mac[5], sta_mac[6]);
  Serial.println(buffer);

  esp_read_mac(sta_mac, ESP_MAC_WIFI_STA);

  Serial.print("STATION MAC Address:  ");
  
  sprintf(buffer, "%02X:%02X:%02X:%02X:%02X:%02X", sta_mac[0], sta_mac[1], sta_mac[2], sta_mac[3], sta_mac[4], sta_mac[5], sta_mac[6]);
  Serial.println(buffer); 
  */

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
    case 4: //rapid 4s
      digitalWrite(Red, LOW);
      delay(3000);
      digitalWrite(Red, HIGH);
      analogWrite(Green, 192);
      delay(4000);
      analogWrite(Green, 255);
      digitalWrite(Red, LOW);
      delay(3000);
      digitalWrite(Red, HIGH);

      break;

    case 6: //rapid 6s
      digitalWrite(Red, LOW);
      delay(3000);
      digitalWrite(Red, HIGH);
      analogWrite(Green, 192);
      delay(6000);
      analogWrite(Green, 255);
      digitalWrite(Red, LOW);
      delay(3000);
      digitalWrite(Red, HIGH);
      break;

    case 8://rapid fire 8s
      digitalWrite(Red, LOW);
      delay(3000);
      digitalWrite(Red, HIGH);
      analogWrite(Green, 192);
      delay(8000);
      analogWrite(Green, 255);
      digitalWrite(Red, LOW);
      delay(3000);
      digitalWrite(Red, HIGH);
      break;
  }
}