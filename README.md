# Smart Temperature Monitor (Arduino)

An Arduino-based embedded systems mini project that continuously reads ambient temperature using an LM35 sensor and triggers a visual/audible alert when the temperature crosses a defined threshold. Built as part of an Embedded Systems & IoT internship task to demonstrate the core sense-process-act workflow of embedded systems.

## Overview

The system uses an LM35 temperature sensor connected to an Arduino UNO. The microcontroller continuously reads the sensor's analog output, converts it into a temperature value in Celsius, and compares it against a fixed threshold (30°C by default).

- If temperature is **below the threshold** → a green LED stays ON (normal status).
- If temperature **exceeds the threshold** → a red LED and a buzzer turn ON (alert state), and the green LED turns OFF.

## Components Used

| Component | Purpose |
|---|---|
| Arduino UNO | Microcontroller — reads sensor, runs logic, controls outputs |
| LM35 Temperature Sensor | Measures ambient temperature (analog output, 10mV/°C) |
| Green LED | Indicates normal temperature status |
| Red LED | Indicates alert/threshold-crossed status |
| Buzzer | Audible alert when threshold is crossed |
| 2x 220Ω Resistors | Current-limiting resistors for the LEDs |

## Circuit Connections

| From | To |
|---|---|
| LM35 VCC | Arduino 5V |
| LM35 GND | Arduino GND |
| LM35 OUT | Arduino A0 |
| Green LED anode → 220Ω resistor | Arduino pin 8 |
| Green LED cathode | Arduino GND |
| Red LED anode → 220Ω resistor | Arduino pin 9 |
| Red LED cathode | Arduino GND |
| Buzzer + | Arduino pin 10 |
| Buzzer − | Arduino GND |

![Circuit Diagram](circuit-diagram.png)

## How It Works

1. The LM35 outputs a voltage linearly proportional to temperature (10mV per °C).
2. The Arduino's ADC reads this analog voltage on pin A0 and converts it to a digital value (0–1023).
3. The code converts this value into an actual voltage, then into a temperature in Celsius.
4. The temperature is compared against `THRESHOLD` (30.0°C by default).
5. Based on the comparison, the Arduino drives the green LED, red LED, and buzzer accordingly.
6. The current temperature is also printed to the Serial Monitor every second for live debugging.

## Code

See [`smart_temp_monitor.ino`](smart_temp_monitor.ino) for the full, commented source code.

```cpp
#define LM35_PIN A0      // Temperature sensor analog input
#define GREEN_LED 8      // Normal status LED
#define RED_LED 9        // Alert LED
#define BUZZER 10        // Alert buzzer
#define THRESHOLD 30.0   // Temperature threshold in Celsius

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(LM35_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = voltage * 100.0;

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

  delay(1000);
}
```

## How to Run

**Option 1 — Tinkercad Circuits (simulation, no hardware needed)**
1. Go to [Tinkercad Circuits](https://www.tinkercad.com/circuits) and create a new circuit.
2. Add an Arduino UNO, LM35 temperature sensor, 2 LEDs, 2 resistors, and a buzzer.
3. Wire the components as shown in the Circuit Connections table above.
4. Open the Code panel, switch to Text mode, and paste in `smart_temp_monitor.ino`.
5. Click Start Simulation and use the LM35's temperature slider to test both states.

**Option 2 — Real Hardware**
1. Wire the components on a breadboard exactly as described above.
2. Open `smart_temp_monitor.ino` in the Arduino IDE.
3. Select the correct board (Arduino UNO) and port, then upload.
4. Open the Serial Monitor (9600 baud) to view live temperature readings.

## Real-World Applications

- Server room / industrial equipment overheating alerts
- Smart thermostats for automated heating/cooling
- Cold chain monitoring for vaccines, medicines, and perishable food
- Greenhouse and agricultural temperature monitoring

## License

This project was built for educational/internship purposes and is free to use or modify.
