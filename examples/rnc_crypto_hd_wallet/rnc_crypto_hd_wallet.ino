#include <nist256p1.h>
#include <ripemd160.h>
#include <segwit_addr.h>
#include <script.h>
#include <blake2b.h>
#include <base58.h>
#include <blake2s.h>
#include <nem_serialize.h>
#include <sha3.h>
#include <address.h>
#include <check_mem.h>
#include <bip32.h>
#include <ecdsa.h>
#include <pbkdf2.h>
#include <options.h>
#include <base32.h>
#include <bip39_english.h>
#include <hasher.h>
#include <sha2.h>
#include <hmac.h>
#include <bip39.h>
#include <macros.h>
#include <rc4.h>
#include <rand.h>
#include <nem.h>
#include <curves.h>
#include <blake2_common.h>
#include <blake256.h>
#include <bignum.h>
#include <secp256k1.h>

#include <i2c_bitbang_at88ck9000.h>
#include <sha2_routines.h>
#include <atca_helpers.h>
#include <atca_basic.h>
#include <atca_compiler.h>
#include <atca_iface.h>
#include <atca_devtypes.h>
#include <atca_command.h>
#include <atca_start_config.h>
#include <atca_status.h>
#include <atca_device.h>
#include <hal_i2c_bitbang.h>
#include <atca_start_iface.h>
#include <atca_hal.h>
#include <atca_cfgs.h>
#include <cryptoauthlib.h>
#include <atca_crypto_sw_sha2.h>
#include <atca_host.h>
#include <atca_crypto_sw.h>


ATCAIfaceCfg *gCfg = &cfg_ateccx08a_i2c_default;
extern ATCADevice _gDevice;
byte buffer[ 64];
ATCA_STATUS status = ATCA_GEN_FAIL;


void hexify(const char *str, const uint8_t *hex, unsigned int len) {
  Serial.write(str);
  for (int i = 0; i < len; i++)  {
    static char tmp[4] = {};
    sprintf(tmp, "%02X", hex[i]);
    Serial.write(tmp);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);
  Serial.write("");

 /*const uint8_t ent[32] = {
                          0x68,0xa7,0x9e,0xac,0xa2,0x32,0x48,0x73,0xea,0xcc,0x50,0xcb,0x9c,0x6e,0xca,0x8c,
                          0xc6,0x8e,0xa5,0xd9,0x36,0xf9,0x87,0x87,0xc6,0x0c,0x7e,0xbc,0x74,0xe6,0xce,0x7c
                      }; */
                      
/*const uint8_t ent[32] = {
                          0x9e,0xf7,0xbf,0x56,0xf9,0x6f,0x68,0x30,0xbf,0xe9,0x60,0xde,0x9c,0x40,0x0b,0xfa,
                          0x2c,0x40,0x51,0xbc,0x87,0x5d,0x04,0xc5,0x27,0xaa,0xf7,0x62,0xc0,0xb6,0xff,0x0b
};*/

  status = atcab_init(gCfg);
  uint8_t ent[32];
  status = atcab_random(ent);
  status = atcab_release();
                      
 const char *mnemon = mnemonic_from_data(ent, 32);
 //const char *mnemon = "alcohol woman abuse must during monitor noble actual mixed trade anger aisle";
 

  Serial.println("");
  Serial.println(mnemon);

  uint8_t seed[512 / 8];
  const char *passphrase= "";
  mnemonic_to_seed(mnemon, passphrase, seed, NULL); 

  Serial.println("");
  hexify("Seed : ", seed, 64);
  Serial.println("");

  HDNode node, node_44h, node_1h, node_0h;

  hdnode_from_seed( seed, 64, SECP256K1_NAME, &node);

  
  /*hdnode_private_ckd_prime(&node, 1);
  hdnode_private_ckd_prime(&node, 1);
  hdnode_private_ckd_prime(&node, 0);
  //hdnode_private_ckd(&node, 0);
  //hdnode_private_ckd(&node, 0); */
  hdnode_fill_public_key(&node);
  
  
  hexify(" Node Priv Key : ", node.private_key, 32);
  Serial.println("");
  hexify(" Node Chain : ", node.chain_code, 32);
  Serial.println("");
  hexify(" Node Pub Key : ", node.public_key, 33);
  Serial.println("");
  Serial.println("");
  Serial.println("");

  char str[112];
  int strsize;
  
  hdnode_serialize_public(&node, 0x0000000, 0x043587DF, str, 112);

  Serial.println("Testnet Public Key");
  Serial.println(str);
  Serial.println("");

  hdnode_serialize_private(&node, 0x00000000, 0x0488ADE4, str, 112);

  Serial.println("Mainnet Private Key");
  Serial.println(str);
  Serial.println("");

  hdnode_serialize_private(&node, 0x00000000, 0x04358394, str, 112);

  Serial.println("Testnet Private Key");
  Serial.println(str);
  Serial.println("");


  hdnode_private_ckd_prime(&node, 44);
  uint32_t fp = hdnode_fingerprint(&node);
  hdnode_serialize_public(&node, fp, 0x04358394, str, 112);

  Serial.println("Testnet Private Key 44\'");
  Serial.println(str);
  Serial.println(""); 
 
  
}

void loop() {

  // nothing to do in the main loop

}
