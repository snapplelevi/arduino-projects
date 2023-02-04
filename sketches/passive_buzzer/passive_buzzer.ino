// Passive Buzzer test, seeing how functionality works
// Changes pitch of buzzer based on two switches w/ pull down resistors 
#include "pitches.h"
const int hail_the_chief = 3;
const int increase_freq_button = 7;
const int decrease_freq_button = 8;
const int buzzer_pin = 12;

int pitch = 300; // Pitch of the passive buzzer


void setup() {
  // put your setup code here, to run once:
  pinMode(increase_freq_button, INPUT);
  pinMode(decrease_freq_button, INPUT);
  pinMode(hail_the_chief, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  
  Serial.begin(9600);
}

#
void hail_to_the_chief(){
  tone(buzzer_pin, NOTE_DS5, 500);
  delay(500);
  tone(buzzer_pin, NOTE_F5, 375);
  delay(375);
  tone(buzzer_pin, NOTE_G5, 125);
  delay(125);
  tone(buzzer_pin, NOTE_GS5, 500);
  delay(500);
  tone(buzzer_pin, NOTE_G5, 375);
  delay(375);
  tone(buzzer_pin, NOTE_F5, 125);
  delay(125);
  tone(buzzer_pin, NOTE_DS5, 375);
  delay(375);
  tone(buzzer_pin, NOTE_F5, 125);
  delay(125);
  tone(buzzer_pin, NOTE_DS5, 375);
  delay(375);
  tone(buzzer_pin, NOTE_C5, 125);
  delay(125);
  tone(buzzer_pin, NOTE_AS4, 500);
  delay(500);
  tone(buzzer_pin, NOTE_GS4, 500);
  delay(500);
}
void loop() {
  int increase_state = digitalRead(increase_freq_button);
  int decrease_state = digitalRead(decrease_freq_button);
  int hail_state = digitalRead(hail_the_chief);

  if(hail_state){
    hail_to_the_chief();
  }
  /* 
  if(increase_state == HIGH){
    pitch += 2;
    
    //Serial.print("Increasing pitch: ");
    //Serial.println(pitch);
  }
  
  if(decrease_state == HIGH){
    pitch -= 2;
    //Serial.print("Decreasing Pitch: ");
    //Serial.println(pitch);
  }
  
  if(increase_state || decrease_state){
    tone(buzzer_pin, pitch);
  }
  else{
    noTone(buzzer_pin);
  } */
  delay(50);
}
