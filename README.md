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
     
     
Next connect the board via USB to your host computer. The Discovery board offers two different USB connectors. One for programming the device via ST-Link, the other one for debugging via J-Link. The board also owns a direct programming J-Link connector foe Segger's J-Link programmers. It is meant for industrial production of Discovery board derived devices. Therefore we ignore it.

<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/stm32_iot_discovery_st-Link_connect.png"/>
     
Once the development environmen is set up and the hardware devices are connected to the host system restart the Arduino IDE

Test Environment and Security Hardware
---

To test the functionality of our setup start with a simple program create true random numbers. To be assured that our TRNG ( true number generator) is trustworthy the random command will be delegated to the secure element.

Open a new file inside the Arduino IDE. Load the Sketch rnc_crypto_random from the Arduino library or open a new file and save it under the name of your choice. Copy and replace the code you already fine in your new sketch window. Save the file again.

```
/* Load all relevant driver files to directly 
 *  communicate with the secure element 
 */

#include <atca_basic.h>
#include <atca_cfgs.h>
#include <atca_command.h>
#include <atca_compiler.h>
#include <atca_crypto_sw.h>
#include <atca_crypto_sw_sha2.h>
#include <atca_device.h>
#include <atca_devtypes.h>
#include <atca_hal.h>
#include <atca_helpers.h>
#include <atca_host.h>
#include <atca_iface.h>
#include <atca_start_config.h>
#include <atca_start_iface.h>
#include <atca_status.h>
#include <cryptoauthlib.h>
#include <hal_i2c_bitbang.h>
#include <i2c_bitbang_at88ck9000.h>
#include <sha2_routines.h>


/* Activate the secure element and configure
 *  it with default values
 */
   
ATCAIfaceCfg *gCfg = &cfg_ateccx08a_i2c_default;
byte buffer[ 64];
ATCA_STATUS status = ATCA_GEN_FAIL;


/* Set up a simply hex-string routine to make it easier
 * to get readable result printed to the serial monitor
 */

void hexify(const char *str, const uint8_t *hex, unsigned int len) {
  int i;

  Serial.write(str);
  for (i = 0; i < len; i++)  {
    static char tmp[4] = {};
    sprintf(tmp, "%02X", hex[i]);
    Serial.write(tmp);
  }
  Serial.write("\n\r");

}

void setup() {
  // Intit the serial inteface for ptinting out results and requesting inputs
  Serial.begin(9600);
  // Wait till Serial gets fulla activated
  while (!Serial) { ; }
  // Give the Discovery boared some time to get through the full bootloader process
  delay(2000);

  // Init the seure element and the AES EEPROM
  status = atcab_init( gCfg );
  status = atcab_release();

  // Request a random number created off-the-bus
  uint8_t random_number[32];
  
  status = atcab_init( gCfg );
  status = atcab_random( random_number );
  status = atcab_release();

  // Send results to serial interface
  hexify("Random Number 32-bytes:", (const uint8_t *) random_number, sizeof(random_number));

}

void loop() {
  // nothing to be done here

}

```
Before you run it you should make an important change to the Arduino IDE. 
Inside the Preferences menu activate "Show verbose output during:" 
compilation and output. Also activeate "All" for the "Compiler Warnings".
Save the changes made to the prefrences.


<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-19%20at%2020.28.05.png"/>
     

To run the code we first have to comopile it and then upload the resulting .bin file via ST-Link to the Discovery board. TZhe Arduino IDE handles this for us. To compile and upload the code the second button to the top-left part of the sketch wiindow has to be clicked. Compiling and uploading will then take a while. Cause we've opted for verbose output we can closely follow the process. During the compilation it is recommended to also activate the built-in Serial Monito of the Arduino IDE. To Accomplish this click the top-right button inside the sketch window. The moment the upload has succeeded the Serial Monitor will show the resulting output of the command operations. From time to time on will have to press the black button on the Discovery board itself to see the full result. Keep in mind that we upoload a new firmware to the board when we do a compile-upload cycle. So it happens from time to time that our code allready stzarts producing results befor the board is fully ready. 

<img alt="Raspberry Kernel I2C Confirmed"
     src="https://github.com/RiddleAndCode/ECLet_STM32/blob/master/images/Screen%20Shot%202018-05-19%20at%2020.28.51.png"/>


You can find more examples inside the folder of the very same name.

Basically the Arduino Examples have to be put into the Arduino Folder on your host computing system and the two library files "CryptoAuthLib-arduino" and "trezor-crypto" hav to put i"nto the folder "libraries" inside the same Arduino folder. In case it doesn't ecist create on, first.







