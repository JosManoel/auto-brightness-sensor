// Enum for the modes
enum class Mode { AUTO, MANUAL };

// Create pins to control the Arduino
const int sensorPin = A0;  

const int modePin = 3;      
const int brightUpPin = 4;  
const int brightDownPin = 5; 

// Set initial values
int manualBrightness = 512;        
Mode mode = Mode::AUTO; 

void checkMode() {
  if (digitalRead(modePin) == LOW) {
    mode = (mode == Mode::AUTO) ? Mode::MANUAL : Mode::AUTO;
    delay(200);  // Debounce
  }
}

void adjustBrightnessUp() {
  if (digitalRead(brightUpPin) == LOW) {
    manualBrightness = min(manualBrightness + 100, 1023);
    delay(200);  // Debounce
  }
}

void adjustBrightnessDown() {
  if (digitalRead(brightDownPin) == LOW) {
    manualBrightness = max(manualBrightness - 100, 0);
    delay(200);  // Debounce
  }
}

void autoBrightnessControl() {
  int sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);
}

void manualBrightnessControl() {
  adjustBrightnessUp();
  adjustBrightnessDown();

  Serial.println(manualBrightness);
}

void setup() {
  Serial.begin(9600);

  // Setup pins
  pinMode(modePin, INPUT_PULLUP);
  pinMode(brightUpPin, INPUT_PULLUP);
  pinMode(brightDownPin, INPUT_PULLUP);
}

void loop() {
  checkMode();

  if (mode == Mode::AUTO) {
    autoBrightnessControl();
  } else {
    manualBrightnessControl();
  }

  delay(500);
}