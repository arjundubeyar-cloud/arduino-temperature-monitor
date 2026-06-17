/*
  Smart Temperature Monitor
  --------------------------
  Reads ambient temperature using an LM35 sensor and triggers an
  LED/buzzer alert when the temperature crosses a defined threshold.

  Hardware:
    - Arduino UNO
    - LM35 Temperature Sensor (analog output, 10mV per degree Celsius)
    - Green LED (normal status indicator) -> pin 8
    - Red LED (alert indicator)           -> pin 9
    - Buzzer (alert sound)                -> pin 10

  Wiring:
    LM35 VCC  -> Arduino 5V
    LM35 GND  -> Arduino GND
    LM35 OUT  -> Arduino A0
    Green LED anode (via 220ohm resistor) -> pin 8, cathode -> GND
    Red LED anode (via 220ohm resistor)   -> pin 9, cathode -> GND
    Buzzer +  -> pin 10, Buzzer - -> GND
*/

#define LM35_PIN A0      // Temperature sensor analog input
#define GREEN_LED 8      // Normal status LED
#define RED_LED 9        // Alert LED
#define BUZZER 10        // Alert buzzer
#define THRESHOLD 30.0   // Temperature threshold in Celsius

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);     // For monitoring readings on PC
}

void loop() {
  int sensorValue = analogRead(LM35_PIN);

  // Convert ADC reading (0-1023) to voltage (0-5V), then to Celsius
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = voltage * 100.0;   // LM35: 10mV per degree Celsius

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  if (temperatureC > THRESHOLD) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);
  }

  delay(1000);  // Read every 1 second
}
