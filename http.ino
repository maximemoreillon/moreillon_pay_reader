void API_call(String card_UID){
  // Create a JSON payload
  StaticJsonDocument<200> outbound_JSON_message;

  outbound_JSON_message["card_uuid"] = card_UID;
  outbound_JSON_message["amount"] = TRANSACTION_AMOUNT;
  outbound_JSON_message["description"] = TRANSACTION_DESCRIPTION;

  char JSONmessageBuffer[200];
  serializeJson(outbound_JSON_message, JSONmessageBuffer, sizeof(JSONmessageBuffer));
  
  Serial.print(F("[HTTP] Outbound payload: "));
  serializeJson(outbound_JSON_message, Serial);

  // Sending the payload using HTTP POST request
  HTTPClient http;
  http.begin(API_URL);
  //http.setTimeout(3000); // Probably ms
  http.addHeader("Content-Type", "application/json");
  String auth_header = "Bearer " + String(API_TOKEN);
  http.addHeader("Authorization", auth_header);
  int httpCode = http.POST(JSONmessageBuffer);
  
  Serial.print(F("[HTTP] Response code:"));
  Serial.println(httpCode);
  
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.print(F("[HTTP] Inbound payload: "));
    Serial.println(payload);
    
    // Parsing payload
    StaticJsonDocument<200> inbound_JSON_message;
    deserializeJson(inbound_JSON_message, payload);
    
    if(httpCode == 200){
      // Success
      display_success(inbound_JSON_message["balance"]);
      buzzer_play_success();
    }
    else {
      // Response code was error
      display_error(inbound_JSON_message["status"]);
      buzzer_play_error();
    }
  }
  else {
    // response code was negative (unable to connect)
    display_upload_failed();
    buzzer_play_error();       
  }

  // Might want to do the following sooner
  // Close HTTP connection
  http.end();
}
