/**
 * \optimized and made MCU agnostic by Tom Fuerstner for RIDDLE&CODE
 * \date   April 25, 2017
 * \file
 * \brief  Hardware Interface Functions - I2C bit-banged
 * \author Atmel Crypto Group
 * \date   November 18, 2015
 *
 * \copyright Copyright (c) 2015 Atmel Corporation. All rights reserved.
 * \optimized and made MCU agnostic by Tom Fuerstner for RIDDLE&CODE
 * \date   April 25, 2017
 *
 * \atmel_crypto_device_library_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel integrated circuit.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \atmel_crypto_device_library_license_stop
 */

#include "Arduino.h"
#include "i2c_bitbang_at88ck9000.h"


uint32_t pin_sda, pin_scl;

I2CBuses i2c_buses_default = {
    //Arduino nRF52 = Nordic nRF52832
    // { 22 },//SDA
    // { 23 }//SCL
    //Arduino  = Atmel SAM D21
    //{ 20 },//SDA
    //{ 21 }//SCL
    //Arduino TI CC = Texas Instruments CC 1310
    // { 16 },//SDA
    // { 17 }//SCL
    //Freedomboard = Freescale/NXP KW41Z
    // { 20 },//SDA
    // { 21 }//SCL
    //Arduino RIDDLE&CODE = nRF52832 & nRF52840
    // { 5 },//SDA
    // { 4 }//SCL
    //RIDDLE&CODE Feather Bluefruit = Atmel SAM D21 / M0 Espresso
    // { 26 },//SDA
    // { 27 }//SCL
    //Adafruit Feather Bluefruit = Nordic Semi nRF52832
    // { 25 },//SDA
    // { 26 } //SCL
    //Raspberry Pi 3 = Broadcom
    // { 17 },//SDA
    // { 18 } //SCL
    //Asus Tinker Board = Rockwell
    // { 21 },//SDA
    // { 22 } //SCL
    //!!! Experimental !!! Parallela FPGA Board Arduino
    // { 21 },//SDA
    // { 22 } //SCL
    // STM32L475VG-DISCOVERY-IOT
    // { 14 },//SDA
    // { 15 } //SCL
		{ PC1 },//SDA
    { PC0 } //SCL
};


void I2C_ENABLE()
{
    pinMode(pin_sda, OUTPUT);
    pinMode(pin_scl, OUTPUT);
}
void I2C_DISABLE()
{
    pinMode(pin_sda, INPUT_PULLUP);
    pinMode(pin_scl, INPUT_PULLUP);
}
void I2C_CLOCK_LOW()
{
    digitalWrite(pin_scl, LOW);
}
void I2C_CLOCK_HIGH()
{
    digitalWrite(pin_scl, HIGH);
}
void I2C_DATA_LOW()
{
    digitalWrite(pin_sda, LOW);
}
void I2C_DATA_HIGH()
{
    digitalWrite(pin_sda, HIGH);
}
byte I2C_DATA_IN()
{
    return digitalRead(pin_sda);
}
void I2C_SET_OUTPUT()
{
    pinMode(pin_sda, OUTPUT);
}
void I2C_SET_OUTPUT_HIGH()
{
    I2C_SET_OUTPUT();
    I2C_DATA_HIGH();
}
void I2C_SET_OUTPUT_LOW()
{
    I2C_SET_OUTPUT();
    I2C_DATA_LOW();
}
void I2C_SET_INPUT()
{
    pinMode(pin_sda, INPUT_PULLUP);
}
void DISABLE_INTERRUPT()
{
    noInterrupts();
}
void ENABLE_INTERRUPT()
{
    interrupts();
}
void I2C_CLOCK_DELAY_WRITE_LOW()
{
    delayMicroseconds(1);
}
void I2C_CLOCK_DELAY_WRITE_HIGH()
{
    delayMicroseconds(1);
}
void I2C_CLOCK_DELAY_READ_LOW()
{
    delayMicroseconds(1);
}
void I2C_CLOCK_DELAY_READ_HIGH()
{
    delayMicroseconds(1);
}

//! This delay plus I2C_CLOCK_HIGH and I2C_CLOCK_LOW takes about 1.3 us.
void I2C_CLOCK_DELAY_SEND_ACK()
{
    delayMicroseconds(1); // 1
}
//! This delay is inserted to make the Start and Stop hold time at least 250 ns.
void I2C_HOLD_DELAY()
{
    delayMicroseconds(1);
}


//! loop count when waiting for an acknowledgment
const byte I2C_ACK_TIMEOUT=4;


void i2c_set_pin(uint32_t sda, uint32_t scl)
{
	pin_sda = sda;
	pin_scl = scl;
}

void i2c_enable(void)
{
	I2C_ENABLE();
	I2C_DATA_HIGH();
	I2C_CLOCK_HIGH();
}

void i2c_disable(void)
{
	I2C_DISABLE();
}


void i2c_send_start(void)
{
	//! Set clock high in case we re-start.
	I2C_CLOCK_HIGH();
	I2C_SET_OUTPUT_HIGH();
	I2C_DATA_LOW();
	I2C_HOLD_DELAY();
	I2C_CLOCK_LOW();
}

void i2c_send_ack(uint8_t ack)
{
	if (ack) {
		I2C_SET_OUTPUT_LOW();   //!< Low data line indicates an ACK.
		while (I2C_DATA_IN());
	}else {
		I2C_SET_OUTPUT_HIGH();  //!< High data line indicates a NACK.
		while (!I2C_DATA_IN());
	}

	//! Clock out acknowledgment.
	I2C_CLOCK_HIGH();
	I2C_CLOCK_DELAY_SEND_ACK();
	I2C_CLOCK_LOW();
}

