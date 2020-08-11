void buzzer_setup(){
  
  pinMode(BUZZER_PIN,OUTPUT);

  // Setting up PWM
  ledcSetup(BUZZER_CHANNEL, 2000, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  ledcWrite(BUZZER_CHANNEL, 0);
}

void buzzer_play_success(){

  tone_custom(900,100);
  tone_custom(1100,100);
  tone_custom(1300,100);
  tone_custom(1500,100);
  delay(100);
  tone_custom(1300,100);
  tone_custom(1500,500);


}

void buzzer_play_request_pending(){
  tone_custom(1000,100);
  delay(200);
}

void buzzer_play_error(){

  tone_custom(300,100);
  delay(100);
  tone_custom(300,500);
  
}


void tone_custom(int freq, int duration){
  ledcWriteTone(BUZZER_CHANNEL, freq);
  ledcWrite(BUZZER_CHANNEL, 125);
  delay(duration);
  ledcWrite(BUZZER_CHANNEL, 0);
}
