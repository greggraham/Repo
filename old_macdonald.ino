// Pin where the buzzer is connected
const int buzzer = 8;

// Notes for "Old MacDonald Had a Farm"
int melody[] = {
  // O-L-D  M-A-C  D-O-N-A-L-D
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_G4,
  // Had a farm, E-I-E-I-O
  NOTE_D4, NOTE_D4, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_G4,
  // And on that farm he had a cow, E-I-E-I-O
  NOTE_D4, NOTE_D4, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_G4,
  // With a moo moo here...
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_B3, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_G4
};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 2
};

// Frequencies for notes (add this at the top of your file)
#define NOTE_B3 247
#define NOTE_A3 220
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_G4 392

void setup() {
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);
    delay(noteDuration * 1.3); // pause between notes
    noTone(buzzer);
  }
}

void loop() {
  // Do nothing
}