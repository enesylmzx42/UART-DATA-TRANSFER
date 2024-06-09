## Data_Transfer_Using_UART

This project primarily demonstrates the implementation of the UART communication protocol using Arduino through a sample project.

## Sensors and Microcontrollers Used in the Project
- DALLAS18B20
- KY-003 HALL EFFECT SENSOR
- LoRa 400T30D
- SD CARD MODULE
- Arduino Mega 2560
- Arduino Uno

## Project Introduction
The project comprises both transmitter and receiver circuits, with all sensors and modules connected to the transmitter circuit. It involves temperature reading, speed calculation using the magnetic field, saving the read data to an SD card, and sending the data to a remote microcontroller.

### Reading Temperature
![temperature](https://github.com/0mustafa/Data_Transfer_Using_UART/assets/78226423/bbfcfec5-0db7-4fc0-bfbb-26b5d0fc4d0b)

The `getTemperatures.h` library is created for temperature reading using the DALLAS18B20 module. The temperature reading process is executed by calling the `getTemps()` function in the main project file's loop section. Data flow between the module and Arduino is facilitated by UART.

### Calculating Speed Using Magnetic Field
![speed](https://github.com/0mustafa/Data_Transfer_Using_UART/assets/78226423/164e8748-e3ec-4018-831e-4dde74b4d6f1)

An interrupt is created by the module each time a magnetic field is detected, incrementing a counter value. At the end of each passing second, another interrupt is created, and the speed calculation is performed based on the counter value using a predefined algorithm. Data flow between the module and Arduino is facilitated by UART.

### Saving Data to SD Card Module
In the project's main file's SD card-related setup section, an attempt is made to establish a connection with the SD card. Once connected, the previously determined file name is searched within the card, and the number of occurrences of this file is determined. A new file name is set for the newly created data records. In the loop section, the `saveSDCard()` function is called to write incoming data to the card based on a predefined pattern. Data flow between the module and Arduino is facilitated by UART.

### Sending Data to Remote Microcontroller
The data sending process is performed using the LoRa 400T30D communication module with a specified address and channel. Sending operations are handled in the `Lora.h` library. The data to be sent is embedded in a struct using the `initValues()` function. The `sendLora()` function is called to initiate the sending process. On the receiving end, the same struct must be maintained to handle the received data.

![lora](https://github.com/0mustafa/Data_Transfer_Using_UART/assets/78226423/b0325217-9b29-42ab-be40-7dcb1b72070b)


