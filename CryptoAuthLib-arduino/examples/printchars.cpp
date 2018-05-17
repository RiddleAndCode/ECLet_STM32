#include "printchars.h"
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

int UNITY_OUTPUT_CHAR(int a)
{
    Serial.write(a);
}
#ifdef __cplusplus
}
#endif
