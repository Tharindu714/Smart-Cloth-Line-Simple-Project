
# ☔ Smart Cloth Line Control System

> An Arduino-driven retractable clothesline system that protects clothes from rain automatically.

---

## 📖 Description

This project monitors a **water sensor** to detect raindrops.

* When rain is detected, the system activates a **motor** for **2 seconds** to retract the clothesline under a protective roof.
* Once the sensor is dry (rain stops), the motor runs again for **2 seconds** to extend the line back outside.

---

## 📂 Project Files

```
Smart_Drayer_Project/
├── Smart_Drayer.ino  # Arduino sketch for rain detection and motor control
└── README.md         # This documentation file
```

---

## ⚙️ Hardware Setup

* **Arduino UNO** (or compatible)
* **Water Sensor Module**
* **DC Motor** + Driver (e.g., L298N)
* **Power supply** (matching motor requirements)
* **Clothesline mechanism** with retractable pulley

---

## 🚀 Installation & Usage

1. **Open** `Smart_Drayer.ino` in the Arduino IDE.
2. **Connect** the water sensor to an analog pin and the motor driver to digital pins.
3. **Select** your board & port under **Tools**.
4. **Upload** the sketch.
5. **Test** by simulating raindrops on the sensor; observe retraction and extension.

---

## 📷 Circuit Diagram

> *Insert your wiring schematic here*

![SmartDrayer_img](https://github.com/user-attachments/assets/af0c44f5-1621-49f0-b2ed-3b70927d5e63)

---

## 🔧 Configuration

Adjust these `#define` settings at the top of `Smart_Drayer.ino`:

```cpp
#define SENSOR_PIN A0         // Water sensor analog input
#define MOTOR_PIN1 9          // Motor driver IN1
#define MOTOR_PIN2 10         // Motor driver IN2
#define RETRACT_DURATION 2000 // Retract time in milliseconds
#define EXTEND_DURATION 2000  // Extend time in milliseconds
#define THRESHOLD 500         // Sensor threshold for rain detection
```

Modify the `THRESHOLD` value to calibrate sensitivity, and motor pins/times as needed.

---

## 🛠️ Operation Flow

1. **Monitor** sensor analog value continuously.
2. **If** value > `THRESHOLD` (rain detected):

   * Activate motor to retract for `RETRACT_DURATION`
3. **Else if** value ≤ `THRESHOLD` (dry):

   * Activate motor to extend for `EXTEND_DURATION`
4. **Loop** indefinitely.

---

## 📜 License

MIT © 2025 Tharindu Chanaka

---

> Automating laundry protection with ☔️ and 🤖 by \Tharindu Chanaka
