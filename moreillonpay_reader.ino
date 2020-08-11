/*
 * Board type: ESP32 Dev module
 */

// Libraries
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include "SSD1306.h"

#include "credentials.h";
#include "moreillonpay_credentials.h";

// Import fonts and images for the display
#include "font.h"
#include "images.h"

// API parameters
#define API_URL "http://192.168.1.2:7342/transaction"
#define TRANSACTION_AMOUNT "-60"
#define TRANSACTION_DESCRIPTION "JPY 60 Coffee"

// Wifi settings
#define WIFI_CONNECTION_TIMEOUT 5000

// IO
#define SDA_PIN 5
#define SCL_PIN 4

#define SPI_SCK_PIN 14
#define SPI_MISO_PIN 12
#define SPI_MOSI_PIN 13

// Double check if working with RST on DPIO2
#define RFID_RST_PIN 16
#define RFID_SS_PIN 15
#define BUZZER_PIN 25

// RFID parameters
#define UID_SIZE 4

// Display parameters
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_MESSAGE_LENGTH 3000
#define DISPLAY_INVERSION_PERIOD 60000

// Buzzer parameters
#define BUZZER_CHANNEL 0
#define BUZZER_RESOLUTION 8

// RFID parameters
#define RFID_SELF_TEST_PERIOD 5000

// Create MFRC522 instance
MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN); 

// Create display instance
SSD1306 display(0x3c, SDA_PIN, SCL_PIN);

// Web server
WebServer web_server(80);

// Global variables for wifi management
boolean wifi_connected = false;
long wifi_disconnected_time = 0;


void setup() {
  delay(100);
	Serial.begin(115200);

  wifi_setup();
  display_setup();
  buzzer_setup();
  rfid_setup();
  web_server_setup();
}

void loop() {
  
  // Check for WiFi
  if(WiFi.status() != WL_CONNECTED){
    // Wifi disconnected
    
    if(wifi_connected){
      // Acknowledge disconnection
      wifi_connected = false;
      wifi_disconnected_time = millis();
      Serial.println(F("[WIFI] disconnected"));
    }

    wifi_reset_if_timout();
    
    display_connecting();
  }
  else {
    // Wifi connected
    
    if(!wifi_connected){
      // Acknowledge connection
      wifi_connected = true;
      Serial.print(F("[WIFI] connected, IP: "));
      Serial.println(WiFi.localIP());
      display_connected();
      delay(2000);
      display_price();
    }

    // Check for cards
    if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      
      // Inform user that card is detected
      display_upload();
      buzzer_play_request_pending();

      // Read the card UID
      String card_UID = UID_as_string(mfrc522.uid.uidByte, UID_SIZE);
      Serial.print(F("[RFID] Card UID: "));
      Serial.println(card_UID);

      // Make the API call
      API_call(card_UID);
  
      // Stop reading the card
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();

      // Wait some more
      delay(DISPLAY_MESSAGE_LENGTH);
  
      // Return to showing the price
      display_price();
    }
  }

  invert_display_periodically();
  rfid_periodic_self_test();
  web_server.handleClient();
}
