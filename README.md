Power Monitoring and Protection System Using LPC2129

An embedded-systems project developed using the LPC2129 ARM7 microcontroller. The system monitors voltage, calculates current and power, and provides protection alerts when the voltage exceeds the predefined limits. It uses the MCP3204 ADC for analog-to-digital conversion, a 16×2 LCD for displaying readings, an I2C EEPROM for data storage, and a GSM module for SMS notifications. SPI, I2C, and UART communication protocols are integrated into the system.

Table of Contents

- Overview
- Objectives
- Hardware Components
- Software and Tools
- System Block Diagram
- Software Architecture
- Working Principle
- Peripheral Interfacing
- Learning Outcomes
- Important Implementation Notes

Overview

This project demonstrates an embedded power monitoring and protection system using the LPC2129 ARM7 microcontroller.

The MCP3204 ADC reads the analog input signal and communicates with the LPC2129 through SPI. The microcontroller processes the digital data and calculates the corresponding current and power values.

The voltage, current, and power readings are displayed on a 16×2 LCD. The user can enter minimum and maximum voltage limits using a keypad.

The measured readings are stored in an external EEPROM through the I2C communication protocol. A push button is provided to retrieve and display the previously stored readings.

If the measured voltage exceeds the maximum limit or falls below the minimum limit, the system activates a buzzer and displays an alert message on the LCD.

The GSM module communicates with the LPC2129 through UART0 and sends SMS notifications to the configured mobile number.

Objectives

- Develop a power monitoring system using the LPC2129 ARM7 microcontroller.
- Interface the MCP3204 ADC using the SPI communication protocol.
- Monitor analog voltage input.
- Calculate current and power values using the programmed formulas.
- Display voltage, current, and power readings on a 16×2 LCD.
- Set minimum and maximum voltage limits using a keypad.
- Store measured readings in an external EEPROM using I2C.
- Retrieve previously stored readings using a push button.
- Generate buzzer alerts for abnormal voltage conditions.
- Send SMS notifications using a GSM module through UART0.
- Integrate SPI, I2C, and UART communication protocols in one embedded application.

Hardware Components

- LPC2129 ARM7 Microcontroller
- MCP3204 12-bit ADC
- 16×2 LCD Display
- Matrix Keypad
- I2C EEPROM
- GSM Module
- Buzzer
- Push Button / Switch
- Regulated Power Supply
- Connecting Wires and Supporting Components

Software and Tools

- Embedded C
- Keil µVision IDE
- LPC2129 Device Header Files
- ARM7 Microcontroller Development Board
- SPI Communication
- I2C Communication
- UART Serial Communication

System Block Diagram

The system consists of the following functional blocks:

/home/v25ce5p4/Downloads/Untitled.png

Software Architecture

1. Main Application — "main.c"

Responsible for:

- Initializing UART0, SPI0, I2C, and LCD.
- Configuring GPIO pins.
- Reading minimum and maximum voltage limits from the keypad.
- Reading ADC values from the MCP3204.
- Calculating voltage, current, and power values.
- Displaying readings on the LCD.
- Writing measured values into EEPROM.
- Comparing voltage with predefined limits.
- Activating the buzzer during abnormal voltage conditions.
- Calling the appropriate GSM SMS alert function.
- Reading stored values from EEPROM when the switch is pressed.

2. SPI Communication Module

Responsible for communication between the LPC2129 and MCP3204 ADC.

Functions:

- "Init_SPI0()"
- "Read_ADC_MCP3204()"

The SPI interface transfers ADC conversion data from the MCP3204 to the microcontroller.

3. ADC Module — MCP3204

Responsible for:

- Reading analog input signals.
- Converting analog signals into digital values.
- Providing 12-bit digital conversion results.
- Sending conversion data to the LPC2129 through SPI.

The current application reads ADC channel 0.

4. I2C Communication Module

Responsible for communication between the LPC2129 and external EEPROM.

Functions:

- "init_i2c()"
- "i2c_eeprom_write()"
- "i2c_eeprom_read()"

5. EEPROM Module

Responsible for:

- Storing voltage readings.
- Storing calculated current values.
- Storing calculated power values.
- Retrieving previously stored readings.

EEPROM memory locations used:

- Address "0x00" – Voltage
- Address "0x01" – Current
- Address "0x02" – Power

The EEPROM device address used in the application is "0x50".

6. LCD Driver

Responsible for displaying:

- Project title.
- Minimum and maximum voltage input prompts.
- System ready status.
- Voltage readings.
- Current readings.
- Power readings.
- Voltage alert messages.
- Previously stored readings.

Functions:

- "LCD_INIT()"
- "LCD_CMD()"
- "LCD_DATA()"
- "LCD_STR()"

7. Keypad Module

