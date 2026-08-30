const int ena = 2;   // Enable (active low)
const int dir = 3;   // Direction
const int pul = 4;   // Pulse


const int limitSwitch1 = 5;  // Left limit
const int limitSwitch2 = 6;  // Right limit

const unsigned long interval = 500;  // Pulse interval in microseconds


bool pulseState = LOW;
bool direction = HIGH;  // Start direction


unsigned long lastPulseTime = 0;


void setup() {
  pinMode(ena, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pul, OUTPUT);
  pinMode(limitSwitch1, INPUT);
  pinMode(limitSwitch2, INPUT);


  digitalWrite(ena, LOW);        // Enable motor
  digitalWrite(dir, direction);  // Set initial direction
  digitalWrite(pul, pulseState); // Initial step state
}


void loop() {
  // Check limit switches and reverse if needed
  if (digitalRead(limitSwitch1) == HIGH && direction == LOW) {
    direction = HIGH;
    digitalWrite(dir, direction);
    delay(50);  // Debounce
  } else if (digitalRead(limitSwitch2) == HIGH && direction == HIGH) {
    direction = LOW;
    digitalWrite(dir, direction);
    delay(50);  // Debounce
  }


  // Generate step pulses at steady rate
  if (micros() - lastPulseTime >= interval) {
    pulseState = !pulseState;
    digitalWrite(pul, pulseState);
    lastPulseTime = micros();
  }
}
 
