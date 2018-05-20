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
#include <uECC.h>

/*#define uECC_OPTIMIZATION_LEVEL 3
#define uECC_PLATFORM   uECC_arm
#define uECC_arm        3
#define uECC_WORD_SIZE  4
#define uECC_SUPPORTS_secp256r1
#define uECC_asm uECC_asm_fast*/
#define BAUD_RATE 9600



uint8_t uECC_RNG_ZEROIZE[32] = {0x00};
int pubKeyHostCnt = 0;

ATCAIfaceCfg *gCfg = &cfg_ateccx08a_i2c_default;
byte buffer[ 64];
ATCA_STATUS status = ATCA_GEN_FAIL;



  uint8_t uECC_RNG_PARAMETERS[32] = {
             0x82,0xc9,0x00,0x87,0xeb,0x71,0x1a,0x35,0x15,0x80,0xcc,0x72,0x61,0x73,0x8b,0xcb,
             0xb6,0x5a,0xbe,0x33,0xe1,0xe3,0x70,0x19,0x0e,0xe7,0x4f,0xd7,0x94,0x21,0xc8,0xc4
  };

  uint8_t ecc_pubKeyHost[64] =  {
             0x12,0x77,0x00,0x87,0xeb,0x71,0x1a,0x35,0x15,0x80,0xcc,0x72,0x61,0x73,0x8b,0xcb,
             0xb6,0x5a,0xbe,0x33,0xe1,0xe3,0x70,0x19,0x0e,0xe7,0x4f,0xd7,0x94,0x21,0xad,0x82,
             0x44,0x77,0x00,0x87,0xeb,0x71,0x1a,0x35,0x15,0x80,0xcc,0x72,0x61,0x73,0x8b,0xcb,
             0xb6,0x5a,0xbe,0x33,0xe1,0xe3,0x70,0x19,0x0e,0xe7,0x4f,0xd7,0x94,0x21,0xad,0x21
  };
 
  static int TRNG_fromSeed(uint8_t *dest, unsigned size) {
    memcpy(dest, uECC_RNG_PARAMETERS, 32);
    return 1;
  }


  static int TRNG(uint8_t *dest, unsigned size) {
    uint8_t rand_out[RANDOM_RSP_SIZE];
    status = atcab_init( gCfg );
    status = atcab_random(rand_out);
    status = atcab_release();
    //delayMicroseconds(20);
    delay(80);
    memcpy(dest, rand_out, 32);
    return 1;
  }


void setup() {
  Serial.begin(BAUD_RATE);
  delay(2000);
  Serial.print("\n\r");

    /* Simulate to endpoints exchanging keys
     *  using the Diffie-Hellman method
     */

    uint8_t ecc_privKeyASM[32];
    uint8_t ecc_privKeyHost[32];
    uint8_t ecc_pubKeyASM[64];
    uint8_t ecc_pubKeyHost[64];
    uint8_t ecdh_secretASM[32];
    uint8_t ecdh_secretHost[32];

    uECC_set_rng(&TRNG_fromSeed);
    //uECC_set_rng(&TRNG);

    /* Select the right elliptic curvve type */
    const struct uECC_Curve_t * curve = uECC_secp256r1();
    
    /* Create private and public key for a host system and
     *  an IoT endpoint device
     */
     
    uECC_make_key(ecc_pubKeyASM, ecc_privKeyASM, curve);
    uECC_make_key(ecc_pubKeyHost, ecc_privKeyHost, curve);

    /* Create the shared secrets. Keep in mind that this happens
     *  normally on two fifferent devices and only the public keys are exchanged
     */
     
    uECC_shared_secret(ecc_pubKeyHost, ecc_privKeyASM, ecdh_secretASM, curve);
    uECC_shared_secret(ecc_pubKeyASM, ecc_privKeyHost, ecdh_secretHost, curve);


    /* Print out the two independently produced secrets and check
     *  them to be equal
     */

    for (int i = 0; i < 32; i++){ 
       static char tmp[4] = {};
       sprintf(tmp, "%02X", ecdh_secretASM[i]);
       Serial.print(String(tmp));
    }

    Serial.print("\n\r");

    for (int i = 0; i < 32; i++){ 
       static char tmp[4] = {};
       sprintf(tmp, "%02X", ecdh_secretHost[i]);
       Serial.print(String(tmp));
    }

    Serial.print("\n\r");
 
  
}

void loop() {
  //Nothing to be done
}
