# IoT-Based Automation System for Efficient Production of Vermicompost Manure

![vermicompost](https://img.shields.io/badge/IoT-Arduino-green)
![Thingspeak](https://img.shields.io/badge/Cloud-Thingspeak-blue)
![Status](https://img.shields.io/badge/Stage-Prototype%20Complete-brightgreen)

## Project Overview

This project introduces an **IoT-powered automation system** designed to optimize the production of **vermicompost manure**. Vermicompost is a nutrient-rich organic fertilizer created by the natural decomposition of organic waste using earthworms. Traditional composting methods require frequent human monitoring and manual intervention. This system solves these problems by automatically monitoring and maintaining ideal environmental conditions—such as **temperature, humidity, moisture level, and gas presence**—to improve compost quality and efficiency.

By leveraging IoT and cloud technologies, this solution provides **real-time data visualization**, **remote monitoring**, and **automated control** of compost conditions using sensors, actuators, and a Wi-Fi module.

---

## Key Objectives
- Automate the composting process using sensors and microcontrollers.
- Maintain ideal temperature and moisture levels with minimal human effort.
- Monitor the presence of hazardous gases during decomposition.
- Enable real-time data monitoring and alerting through cloud integration.
- Improve the quality and speed of vermicompost production.

---

## 🛠️ Hardware Components
| Component              | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| Arduino UNO            | Microcontroller board for processing sensor data and triggering actuators. |
| ESP32 Wi-Fi Module     | Connects the system to the internet for cloud data upload.                 |
| DHT11 Sensor           | Measures temperature and humidity.                                          |
| MQ2 Gas Sensor         | Detects gases like methane, smoke, and hydrogen during decomposition.      |
| Soil Moisture Sensor   | Measures moisture content in the compost mixture.                           |
| Water Level Sensor     | Monitors the water level for irrigation control.                            |
| Relay Module           | Controls water pump or motor based on sensor thresholds.                    |
| LCD Display            | Shows sensor readings and system status in real-time.                       |
| Power Supply Unit      | Converts 230V AC to 5V/12V DC for safe circuit operation.                   |

---

## Software & Tools
- **Arduino IDE** – For programming the Arduino and ESP32 in Embedded C.
- **ThingSpeak** – Cloud platform for data visualization and analytics.
- **Embedded C Programming** – Used to develop sensor control logic.
- **Serial Monitor/LCD** – For local output and debugging.

---

## Features
- **Temperature Monitoring** – Activates cooling mechanism if temperature exceeds threshold.
- **Moisture Monitoring** – Detects soil dryness to maintain ideal compost conditions.
- **Gas Detection** – Alerts if harmful gases are released during decomposition.
- **Wi-Fi Connectivity** – Sends data to ThingSpeak cloud in real-time.
- **Dashboard Visualization** – Displays real-time graphs of all sensor data.
- **Automated Control** – Turns on motor/sprayer based on environmental conditions.
- **LCD Feedback** – Displays status messages like “Gas Detected” or “Moisture Low.”

---

## Workflow

```mermaid
graph TD;
    Start[Power On] --> ReadSensors[Read Sensor Values]
    ReadSensors --> CheckThresholds{Values in Range?}
    CheckThresholds -- Yes --> SendCloud[Upload to ThingSpeak]
    CheckThresholds -- No --> ActivateRelay[Activate Relay for Water Spray]
    ActivateRelay --> MonitorAgain[Monitor Again]
    SendCloud --> MonitorAgain
