# Arduino LED Simulator – Qt Project

## Overview
This project is a Qt-based Arduino LED simulator that allows users to write Arduino code, build it, and simulate LED and button behavior visually.

The application provides:
- a code editor for Arduino sketches
- a **Build** button to compile the code
- a **Run** button to execute the simulation
- a visual Arduino circuit area
- debug and output consoles

The simulator is designed to demonstrate basic Arduino digital I/O operations such as turning LEDs on and off, blinking, controlling multiple outputs, and reading input from a button.

---

## Features
- Compile Arduino sketches
- Simulate LED output on digital pins
- Simulate button input
- Show compilation and runtime messages
- Visual representation of Arduino connections

---

## Arduino Commands Implemented

### 1. LED ON
Turns the LED connected to pin 13 on permanently.

```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
}
```

---

## 2. LED OFF
Turns LED on pin 13 OFF.

```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, LOW);
}
```

---

## 3. Blinking LED
LED blinks every 500 ms.

```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}
```

---

## 4. Multiple Blinking (Two LEDs)
Two LEDs blink alternately on pins 13 and 12.

```cpp
void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(500);

  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(500);
}
```

---

## 5. Blinking with Different Speed
LED blinks every 1 second.

```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
```

---

## 6. Input Detection (Button)
Reads the state of a button connected to pin 2.

```cpp
void setup() {
  pinMode(2, INPUT);
}

void loop() {
  int state = digitalRead(2);
}
```

---

## How the Simulator Works
1. User writes Arduino code in the editor.
2. Press Build to compile the sketch.
3. Press Run to start the simulation.
4. The simulator interprets:
   - pinMode()
   - digitalWrite()
   - digitalRead()
   - delay()
5. LEDs and buttons update visually in the simulation area.

---

## Technologies Used
- Qt (C++)
- QGraphicsView for simulation visualization
- Arduino CLI / External Compilation
- Custom Arduino Simulation Engine

---

## Pins Used
| Pin | Function |
|-----|----------|
| 13  | LED |
| 12  | Second LED |
| 2   | Button Input |

---

## Future Improvements
- Serial monitor simulation
- PWM (analogWrite)
- Multiple buttons
- Circuit designer (drag & drop)
- Real-time code execution
- Save/Load sketches
