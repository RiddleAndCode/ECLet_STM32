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

  /* Create a private and a public key inside slot 0.
   * Keep in mind that the secure element will never show 
   * you the private. It will stay unknown within the element
   * It can only be activated with its secure enclave for 
   * creating and validating signatures and producing HMACs
   */
  
  uint8_t public_key[64];
  bool isLocked;
  memset(public_key, 0x44, 64 );  // mark the key with bogus data
  
  status = atcab_init( gCfg );
  status = atcab_get_pubkey(0, public_key);;
  status = atcab_release();

  // spot check public key for bogus data, there should be none
  // pub key is random so can't check the full content anyway
  
  hexify("Public Key:", (const uint8_t *) public_key, sizeof(public_key));

}

void loop() {
  // nothing to be done here

}
