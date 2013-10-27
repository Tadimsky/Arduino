
#include <XBee.h>

Xbee xbee = XBee();
unit8_t payload[] = {'H', 'e', 'l', 'l', 'o'};
XBeeAddress64 addr64 = XBeeAddress64(0x0, 0xFFFF);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  ZBTxRequest zbTx = ZBTXRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);
  delay(1000);  
}
