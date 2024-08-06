#include <Arduino.h>

#define CLOCK_PIN 1
#define DATA_PIN 2

const uint32_t CLOCK_PERIOD_MICROS = 2000; // 500 Hz -> 1s / 500 = 2ms = 2000µs

// End of Transmission Marker
const uint32_t END_MARKER = 0b11010010110110101010101010;

// Function to send a bit in binary
void sendBit(bool bit) {
    digitalWrite(DATA_PIN, bit ? HIGH : LOW);
    delayMicroseconds(CLOCK_PERIOD_MICROS / 2);
    digitalWrite(CLOCK_PIN, HIGH);
    delayMicroseconds(CLOCK_PERIOD_MICROS / 2);
    digitalWrite(CLOCK_PIN, LOW);
}

// Function to send a data byte in hexadecimal
void sendData(uint8_t data) {
    for (int i = 7; i >= 0; i--) {
        sendBit((data >> i) & 1);
    }
}

// Function to send the end marker
void sendEndMarker() {
    for (int i = 31; i >= 0; i--) {
        sendBit((END_MARKER >> i) & 1);
    }
}

void setup() {
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    // Test data
    uint8_t exampleData[] = {0xA3, 0x7F, 0x42}; // Detecting BrickBit accesory

    // Send data
    for (int i = 0; i < sizeof(exampleData); i++) {
        sendData(exampleData[i]);
    }

    // Send end marker
    sendEndMarker();
}

void loop() {
    // Currently empty
}
