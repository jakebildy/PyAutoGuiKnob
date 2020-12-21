
#include <ErriezRotaryFullStep.h>

// Connect rotary pins to the DIGITAL pins of the Arduino board with interrupt
// support:
//
// +-----------------------------------+----------------------------+
// |              Board                |    DIGITAL interrupt pins  |
// +-----------------------------------+----------------------------+
// | Uno, Nano, Mini, other 328-based  |  2, 3                      |
// | Mega, Mega2560, MegaADK           |  2, 3, 18, 19, 20, 21      |
// | Micro, Leonardo, other 32u4-based |  0, 1, 2, 3, 7             |
// | WeMos D1 R2 & mini (ESP8266)      |  12 = D6; 13 = D7; 14 = D5 |
// +-----------------------------------+----------------------------+
//
#define ROTARY_PIN1         12
#define ROTARY_PIN2         13

// Initialize full step rotary encoder with internal pull-up pins enabled
// and default sensitivity=100
RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2);

// Or initialize full step rotary encoder with internal pull-up pins disabled
// and default sensitivity=100
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, false);

// Or initialize full step rotary encoder with internal pull-up pins enabled and
// sensitivity value 1..255
// A higher value is more sensitive
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, true, 200);

// Global variables
int count = 0;
int countLast = 0;

// Forward declaration
void rotaryInterrupt();

void setup()
{
  // Initialize Serial port
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  // Initialize pin change interrupt on both rotary encoder pins
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), rotaryInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), rotaryInterrupt, CHANGE);

  // Change sensitivity
  rotary.setSensitivity(125);

  pinMode(15, INPUT);
 
}

bool hasButtonPressed = false;

void loop()
{
  // Wait for interrupt
  
  if (digitalRead(15) == LOW) {
    
    if (hasButtonPressed == false) {
      Serial.println("Pressed");
    }
    hasButtonPressed = true;
  }
  else {
    hasButtonPressed = false;
  }
}

void rotaryInterrupt()
{
  int rotaryState;

  // Read rotary state (Counter clockwise) -2, -1, 0, 1, 2 (Clockwise)
  rotaryState = rotary.read();

  // Count up or down by using rotary speed
  if (rotaryState == 0) {
    // No change
    return;
  } else if (abs(rotaryState) >= 2) {
    count += rotaryState * 2;
  } else {
    count += rotaryState;
  }



  // Print count value when count value changed
  if (countLast != count) {
    countLast = count;
    Serial.println(count);
  }
}
