void wifi_setup(){
  Serial.println(F("[WIFI] Initialization"));
  WiFi.mode(WIFI_STA);
  WiFi.enableSTA(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void wifi_reset_if_timout(){
  // Force reconnect if fail
  if(millis() - wifi_disconnected_time > WIFI_CONNECTION_TIMEOUT){
    wifi_disconnected_time = millis();
    Serial.println(F("[WIFI] connection timeout"));
    WiFi.disconnect(true);
    wifi_setup();
  }
}
