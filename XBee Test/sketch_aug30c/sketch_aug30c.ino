#include <SoftwareSerial.h>

#include <XBee.h>


SoftwareSerial mySerial(10, 11); // RX, TX

XBee xbee = XBee();
uint8_t payload[] = {
  'H', 'e', 'l', 'l', 'o'};

XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000FFFF);
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  Serial.println("lol");
  
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
  
  // xbee.setSerial(Serial);
}

void loop() {  
  xbee.readPacket();  
  if (xbee.getResponse().isError()) {
    Serial.println("Error");
  } 
  else {
    if (xbee.getResponse().isAvailable()) {
      if (xbee.getResponse().getApiId() != ZB_TX_STATUS_RESPONSE ) {      
        xbee.getResponse().getZBTxStatusResponse(txStatus);
        Serial.println(rx.getOption());
      }      
      
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        xbee.getResponse().getZBRxResponse(rx);
        Serial.print("Response Data: ");
        
        for (int i = 0; i < rx.getDataLength(); i++) { 
          Serial.print((char)rx.getData(i));
        } 
        /*
        if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
          System
          Serial.println(*rx.getData());
          ZBTxRequest zbTx = ZBTxRequest(addr64, rx.getData(), sizeof(rx.getData()));
          xbee.send(zbTx);
        }
        else {
          // error
        }
        */
      }
      else {
        if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) {
          xbee.getResponse().getModemStatusResponse(msr); 
          Serial.println(msr.getStatus());
        }
      }
    }
    else {
      ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
      xbee.send(zbTx);
      delay(3500);
    }
  }

}

