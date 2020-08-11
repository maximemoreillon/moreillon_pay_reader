void web_server_setup() {  
  web_server.on("/", handle_root);
  
  web_server.on("/reboot_form", handle_reboot_form);
  web_server.on("/reboot",HTTP_POST, handle_reboot);
  
  web_server.on("/update_form", handle_update_form);
  web_server.on("/update",HTTP_POST, handle_update, handle_update_upload);
  
  // need a handler for not found
  web_server.begin();
  Serial.println("[Web server] server started");
}

void handle_root() {
  String html = pre_main + root_main + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.sendHeader("Access-Control-Allow-Origin", "*");
  web_server.send(200, "text/html", html);
}

void handle_reboot_form() {
  String html = pre_main + reboot_form + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.sendHeader("Access-Control-Allow-Origin", "*");
  web_server.send(200, "text/html", html);
}

void handle_reboot() {
  String html = pre_main + "Rebooting..." + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.sendHeader("Access-Control-Allow-Origin", "*");
  web_server.send(200, "text/html", html);
  ESP.restart();
}

void handle_update_form(){
  String html = pre_main + update_form + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.sendHeader("Access-Control-Allow-Origin", "*");
  web_server.send(200, "text/html", html);
}

void handle_update(){
  String upload_status;
  if(Update.hasError()){
    upload_status = "Upload failed";
  }
  else {
    upload_status = "Upload success";
  }
  String html = pre_main + upload_status + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.sendHeader("Access-Control-Allow-Origin", "*");
  web_server.send(200, "text/html", html);
  ESP.restart();
  
}

void handle_update_upload() {
  HTTPUpload& upload = web_server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.setDebugOutput(true);
    Serial.printf("Update: %s\n", upload.filename.c_str());
    if (!Update.begin()) { //start with max available size
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { //true to set the size to the current progress
      Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
    Serial.setDebugOutput(false);
  }
}