void i2c_send_stop(void)
{
	I2C_SET_OUTPUT_LOW();
	I2C_CLOCK_DELAY_WRITE_LOW();
	I2C_CLOCK_HIGH();
	I2C_HOLD_DELAY();
	I2C_DATA_HIGH();
}

/* void i2c_send_wake_token(void)
{
    I2C_DATA_LOW();
    delayMicroseconds(80);
    I2C_DATA_HIGH();
} */


void i2c_send_wake_token(void)
{
	I2C_DATA_LOW();
  I2C_CLOCK_LOW();
	delayMicroseconds(60);
	I2C_DATA_HIGH();
  I2C_CLOCK_HIGH();
  delayMicroseconds(500);
}

/*void i2c_send_wake_token(void)
{
	I2C_DATA_LOW();
  delayMicroseconds(1);
  I2C_CLOCK_LOW();
	delayMicroseconds(8);
	I2C_CLOCK_HIGH();
  delayMicroseconds(1);
  I2C_DATA_HIGH();
}*/

ATCA_STATUS i2c_send_byte(uint8_t i2c_byte)
{
	ATCA_STATUS status = ATCA_TX_TIMEOUT;

	uint8_t i;

	DISABLE_INTERRUPT();

	//! This avoids spikes but adds an if condition.
	//! We could parametrize the call to I2C_SET_OUTPUT
	//! and translate the msb to OUTSET or OUTCLR,
	//! but then the code would become target specific.
	if (i2c_byte & 0x80)
		I2C_SET_OUTPUT_HIGH();
	else
		I2C_SET_OUTPUT_LOW();

	//! Send 8 bits of data.
	for (i = 0; i < 8; i++) {
		I2C_CLOCK_LOW();
		if (i2c_byte & 0x80)
			I2C_DATA_HIGH();
		else
			I2C_DATA_LOW();

		I2C_CLOCK_DELAY_WRITE_LOW();

		//! Clock out the data bit.
		I2C_CLOCK_HIGH();

		//! Shifting while clock is high compensates for the time it
		//! takes to evaluate the bit while clock is low.
		//! That way, the low and high time of the clock pin is
		//! almost equal.
		i2c_byte <<= 1;
		I2C_CLOCK_DELAY_WRITE_HIGH();
	}
	//! Clock in last data bit.
	I2C_CLOCK_LOW();

	//! Set data line to be an input.
	I2C_SET_INPUT();

	I2C_CLOCK_DELAY_READ_LOW();
	//! Wait for the ack.
	I2C_CLOCK_HIGH();
	for (i = 0; i < I2C_ACK_TIMEOUT; i++) {
		if (!I2C_DATA_IN()) {
			status = ATCA_SUCCESS;
			I2C_CLOCK_DELAY_READ_HIGH();
			break;
		}
	}
	I2C_CLOCK_LOW();

	ENABLE_INTERRUPT();

	return status;
}

ATCA_STATUS i2c_send_bytes(uint8_t count, uint8_t *data)
{
	ATCA_STATUS status = ATCA_TX_TIMEOUT;

	uint8_t i;

	for (i = 0; i < count; i++) {
		status = i2c_send_byte(data[i]);
		if (status != ATCA_SUCCESS) {
			if (i > 0)
				status = ATCA_TX_FAIL;
			break;
		}
	}

	return status;
}


/* uint8_t i2c_receive_one_byte(uint8_t ack)
{
	uint8_t i2c_byte;
	uint8_t i;

	DISABLE_INTERRUPT();

	I2C_SET_INPUT();
	for (i = 0x80, i2c_byte = 0; i; i >>= 1) {
		I2C_CLOCK_HIGH();
		//I2C_CLOCK_DELAY_READ_HIGH();
    delayMicroseconds(0.6);
		if (I2C_DATA_IN())
			i2c_byte |= i;
		I2C_CLOCK_LOW();
		if (i > 1) {
			//! We don't need to delay after the last bit because
			//! it takes time to switch the pin to output for acknowledging.
			//I2C_CLOCK_DELAY_READ_LOW();
      delayMicroseconds(0.4);
		}
	}
	i2c_send_ack(ack);

	ENABLE_INTERRUPT();

	return i2c_byte;
} */


uint8_t i2c_receive_one_byte(uint8_t ack)
{
                uint8_t i2c_byte;
                uint8_t i;

                DISABLE_INTERRUPT();

                I2C_SET_INPUT();
                for (i = 0x80, i2c_byte = 0; i; i >>= 1) {
                               I2C_CLOCK_HIGH();
                               //I2C_CLOCK_DELAY_READ_HIGH();
                               delayMicroseconds(0.6); // 0.6
                               if (I2C_DATA_IN())
                                               i2c_byte |= i;
                               I2C_CLOCK_LOW();
                               if (i > 1) {
                                  //! We don't need to delay after the last bit because
                                  //! it takes time to switch the pin to output for acknowledging.
                                  //I2C_CLOCK_DELAY_READ_LOW();
                                  delayMicroseconds(0.4); //0.4
                               }
                }
                i2c_send_ack(ack);

                ENABLE_INTERRUPT();

                return i2c_byte;
}

void i2c_receive_byte(uint8_t *data)
{
	*data = i2c_receive_one_byte(1);
}

void i2c_receive_bytes(uint8_t count, uint8_t *data)
{
	while (--count)
    {
		    *data++ = i2c_receive_one_byte(1);
    }
	*data = i2c_receive_one_byte(1); // default 1

	i2c_send_stop();
}
