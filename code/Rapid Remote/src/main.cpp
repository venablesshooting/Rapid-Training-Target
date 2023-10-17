
#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xA0, 0x76, 0x4E, 0x41, 0xA9, 0xD0};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    uint8_t b;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
bool sendFlag = false;
 
void setup() {
  pinMode(GPIO_NUM_3, OUTPUT); // LDO enable
  digitalWrite(GPIO_NUM_3, HIGH); // Initialise holding the LDO on until button released
  pinMode(GPIO_NUM_5, INPUT); // 8s
  pinMode(GPIO_NUM_6, INPUT); // 6s
  pinMode(GPIO_NUM_7, INPUT); // 4s
  
  
  Serial.begin(115200);// Init Serial Monitor
  WiFi.mode(WIFI_STA);// Set device as a Wi-Fi Station

 
  if (esp_now_init() != ESP_OK) { // Init ESP-NOW
    //Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    //Serial.println("Failed to add peer");
    return;
  }

   if(digitalRead(GPIO_NUM_5)){
    if(!sendFlag){
    myData.b = 8;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    sendFlag = true;
    //delay(10000);
    }
  }
  else if(digitalRead(GPIO_NUM_6)){
    if(!sendFlag){
    myData.b = 6;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    sendFlag = true;
    //delay(10000);
    }
   
  }
  else if(digitalRead(GPIO_NUM_7)){
    if(!sendFlag){
    myData.b = 4;
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    sendFlag = true;
    //delay(10000);
    }
  }else{
    sendFlag = false;
  }
}
 
void loop() {
  // Set values to send
 
  
  digitalWrite(GPIO_NUM_3,LOW); // turn off the LDO
  // Send message via ESP-NOW
}
