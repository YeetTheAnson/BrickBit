#include <HardwareSerial.h>

#define TX_PIN 1
#define RX_PIN 2

#define BAUD_RATE 9600

HardwareSerial SerialPort(1);

void setup() {
  SerialPort.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  // Listen for incoming data
  if (SerialPort.available()) {
    String receivedMessage = SerialPort.readStringUntil('\n');
    receivedMessage.trim(); // Remove any leading/trailing whitespace

    if (receivedMessage == "anyonethere?") {
      // Respond with "imhere"
      SerialPort.println("imhere");
    } else if (receivedMessage.startsWith("print(") && receivedMessage.endsWith(")")) {
      // Extract the text within the brackets
      String messageToPrint = receivedMessage.substring(6, receivedMessage.length() - 1);
      Serial.print(messageToPrint);
      // Send "received" response
      SerialPort.println("received");
    }
  }
}
