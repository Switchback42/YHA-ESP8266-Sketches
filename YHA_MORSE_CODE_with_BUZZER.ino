//YHA_MORSE_CODE_with_BUZZER

int BUZZER_PIN = D6;                // one leg of buzzer to D6 and the other to ground
int ONE_TIME_UNIT = 500;            // default 500 milliseconds for one time unit
                                  
// Setup runs once
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(BUZZER_PIN, OUTPUT);      // Initialize the BUZZER_PIN as an output
  Serial.begin(115200);             // default 9600
}

// This is a function for a dot, which is 1 unit
void dot() {
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW
  digitalWrite(BUZZER_PIN, HIGH);  // Turn the buzzer ON by making the voltage HIGH
  delay(ONE_TIME_UNIT);            // Wait for 1 unit of time
}

// This is a function for a dash, which is 3 units
void dash() {
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW
  digitalWrite(BUZZER_PIN, HIGH);  // Turn the buzzer ON by making the voltage HIGH
  delay(3*ONE_TIME_UNIT);          // Wait for 3 units of time  
}
  
// This is a function for a space
void space(int ms) {
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  digitalWrite (BUZZER_PIN, LOW);  // Turn the buzzer OFF by making the voltage LOW
  delay(ms);                       // Delay for specified duration  
}

// This is a function for J = .---
void J(){
  dot();
  space(ONE_TIME_UNIT); // The space between parts of the same letter is 1 unit of time
  dash();
  space(ONE_TIME_UNIT);
  dash();
  space(ONE_TIME_UNIT);
  dash();  
}

// This is a function for I = ..
void I(){
  dot();
  space(ONE_TIME_UNIT); // The space between parts of the same letter is 1 unit of time
  dot();
}

// This is a function for L = .-..
void L(){
  dot();
  space(ONE_TIME_UNIT); // The space between parts of the same letter is 1 unit of time
  dash();
  space(ONE_TIME_UNIT);
  dot();
  space(ONE_TIME_UNIT);
  dot();
}

// This is a function for S = ...
void S(){
  dot();
  space(ONE_TIME_UNIT); // The space between parts of the same letter is 1 unit of time
  dot();
  space(ONE_TIME_UNIT);
  dot();
}

// This is a function for 0 = ---
void O(){
  dash();
  space(ONE_TIME_UNIT); // The space between parts of the same letter is 1 unit of time
  dash();
  space(ONE_TIME_UNIT);
  dash();
}

// the loop function runs over and over again forever
void loop() {
J();
space(3*ONE_TIME_UNIT); // Space between letters is 3 units of time
I();
space(3*ONE_TIME_UNIT);
L();
space(3*ONE_TIME_UNIT);
L();
space(7*ONE_TIME_UNIT); // Space between words is 7 units of time
}
