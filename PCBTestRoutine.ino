/*******************************************
 * PCB Test Routine for Electronic Harmonium
 * Department of Computer Science and Engineering
 * MBM University, Jodhpur
 * 
 * This code tests all components on the
 * harmonium PCB after assembly
 *******************************************/

#include <Tone.h>

// Define pins to test
const int NUM_KEYS = 12;
int keyPins[NUM_KEYS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A0};

// Speaker pin
const int speakerPin = A5;

// LED indicators
const int octaveUpLedPin = A1;
const int octaveDownLedPin = A2;

// Control buttons
const int octaveUpPin = A3;
const int octaveDownPin = A4;

// Analog inputs
const int volumePotPin = A6;
const int scaleSelectPin = A7;

// Test tones
float testFrequencies[] = {
  261.63, 329.63, 392.00, 523.25
};

// Tone object
Tone tonePlayer;

// Test state
int testState = 0;
unsigned long lastStateChangeTime = 0;
const long testDuration = 1000; // 1 second per test

void setup() {
  Serial.begin(9600);
  Serial.println("Electronic Harmonium PCB Test Routine");
  Serial.println("Testing all components in sequence...");
  
  // Initialize all pins
  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }
  
  pinMode(octaveUpLedPin, OUTPUT);
  pinMode(octaveDownLedPin, OUTPUT);
  pinMode(octaveUpPin, INPUT_PULLUP);
  pinMode(octaveDownPin, INPUT_PULLUP);
  
  tonePlayer.begin(speakerPin);
  
  // Start the test sequence
  lastStateChangeTime = millis();
}

void loop() {
  // Update test state every testDuration milliseconds
  if (millis() - lastStateChangeTime > testDuration) {
    testState++;
    if (testState > 5) {
      testState = 0;  // Loop tests
    }
    lastStateChangeTime = millis();
    
    // Print current test
    Serial.print("Test #");
    Serial.print(testState);
    Serial.print(": ");
    
    switch (testState) {
      case 0:
        Serial.println("LEDs");
        break;
      case 1:
        Serial.println("Speaker");
        break;
      case 2:
        Serial.println("Touch Sensors");
        break;
      case 3:
        Serial.println("Buttons");
        break;
      case 4:
        Serial.println("Volume Potentiometer");
        break;
      case 5:
        Serial.println("Scale Selector");
        break;
    }
  }
  
  // Run the appropriate test based on current state
  switch (testState) {
    case 0:
      testLEDs();
      break;
    case 1:
      testSpeaker();
      break;
    case 2:
      testTouchSensors();
      break;
    case 3:
      testButtons();
      break;
    case 4:
      testVolumePot();
      break;
    case 5:
      testScaleSelector();
      break;
  }
}

void testLEDs() {
  // Blink pattern for LEDs
  long elapsed = millis() - lastStateChangeTime;
  
  if (elapsed < testDuration / 3) {
    digitalWrite(octaveUpLedPin, HIGH);
    digitalWrite(octaveDownLedPin, LOW);
  }
  else if (elapsed < 2 * testDuration / 3) {
    digitalWrite(octaveUpLedPin, LOW);
    digitalWrite(octaveDownLedPin, HIGH);
  }
  else {
    digitalWrite(octaveUpLedPin, HIGH);
    digitalWrite(octaveDownLedPin, HIGH);
  }
}

void testSpeaker() {
  // Play different test tones
  long elapsed = millis() - lastStateChangeTime;
  int toneIndex = (elapsed * 4) / testDuration;
  
  if (toneIndex >= 4) {
    toneIndex = 3;
  }
  
  tonePlayer.play(testFrequencies[toneIndex]);
}

void testTouchSensors() {
  // Check all touch sensors
  for (int i = 0; i < NUM_KEYS; i++) {
    if (digitalRead(keyPins[i]) == LOW) {
      Serial.print("Key ");
      Serial.print(i);
      Serial.println(" detected");
      
      // Visual feedback
      digitalWrite(octaveUpLedPin, (i % 2 == 0) ? HIGH : LOW);
      digitalWrite(octaveDownLedPin, (i % 2 == 0) ? LOW : HIGH);
      
      // Audio feedback
      tonePlayer.play(testFrequencies[i % 4]);
      return;
    }
  }
  
  // If no keys detected
  tonePlayer.stop();
}

void testButtons() {
  // Test octave buttons
  if (digitalRead(octaveUpPin) == LOW) {
    digitalWrite(octaveUpLedPin, HIGH);
    tonePlayer.play(testFrequencies[3]);  // Higher tone
    Serial.println("Octave Up button pressed");
  }
  else if (digitalRead(octaveDownPin) == LOW) {
    digitalWrite(octaveDownLedPin, HIGH);
    tonePlayer.play(testFrequencies[0]);  // Lower tone
    Serial.println("Octave Down button pressed");
  }
  else {
    digitalWrite(octaveUpLedPin, LOW);
    digitalWrite(octaveDownLedPin, LOW);
    tonePlayer.stop();
  }
}

void testVolumePot() {
  // Read and display volume pot value
  int value = analogRead(volumePotPin);
  int mappedValue = map(value, 0, 1023, 0, 10);
  
  Serial.print("Volume: ");
  Serial.println(mappedValue);
  
  // Visual feedback
  if (millis() % 200 < 100) {  // Flash every 200ms
    digitalWrite(octaveUpLedPin, HIGH);
    digitalWrite(octaveDownLedPin, HIGH);
  }
  else {
    digitalWrite(octaveUpLedPin, LOW);
    digitalWrite(octaveDownLedPin, LOW);
  }
  
  // Audio feedback - tone with changing volume
  tonePlayer.play(testFrequencies[2]);
}

void testScaleSelector() {
  // Read and display scale selector value
  int value = analogRead(scaleSelectPin);
  int scaleType;
  
  if (value < 341) {
    scaleType = 0;
    Serial.println("Scale: Standard");
  } 
  else if (value < 682) {
    scaleType = 1;
    Serial.println("Scale: Harmonic");
  } 
  else {
    scaleType = 2;
    Serial.println("Scale: Minor");
  }
  
  // Visual feedback
  digitalWrite(octaveUpLedPin, scaleType == 0 || scaleType == 2);
  digitalWrite(octaveDownLedPin, scaleType == 1 || scaleType == 2);
  
  // Audio feedback - different tone for each scale
  tonePlayer.play(testFrequencies[scaleType % 4]);
}