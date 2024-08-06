#include <HardwareSerial.h>

#define TX_PIN 1
#define RX_PIN 2

#define BAUD_RATE 9600

HardwareSerial SerialPort(1);

void setup() {
  // Configure serial communication
  SerialPort.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  // Send "anyonethere?" every second until we get a response
  while (true) {
    SerialPort.println("anyonethere?");
    delay(1000);
    if (SerialPort.available()) {
      String response = SerialPort.readStringUntil('\n');
      response.trim(); // Remove any leading/trailing whitespace
      if (response == "imhere") {
        break;
      }
    }
  }

  // Send "print(helloworld)" and wait for "received"
  SerialPort.println("print(helloworld)");
  while (true) {
    if (SerialPort.available()) {
      String response = SerialPort.readStringUntil('\n');
      response.trim(); // Remove any leading/trailing whitespace
      if (response == "received") {
        break;
      }
    }
  }

  // Continue with the rest of the code
}
