# Ultrasonic Alarm Project

## Basic Information
- **Institution:** UNCC
- **Course:** Embedded Systems
- **Author:** Nathan Culler
- **Project:** Lab 4 - Ultrasonic Alarm

## Project Description
This project demonstrates the use of an ultrasonic range finder to create an invisible tripwire that sounds an alarm when crossed. The MSP430 development board is used to control the ultrasonic sensor and a buzzer, generating an alert when an object is detected within a specified range.

## Materials Used
- **MSP-EXP430FR2355** - TI's MSP430 development board
- **Seeed Studio Grove Ultrasonic Distance Sensor** - Used to detect objects
- **Seeed Studio Grove Buzzer** - Emits an alarm when triggered
- **Seeed Studio Grove Base Booster Pack** - Provides additional connections
- **Grove connection cable**
- **USB micro cable**
- **Laptop (Windows preferable)**

## Skills Showcased
- Timer peripheral configuration
- Clock source selection for precise pulse generation
- Analog-to-Digital Conversion (ADC)
- GPIO manipulation
- Interrupt handling for ultrasonic sensor and buzzer control
- State machine implementation for tripwire logic

## How to Run
1. Connect the ultrasonic sensor and buzzer to the MSP430 via the Grove Base Booster Pack.
2. Configure the GPIO pins for controlling the ultrasonic sensor and buzzer.
3. Implement the ultrasonic sensor logic:
   - Emit an ultrasonic pulse and measure the echo time.
   - Calculate the distance using the speed of sound.
4. Implement tripwire logic:
   - Arm the system using a button press.
   - Continuously measure distance and compare with the initial armed state.
   - Trigger the buzzer if an object is detected within a threshold range.
5. Compile and flash the firmware onto the MSP430.

## Additional Information
More details about this project can be found in the **Lab 4 - Ultrasonic Alarm** PDF.

## Author
Nathan Culler

Developed as part of an Embedded Systems course at UNCC.
