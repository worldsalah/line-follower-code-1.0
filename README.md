---

#  Line Follower Robot (5 IR Sensors + TB6612 + Arduino Nano)

This project is an Arduino-based **line follower robot** using **5 IR sensors** and the **TB6612FNG** motor driver.
The robot reads the sensor inputs and decides whether to go straight, turn softly, or turn sharply to stay on the line.

---

##  Features

* 5 digital IR sensors (no analog required)
* Direction memory (recovers when line is lost)
* Separate speeds for left/right motors
* Hard and soft turn control
* Works with Arduino Nano or Uno

---

##  Hardware Setup

### 🔹 Microcontroller

Arduino Nano (CH340 or FT232) or Arduino Uno

### 🔹 Motor Driver

TB6612FNG

### 🔹 Motors

2x N20 or DC gear motors (PWM controlled)

### 🔹 Sensors

5 reflective IR line sensors
Positions:

```
Far Left  |  Left  |  Middle  |  Right  |  Far Right
 S_FL       S_L       S_M        S_R       S_FR
```

### 🔹 Power

18650 battery / Li-ion / 7.4V depending on setup

---

##  Pin Connections

### 🔸 Motor Driver

```
ENA → D7    (PWM)
IN1 → D6
IN2 → D9

ENB → D12   (PWM)
IN3 → D10
IN4 → D11
```

### 🔸 Sensors

```
S_FL → D8  
S_L  → D2  
S_M  → D5  
S_R  → D4  
S_FR → D3
```

---

##  Code Behavior

* The robot reads all 5 sensors as digital values.
* Based on the pattern, it performs:

  * Forward
  * Soft turn (left/right)
  * Hard turn (left/right)
  * Recovery using last known direction

It uses this helper to check black/white:

```cpp
const bool BLACK_IS_LOW = false;
```

Change this if your sensor works opposite.

---

##  Movement Logic (Simplified)

| Sensors Detected   | Action       |
| ------------------ | ------------ |
| Left side active   | Hard Left    |
| Right side active  | Hard Right   |
| Slight left drift  | Soft Left    |
| Slight right drift | Soft Right   |
| Middle / balanced  | Forward      |
| All sensors off    | Use lastSeen |

It uses an enum to remember last direction:

```cpp
enum LastDir { STRAIGHT, LEFT, RIGHT };
```

---

##  Speed Configuration

These can be tuned based on motors and weight:

```cpp
int leftMotorSpeed  = 40;  
int rightMotorSpeed = 255;  
int turnSpeed       = 200;  
int hardTurnSpeed   = 255;
```

---

##  How to Use

1. Wire the components as above
2. Open Arduino IDE
3. Select the correct board & port
4. Upload the `.ino` file
5. Place the robot on a black/white track

Optional:

```cpp
Serial.begin(9600);
```

Add prints if you want debugging.

---

##  Future Improvements (Optional)

* PID support
* Encoder integration
* Automatic calibration
* Smoother turning
* OLED display or Bluetooth debug

---

##  License

Free to use, modify, and improve.
Credit appreciated but not required.

---
