# Asynchronous Stepper Motor Position Control
Controlling __4__ __stepper__ __motors__ with **1 Arduino Mega** by using **16 bit timers**

**1. Hardware**
- Arduino Mega
- Four Stepper Motor, Syringe pump
- 'DRV8711' Texas Instruments Motor Driver Module (Polulu)
- Support microstepping

**2. Important Notice**
- Assigned pin number of Arduino Mega is based on my configuration. User can change the pin assignment.
- _STEP, _DIR, _SS, _SLEEP, _STLFLT, _HOME, and _RESET are should be assigned.

**3. Class Declaration**
    
    ASMC(int MotorNumber, float MotorCurrent, unsigned int max_speed, unsigned int min_speed, int microstepping, float lead, bool newboard=false) 

- **Motor Current** should be checked by motor specification
- Based on **MotorNumber**, pre-assigned pins are chosen. Please refer to the ASMC.cpp
- Based on **max_speed** and **min_speed**, the library automatically calculates middle speed.
- **microstepping** is calculated as 2^microstepping. If you want to choose 8 microstepping, you can put 3.
- **lead** is the unit number for changing revolution to linear acutation.

**4. SPI Communication**

- Through SPI communication, Arduino Mega can set motor driver, DRV8711. The SPI communication is based on pre-set pins of Arduino Mega.
You can refer to the Arduino Website for SPI communication.
- Register_DRV8711.h file shows what you can program
- Important Notice: To avoid unexpected current flow at the beginning, when you write register in DRV8711, you should write 0 ENABLE register in CTRL area first.
After finishing all set-up of register in DRV8711, you can write 1 on ENABLE register.
By using this methodology, you can protect your circuit board and motor from unexpected current draw from power source.
Please refer to SPI_DRV8711.cpp.
