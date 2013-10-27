#include <Servo.h>
#include <XBee.h>

Servo light;
const int lightServo = 6;

Servo door;
const int doorServo = 7;

XBee xbee = XBee();
uint8_t payload[] = {
  'H', 'e', 'l', 'l', 'o'};

XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000FFFF);
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

ZBRxResponse rx = ZBRxResponse();
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));


void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  Serial.println("Connecting to XBee");
  Serial1.begin(9600);
  xbee.setSerial(Serial1);
  Serial.println("Ready to connect to Wireless");  
}

void loop(void) {  
  String message = readXbee();

  if (message.indexOf("Light") == 0) {
    light.attach(lightServo);  
    delay(250);          
    if (message.indexOf("On")) {
      light.write(90);
    }
    else if (message.indexOf("Off")) {
      light.write(0);
    }
    delay(250);
    light.detach();
  }
  
  if (message.indexOf("Door") == 0) {
    door.attach(doorServo);  
    delay(250);          
    if (message.indexOf("Unlock")) {
      door.write(10);
    }
    else if (message.indexOf("Lock")) {
      door.write(180);
    }
    delay(250);
    door.detach();
  }
  delay(80);
}

String readXbee(void) {
  xbee.readPacket();  
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(rx);         
      String f = String();
      for (int i = 0; i < rx.getDataLength(); i++) {
        f += char(rx.getData(i));  
      }
      return f;
    }
  }
  return "";
}
