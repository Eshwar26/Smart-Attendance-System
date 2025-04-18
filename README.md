# Biometric Attendance System

A fingerprint-based attendance tracking system built on ESP microcontroller platform, featuring LCD display and real-time clock integration.

## Overview

This project implements a biometric attendance system using a fingerprint sensor to identify registered users and record their attendance with timestamps. The system supports two modes of operation:
- **Attendance Mode:** The default mode where users can mark their attendance by scanning their fingerprint
- **Enrollment Mode:** For registering new users into the system

## Hardware Requirements

- ESP8266/NodeMCU microcontroller board
- Fingerprint sensor (compatible with Adafruit Fingerprint library)
- I2C LCD display (16x2)
- DS3231 RTC (Real-Time Clock) module
- Jumper wires
- 5V power supply

## Pin Connections

| Component | Pin on ESP8266 |
|-----------|----------------|
| Fingerprint TX | D5 |
| Fingerprint RX | D6 |
| LCD and RTC SDA | D2 |
| LCD and RTC SCL | D1 |

## Software Dependencies

The following libraries are required:
- Adafruit_Fingerprint
- Wire
- LiquidCrystal_I2C
- SoftwareSerial
- RTClib

## Installation

1. Install Arduino IDE
2. Add ESP8266 boards to Arduino IDE
3. Install all required libraries through the Arduino Library Manager
4. Upload the code to your ESP8266 board

## Usage

### User Enrollment Process

1. Open Serial Monitor at 115200 baud rate
2. Send '1' to enter Enrollment Mode
3. Follow the prompts to enter:
   - User's name
   - Roll number
4. Place the same finger multiple times as instructed
5. The system will store the fingerprint template and user details

### Marking Attendance

1. Ensure the system is in Attendance Mode (displays "Attendance Mode" on LCD)
2. Place the enrolled finger on the fingerprint sensor
3. Upon successful recognition:
   - The LCD will display the user's name and confirmation
   - Attendance with timestamp will be logged to the Serial Monitor

### Return to Attendance Mode

1. Send '2' via Serial Monitor to return to Attendance Mode from Enrollment Mode

## Data Structure

The system stores user information in memory:
- Up to 127 users can be enrolled
- Each user record contains:
  - Name (up to 20 characters)
  - Roll number

## System Features

- Real-time attendance tracking with date and timestamp
- Clear user feedback via LCD display
- Simple enrollment process
- Reliable fingerprint matching

## Troubleshooting

- **RTC Failed:** Check the I2C connection to the RTC module
- **Sensor Failed:** Verify the fingerprint sensor connections and power
- **Finger not found:** The fingerprint could not be recognized; try again or ensure the user is enrolled

## Future Enhancements

The code includes a commented section for potential WiFi connectivity and Google Sheets integration. This could be implemented to:
- Store attendance records in a cloud spreadsheet
- Enable remote monitoring of attendance
- Provide attendance reports and analytics

