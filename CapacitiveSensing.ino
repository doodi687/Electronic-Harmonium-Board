/*******************************************
 * Capacitive Touch Sensing for Electronic Harmonium
 * Department of Computer Science and Engineering
 * MBM University, Jodhpur
 * 
 * This code demonstrates the capacitive touch
 * functionality needed for the harmonium keys
 *******************************************/

#include <CapacitiveSensor.h>

// Number of keys
const int NUM_KEYS = 12;

// Define send pin and receive pins for capacitive sensing
const int sendPin = 13;  // Common send pin
int receivePins[NUM_KEYS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A0};

// Create CapacitiveSensor objects
CapacitiveSensor* keys[NUM_KEYS];

// Threshold for touch detection
const long touchThreshold = 200;

// LED for visual feedback
const int ledPin = A1;

void setup() {
  Serial.begin(9600);
  Serial.println("Capacitive Touch Sensor Test - Electronic Harmonium");
  
  // Initialize CapacitiveSensor objects
  for (int i = 0; i < NUM_KEYS; i++) {
    keys[i] = new CapacitiveSensor(sendPin, receivePins[i]);
    keys[i]->set_CS_AutocaL_Millis(0xFFFFFFFF);  // Turn off autocalibration
  }
  
  // Initialize LED pin
  pinMode(ledPin, OUTPUT);
  
  delay(500);
}

void loop() {
  // Check each key
  for (int i = 0; i < NUM_KEYS; i++) {
    // Read capacitive value
    long sensorValue = keys[i]->capacitiveSensor(30);
    
    // If touched
    if (sensorValue > touchThreshold) {
      digitalWrite(ledPin, HIGH);
      Serial.print("Key ");
      Serial.print(i);
      Serial.print(" touched: ");
      Serial.println(sensorValue);
    }
  }
  
  // Turn off LED if no key is touched
  boolean anyKeyTouched = false;
  for (int i = 0; i < NUM_KEYS; i++) {
    if (keys[i]->capacitiveSensor(1) > touchThreshold) {
      anyKeyTouched = true;
      break;
    }
  }
  
  if (!anyKeyTouched) {
    digitalWrite(ledPin, LOW);
  }
  
  delay(10);  // Small delay for stability
}