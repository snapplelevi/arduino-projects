// Program for sensing motion in a room and playing a rewarding sound effect
#include "pitches.h"

const int increase_freq_pin = 7;
const int decrease_freq_pin = 8;
const int bp = 12; // bp = buzzer pin
const int motion_pin = 3;

int increase_state, decrease_state, motion_state;
int pitch = 0; // used to alter tuning of melody when needed
int doorbell_played = false;
unsigned long int time_start = 0;


// Cowboy bebop - 140 bpm --> zeroes represent rests
int melody[] = { NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_FS5, 
                 NOTE_G5, NOTE_GS5, 0, 0, 0, 0, 0, 
                 
                 NOTE_C5, NOTE_G5, NOTE_C5, NOTE_FS5, NOTE_C5, NOTE_DS5, NOTE_C5, NOTE_AS4, NOTE_C5};
int song_length = sizeof(melody) / sizeof(int);

// based on 140 bpm, with each beat being a quarter note
// the decimal values represent a fraction of one beat (quarter note)

float note_length[] = { .25, .50, .25, .50, .25, .50, .25, .50, .50, .50, 1.0, 1.0, 1.0, 1.0, 1.0, 
                         .25, .50, .25, .50, .25, .50, .25, 1.0, 2.5};

// Plays a song based on the melody/note lengths provided in the global arrays
// could add in an optional pitch shift adds a certain shift to the predefined notes in the song
void play_doorbell(int song_length, int bpm, int pitch_shift){
  for(int i = 0; i < song_length; i++){
     int note = melody[i];
     float ms_per_beat = (1000.0 / ((float)(bpm) / 60.0));
     float duration = note_length[i] * ms_per_beat;
     if(duration == 0) noTone(bp);
     else              tone(bp, note, duration);
     delay((duration == 0) ? ms_per_beat : duration);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(increase_freq_pin, INPUT);
  pinMode(decrease_freq_pin, INPUT);
  pinMode(motion_pin, INPUT);
  pinMode(bp, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  increase_state = digitalRead(increase_freq_pin);
  decrease_state = digitalRead(decrease_freq_pin);
  motion_state = digitalRead(motion_pin);
  Serial.print("Millis  - time start:");
  Serial.println(millis() - time_start);
  if(doorbell_played && millis() - time_start >= 10000){
    doorbell_played = 0; 
    Serial.println("doorbell played reset");
  }
  if(increase_state == HIGH){
    pitch++;
  }

  if(decrease_state == HIGH){
    pitch--;
  }
  if(motion_state == HIGH){
      if(!doorbell_played){
         play_doorbell(song_length, 140, 0);
         doorbell_played = 1;
      }
      time_start = millis(); 
      Serial.println("MOTION DETECTED");
  } 
  delay(150);
}
