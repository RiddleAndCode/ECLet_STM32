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


