#include "PRK5TR.h"
PRK5TR npk(Serial2);                             // decare class to npk name.
PRK5TR::DATA data;                               // decare DATA structure to data

void setup() {
  Serial.begin(9600);                            // GPIO1,   GPIO3 (TX/RX pin on ESP-32 Development Board)
  Serial2.begin(4800);                           // GPIO17, GPIO16 (TX/RX pin on ESP-32 Development Board)
  npk.setID(0x01);                               // Set Slave ID
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
  delay(1000);
  // Do other stuff...
}