Responsible for:

- Accepting minimum voltage limit.
- Accepting maximum voltage limit.
- Providing user input to the LPC2129.

Function:

- "keyscan()"

8. GSM Communication Module

Responsible for sending SMS notifications when voltage exceeds the configured limits.

Functions:

- "UART0_Init()" – Initializes UART0 communication.
- "gsm_send()" – Transmits AT commands and message characters.
- "SMS_ALERT1()" – Sends a high-voltage alert.
- "SMS_ALERT2()" – Sends a low-voltage alert.

9. Buzzer and Switch Control

The buzzer provides an audible indication during abnormal voltage conditions.

The switch is used to retrieve stored voltage, current, and power readings from EEPROM.

Working Principle

1. The LPC2129 initializes SPI0, I2C, UART0, LCD, and GPIO peripherals.
2. The LCD displays the project title.
3. The user enters the minimum voltage limit using the keypad.
4. The user enters the maximum voltage limit using the keypad.
5. The system displays the system-ready message.
6. The MCP3204 ADC reads the analog input signal from channel 0.
7. The ADC converts the analog signal into digital data and transfers it to the LPC2129 through SPI.
8. The microcontroller calculates current and power values using the programmed formulas.
9. Voltage and current readings are displayed on the LCD.
10. The power value is displayed on the LCD.
11. Voltage, current, and power readings are stored in EEPROM through I2C communication.
12. The microcontroller compares the measured voltage with the entered minimum and maximum limits.
13. If the voltage exceeds the maximum limit:
    - The buzzer is activated.
    - The LCD displays "VOLT ALERT!".
    - The LCD displays "CHECK INPUT".
    - The "SMS_ALERT1()" function sends a high-voltage SMS notification.
14. If the voltage falls below the minimum limit:
    - The buzzer is activated.
    - The LCD displays "VOLT ALERT!".
    - The LCD displays "CHECK INPUT".
    - The "SMS_ALERT2()" function sends a low-voltage SMS notification.
15. When the push button is pressed, the microcontroller reads the stored values from EEPROM.
16. The retrieved voltage, current, and power values are displayed on the LCD.
17. The system continuously repeats the monitoring process.

Peripheral Interfacing

SPI0 Communication

SPI0 is used for communication between the LPC2129 and MCP3204 ADC.

- P0.4 – SCK0 (Serial Clock)
- P0.5 – MISO0 (Master In Slave Out)
- P0.6 – MOSI0 (Master Out Slave In)
- P0.7 – Chip Select (CS)

The MCP3204 is a 12-bit ADC with four analog input channels.

I2C Communication

I2C0 is used for communication between the LPC2129 and external EEPROM.

- P0.2 – SDA0 (Serial Data)
- P0.3 – SCL0 (Serial Clock)

The EEPROM is used to store and retrieve measured readings.

UART0 Communication

UART0 is used for serial communication between the LPC2129 and GSM module.

- P0.0 – TXD0
- P0.1 – RXD0
- Baud Rate – 9600 bps (as configured, assuming the intended peripheral clock)

The GSM module receives AT commands from the LPC2129 and sends SMS notifications through the cellular network.

LCD Interface

The 16×2 LCD is used to display voltage, current, power, and system alert messages.

Keypad Interface

The keypad is used to enter minimum and maximum voltage limits.

Buzzer Interface

The buzzer provides an audible alert when the measured voltage goes outside the predefined range.

Push Button Interface

The switch is used to retrieve previously stored readings from the external EEPROM.

Learning Outcomes

- LPC2129 ARM7 microcontroller programming.
- Embedded C programming using Keil µVision.
- SPI communication and ADC interfacing.
- MCP3204 12-bit ADC operation.
- I2C communication and EEPROM interfacing.
- UART0 serial communication.
- GSM module interfacing and AT commands.
- LCD interfacing.
- Keypad interfacing.
- GPIO programming.
- Buzzer and switch interfacing.
- Embedded system integration.
- Hardware and software debugging.

Important Implementation Notes

- The MCP3204 provides 12-bit ADC conversion.
- The current source code reads ADC channel 0.
- The current value is calculated using "current = voltage / 10.0".
- Power is calculated using "power = voltage * current".
- Current is not independently measured using a separate current sensor in the present implementation.
- EEPROM values are converted to "u8" before writing, so decimal precision is not retained.
- The GSM module is controlled through UART0 using AT commands.
- The current GSM sending function transmits commands but does not check modem responses.
- The actual peripheral clock, hardware pin connections, and GSM voltage-level requirements should be verified before hardware testing.
- The buzzer GPIO register configuration should be checked against the actual physical pin connection.

This project is an educational prototype. Proper sensing calibration, electrical isolation, and protection circuitry are necessary before use in real electrical installations.
