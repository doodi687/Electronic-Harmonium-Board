/*******************************************
 * Electronic Harmonium
 * Department of Computer Science and Engineering
 * MBM University, Jodhpur
 * 
 * This code implements a digital harmonium using
 * touch sensors and PWM sound generation
 *******************************************/

#include <Tone.h>

// Define pins for touch sensors (keys)
const int NUM_KEYS = 12;  // One octave
int keyPins[NUM_KEYS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A0};

// Define corresponding frequencies for Sa, Re, Ga, Ma, Pa, Dha, Ni (and sharps)
// C, C#, D, D#, E, F, F#, G, G#, A, A#, B
float notes[NUM_KEYS] = {
  261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 
  369.99, 392.00, 415.30, 440.00, 466.16, 493.88
};

// Speaker pin (PWM)
const int speakerPin = A5;

// LED indicators
const int octaveUpLedPin = A1;
const int octaveDownLedPin = A2;

// Octave control buttons
const int octaveUpPin = A3;
const int octaveDownPin = A4;

// Volume control
const int volumePotPin = A6;

// Scale selection switch
const int scaleSelectPin = A7;

// Variables
int currentOctave = 4;  // Start with middle octave
int volumeLevel = 5;    // Volume level (1-10)
int currentScale = 0;   // 0 = Standard, 1 = Harmonic, 2 = Minor

// Tone object
Tone tonePlayer;

// Debounce variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("Electronic Harmonium - MBM University");
  
  // Initialize key pins as inputs with pullup resistors
  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }
  
  // Initialize LED pins
  pinMode(octaveUpLedPin, OUTPUT);
  pinMode(octaveDownLedPin, OUTPUT);
  
  // Initialize octave control buttons
  pinMode(octaveUpPin, INPUT_PULLUP);
  pinMode(octaveDownPin, INPUT_PULLUP);
  
  // Initialize speaker pin
  tonePlayer.begin(speakerPin);
  
  // Update LED indicators
  updateLEDs();
  
  // Wait before starting
  delay(500);
}

void loop() {
  // Check octave controls
  checkOctaveControls();
  
  // Read volume potentiometer
  readVolume();
  
  // Read scale selection
  readScaleSelection();
  
  // Check for key presses and play notes
  checkKeys();
}

void checkOctaveControls() {
  // Check if octave up button is pressed
  if (digitalRead(octaveUpPin) == LOW) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (currentOctave < 8) {
        currentOctave++;
        Serial.print("Octave Up: ");
        Serial.println(currentOctave);
        updateLEDs();
        lastDebounceTime = millis();
      }
    }
  }
  
  // Check if octave down button is pressed
  if (digitalRead(octaveDownPin) == LOW) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (currentOctave > 1) {
        currentOctave--;
        Serial.print("Octave Down: ");
        Serial.println(currentOctave);
        updateLEDs();
        lastDebounceTime = millis();
      }
    }
  }
}

void updateLEDs() {
  // Update octave indicator LEDs
  if (currentOctave > 4) {
    digitalWrite(octaveUpLedPin, HIGH);
    digitalWrite(octaveDownLedPin, LOW);
  } 
  else if (currentOctave < 4) {
    digitalWrite(octaveUpLedPin, LOW);
    digitalWrite(octaveDownLedPin, HIGH);
  } 
  else {
    // Middle octave (4)
    digitalWrite(octaveUpLedPin, HIGH);
    digitalWrite(octaveDownLedPin, HIGH);
  }
}

void readVolume() {
  // Read analog value from potentiometer
  int rawValue = analogRead(volumePotPin);
  
  // Map to volume level (1-10)
  int newVolumeLevel = map(rawValue, 0, 1023, 1, 10);
  
  // Update only if changed
  if (newVolumeLevel != volumeLevel) {
    volumeLevel = newVolumeLevel;
    Serial.print("Volume: ");
    Serial.println(volumeLevel);
  }
}

void readScaleSelection() {
  // Read analog value from scale selection switch/potentiometer
  int rawValue = analogRead(scaleSelectPin);
  
  // Determine scale based on range
  int newScale;
  if (rawValue < 341) {
    newScale = 0;  // Standard scale
  } 
  else if (rawValue < 682) {
    newScale = 1;  // Harmonic scale
  } 
  else {
    newScale = 2;  // Minor scale
  }
  
  // Update only if changed
  if (newScale != currentScale) {
    currentScale = newScale;
    String scaleName;
    switch (currentScale) {
      case 0: 
        scaleName = "Standard"; 
        break;
      case 1: 
        scaleName = "Harmonic"; 
        break;
      case 2: 
        scaleName = "Minor"; 
        break;
    }
    Serial.print("Scale: ");
    Serial.println(scaleName);
  }
}

void checkKeys() {
  boolean anyKeyPressed = false;
  
  // Check each key
  for (int i = 0; i < NUM_KEYS; i++) {
    // If key is pressed (LOW for capacitive touch sensor or button)
    if (digitalRead(keyPins[i]) == LOW) {
      anyKeyPressed = true;
      
      // Calculate note frequency based on octave and scale
      float baseFreq = notes[i];
      
      // Adjust for octave
      float octaveMultiplier = pow(2, currentOctave - 4); // Relative to middle octave (4)
      baseFreq *= octaveMultiplier;
      
      // Adjust for scale if needed
      if (currentScale == 1) { // Harmonic scale
        if (i == 3 || i == 8) { // Adjust specific notes for harmonic scale
          baseFreq *= 1.04166;  // Raise by approximately a quarter step
        }
      }
      else if (currentScale == 2) { // Minor scale
        if (i == 2 || i == 6 || i == 9) { // Flatten 3rd, 6th, 7th for minor scale
          baseFreq *= 0.94387;  // Lower by a semitone
        }
      }
      
      // Play the note
      tonePlayer.play(baseFreq);
      
      // Adjust volume (if hardware supports it)
      // This is simplified; actual implementation would depend on hardware
      
      Serial.print("Key pressed: ");
      Serial.print(i);
      Serial.print(", Frequency: ");
      Serial.println(baseFreq);
      
      // Only play the first pressed key to avoid cacophony
      break;
    }
  }
  
  // If no keys are pressed, stop the tone
  if (!anyKeyPressed) {
    tonePlayer.stop();
  }
}