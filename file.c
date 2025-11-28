#include <Arduino.h>
#include <TM1637Display.h>

// --- WIRING CONFIGURATION ---
// Display Pins
#define CLK 2
#define DIO 3

// Ultrasonic Sensor Pins
#define TRIG 5
#define ECHO 6

// --- CONTAINER SETTINGS ---
// Measure your container's total depth in cm and change this number!
const float BOX_HEIGHT_CM = 20.0; 

// Initialize Display Library
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600); // Start serial communication

  // Setup Sensor Pins
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Setup Display Intensity (Brightness: 0-7)
  display.setBrightness(5);
  
  // Test pattern: Show "8888" to prove it's working
  uint8_t allOn[] = { 0xff, 0xff, 0xff, 0xff };
  display.setSegments(allOn);
  delay(1000); // Keep it on for 1 second
}

float getDistance() {
  // Send the sound wave
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Listen for the echo
  long duration = pulseIn(ECHO, HIGH);
  
  // If no echo received (0), return a "safe" far distance
  if (duration == 0) return 999.0;
  
  // Calculate distance in centimeters
  return duration * 0.034 / 2;
}

void loop() {
  // 1. Measure Distance
  float currentDistance = getDistance();
  
  // 2. Filter Bad Readings
  // If reading is crazy high (>100cm) or zero, ignore it
  if (currentDistance > 100 || currentDistance <= 0) {
     return; 
  }

  // 3. Calculate Percentage
  // Formula: How much space is left vs. Total space
  float filledHeight = BOX_HEIGHT_CM - currentDistance;
  
  // Safety check: don't let it go below 0
  if (filledHeight < 0) filledHeight = 0;
  
  int percentage = (filledHeight / BOX_HEIGHT_CM) * 100;

  // Safety check: don't let it go above 100
  if (percentage > 100) percentage = 100;

  // 4. Show Results
  // Print to computer (Serial Monitor)
  Serial.print("Distance: ");
  Serial.print(currentDistance);
  Serial.print(" cm | Filled: ");
  Serial.print(percentage);
  Serial.println("%");

  // Print to Display Screen
  display.showNumberDec(percentage);
  
  // Wait 0.5 seconds before measuring again
  delay(500); 
}