EClet_STM32 by Riddle&Code 
=====

... is the combination of Atmel's ATECC608A crypto accelerator, Atmel's ATAES132A secure EEPROM, ST-Micros STM32L475 IOT Discovery board, a rewrite of Trezor's crypto libraries for Arduino and an adoption of Atmel's crypto-auth library for ARM Cortex based Arduino boards.

Hardware
---

The ATECC608A and the ATAES132A secure element can turn any Arduino or IoT Board into a full fledged Hardware Wallet. The combination also addresses all challenges of machine identity and data integrity. This way it becomes easy to turn IoT devices in market places for Sensor data.

The secure element is especially built for ST-Micro's B-L475E-IOT01A-STM32L4 Discovery kit IoT node, the reference board for Amazon's AWT for IOT. It is designed to help promptly connect IoT devices to Cloud services power-efficiently and cost-effectively, ST’s new IoT development kit adds modules for Bluetooth® Low Energy (BLE), sub-GHz RF, and Wi-Fi, with a dynamic NFC-tag IC with printed antenna to a high-performance, ultra-low power STM32L4 microcontroller all on the same board.

Software
---

Essentially there are two distinctive libraries. 

One is the Trezor-Crypto a collection of crypto libs and algorithms of importance for any kind of blockchain and public ledger settlement and payment system. In the specific case also used to give uncompromisable identities to hardware devices and to protect the integrity of any kind of data.

One is the Crypto-Auth library a collection of drivers for the hardware crypto accelerator chips produced by Atmel. On these temper proof ICs important crypto algorithms like hashing, true random number generation, elliptic curves, Diffie-Hellman key exchanges, key storage, et al. are operated strictly off the bus and hardware accelerated.

Installation
---

Both libraries implement the code to run within  Arduino's development environment. Therefore a first step requires downloading the IDE from Arduino's website.

```1.  https://www.arduino.cc/en/Main/Software```

Take care to download the Arduino IDE and not the Web Editor.

Following the installation of the IDE enable the environment to work with STM32 based micro-controllers like the Nucleo or Discovery boards. 

Enable Arduino's Board Manager to work with the IoT Discovery board.

```
2. https://github.com/RiddleAndCode/Arduino_Core_STM32
```
After the successful installing  Arduino IDE and Arduino Core for STM32  on your machine, configure the environment to select the IoT board as the development target of choice. 

Open the Board submenu from the Tools menu and select the Discovery series of boards.

<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-18%20at%2011.16.31.png"/>
     
Select the board part number.
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-18%20at%2011.21.32.png"/>
     
Select the serial interface.
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-18%20at%2011.22.59.png"/>
     
Select USB interface.
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-18%20at%2011.23.10.png"/>
     
Select uplink method.
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-18%20at%2011.23.37.png"/>
     
Select optimize method.
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-18%20at%2011.23.43.png"/>
     
Select the port the Arduino board is connected to.
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-18%20at%2011.28.02.png"/>
     
 

Connect Secure Element to STM32-Discovery-IoT Board
---

The Secure Element was built witha dual purpose in mind. To extend all Arduino UNO R3 pin compliant Amker boards and all Raspberry Pi pin compliant boards. Accordingly one has to take care to use the right one.

To avoid mixing the pins up a basic distinction was made. Female pins are connectors to Raspbery Pis and male connectors are pins to be connected Uno R3 compliant devices. THe STM32L475 belongs to the Arduino group of boards. The pin connection scheme is as follows:
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/secure_element_2_stm32_iot_discovery.png"/>
     
 Check that your conected board looks like this:
     
<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/IMG_0423.jpg"/>

