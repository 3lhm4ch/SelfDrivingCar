
#include <Arduino.h>

#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

int ir_receive_pin = 2;

void setup() {
    Serial.begin(115200);

    IrReceiver.begin(ir_receive_pin, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(ir_receive_pin)));
}

void loop() {
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */

    String direction = "stop";

    if (IrReceiver.decode()) {

        /*
         * Print a summary of received data
         */
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print extended info
            IrReceiver.printIRResultRawFormatted(&Serial, true);

            IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
        } else {
            IrReceiver.resume(); // Early enable receiving of the next IR frame

            IrReceiver.printIRResultShort(&Serial);
            IrReceiver.printIRSendUsage(&Serial);
        }
        Serial.println();

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
          
          Serial.println(F("Repeat received. Here you can repeat the same action as before."));
        } else {
          if (IrReceiver.decodedIRData.command == 0x10) {
              Serial.println(F("Received command 0x10."));
              direction = "något bra";
          } else if (IrReceiver.decodedIRData.command == 0x11) {
              Serial.println(F("Received command 0x11."));
              direction = "något annat bra";
          }
        }
    }
    runCar(direction);
}

void runCar(String direction){
  if (direction == "fram"){
    if (direction == "vanster"){
      digitalWrite(motorleft, LOW);
      digitalWrite(motorright, HIGH);
    } else if (direction == "hoger"){
      digitalWrite(motorleft, HIGH);
      digitalWrite(motorright, LOW);
    } else{
      digitalWrite(motorleft, LOW);
      digitalWrite(motorright, LOW);
    }
  } else{
    digitalWrite(motorleft, LOW);
    digitalWrite(motorright, LOW);
  }
}
