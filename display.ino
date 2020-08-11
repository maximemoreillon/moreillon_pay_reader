void display_setup() {
  // Initializes the SSD1306 display
  
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setBrightness(100);
  display.invertDisplay();
  
  delay(10);
  display_nothing();
}

void invert_display_periodically(){

  static long display_inversion_time = 0;
  static boolean display_inverted = false;
  
  // Inverts the display every once in a while to prevent screen burn in
  if(millis() - display_inversion_time > DISPLAY_INVERSION_PERIOD){
    display_inversion_time = millis();
    if(display_inverted){
      display_inverted = false;
      display.normalDisplay();
    }
    else {
      display_inverted = true;
      display.invertDisplay();
    }
  }
}

void display_nothing(){
  // Empty screen
  
  display.clear();
  display.display();
}


void display_connecting(){
  // Display the connecting animation
  
  long now = millis();
  static long last_change;
  const long change_period = 200;
  static int frame = 0;
  
  if(now-last_change > change_period){
    last_change = now;
    frame++;
    if(frame > 3){
      frame = 0;
    }
  }

  display.clear();
  if(frame == 0) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_1_2_3_off);
  else if(frame == 1) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_2_3_off);
  else if(frame == 2) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_3_off);
  else if(frame == 3) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_full);
  display.display();
  
}

void display_price(){
  display.clear();
  //display.setFont(Roboto_48);
  display.setFont(ArialMT_Plain_16);

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  //display.drawString(DISPLAY_WIDTH / 2, 0, TRANSACTION_AMOUNT);
  display.drawString(DISPLAY_WIDTH / 2, 0.5*DISPLAY_HEIGHT - 8, TRANSACTION_DESCRIPTION);
  display.display();
}


void display_connected(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, wifi_ok);
  display.display();
}

void display_upload(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, uploading_image);
  display.display();
}

void display_upload_failed(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, upload_fail);
  display.display();
}

void display_success(String remaining_balance){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/8, "OK");
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, remaining_balance);
  display.display();
}

void display_error(String transaction_status){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/8, "ERROR");
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, transaction_status);
  display.display();
}

void display_message(String message){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(DISPLAY_WIDTH/2, 0, message);
  display.display();
}
