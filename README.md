# PRK5TR
NPK , PR-3000-TR-7in1
## Installation
Just use Arduino Library Manager and search "PR-3000-TR-7in1 Library" in Sensors category.
## Main assumptions
- easy as possible,
- minimal memory consumption,
- non-blocking functions,
- supporting Device ID 1 -254.

## Basic example
```
#include "PRK5TR.h"
PRK5TR npk(Serial2);                              // decare class to npk
PRK5TR::DATA data;                                // decare DATA structure to data
void setup() {
  Serial.begin(9600);                             // GPIO1, GPIO3 (TX/RX pin on ESP-32 Development Board)
  Serial2.begin(4800);                            // GPIO17, GPIO16 (TX/RX pin on ESP-32 Development Board)
  npk.setID(0x01);                                // Set Slave ID
}

void loop() {
  if (npk.getMS(data))   {                         //Get Moisture value
    Serial.print("Soil moisture (1%): ");
    Serial.println(data.SOIL_MS);
  }
  if (npk.getTP(data))  {                          //Get Soil temperature value
    Serial.print("Soil temperature (*C): ");
    Serial.println(data.SOIL_TP);
  }
  if (npk.getEC(data))   {                         //Get Soil conductivity value
    Serial.print("EC (us/cm): ");
    Serial.println(data.SOIL_EC);
  }
  if (npk.getPH(data))   {                         //Get SoilPH value
    Serial.print("PH (pH): ");
    Serial.println(data.SOIL_PH);
  }
  if (npk.getN(data))  {                            //Get N value
    Serial.print("N (mg/L): ");
    Serial.println(data.SOIL_N);
  }
  if (npk.getP(data))  {                            //Get P value
    Serial.print("P (mg/L): ");
    Serial.println(data.SOIL_P);
  }
  if (npk.getK(data))   {                           //Get K value
    Serial.print("K (mg/L): ");
    Serial.println(data.SOIL_K);
  }
  delay(200);
  Serial.println();
  // Do other stuff...
}
```
## Output
```
N (mg/L):  103
P (mg/L):  108
K (mg/L):  203
```
## Additional remarks
Tested with PR-3000-TR-NPK-N01 and ESP-32 WROOM Development Board.
