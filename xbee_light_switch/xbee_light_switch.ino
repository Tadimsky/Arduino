#include <Servo.h>

#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
Servo light;

XBee xbee = XBee();
uint8_t payload[] = {'H', 'e', 'l', 'l', 'o'};

XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000FFFF);
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

ZBRxResponse rx = ZBRxResponse();
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

const int lightServoSwitch = 8;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  Serial.println("Connecting to XBee");
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
  Serial.println("Ready to connect to Wireless");  
  
  light.attach(6);
}

void loop(void) {  
  
  /*
  xbee.readPacket();  
  if (xbee.getResponse().isAvailable()) {
        if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
          xbee.getResponse().getZBRxResponse(rx);        
          turnon();  
          String f = String();
          for (int i = 0; i < rx.getDataLength(); i++) {
            f += char(rx.getData(i));  
          }
          Serial.println(f);
          if (f == "Light:On") {
            turnon();
          }
          else if (f == "Light:Off") {
            turnoff();
          }
      }
  }
  delay(80);
  */
}

void turnon(void) {
  light.write(90);
}

void turnoff(void) {
  light.write(0);
}
