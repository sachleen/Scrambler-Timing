int sensePin = A1;
int signalPin = 1;
int ledPin = 3;

#include <SoftwareSerialTX.h>
#define PIN_TX 4
SoftwareSerialTX TinySerial(SoftwareSerialTX::BAUD_9600, PIN_TX);

void setup()
{
    pinMode(signalPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, 0);
    
    //TinySerial.write("Starting Finish Line Sensor\n");
}

bool tripped = false; // sets to true when laser beam is broken.
int threshold = 900;
void loop()
{
    int reading = analogRead(sensePin);
    
    tripped = reading <= threshold;
    
    if (tripped) {
        digitalWrite(signalPin, 0);
        
        for (int i = 0; i < 10; i++) {
            digitalWrite(ledPin, 1);
            delay(100);
            digitalWrite(ledPin, 0);
            delay(100);
        }
    } else {
        digitalWrite(signalPin, 1);
    }
}