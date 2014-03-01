int sensePin = A1;
int signalPin = 1;
int ledPin = 3;

#include <SoftwareSerialTX.h>
#define PIN_TX 4
SoftwareSerialTX TinySerial(SoftwareSerialTX::BAUD_9600, PIN_TX);

bool tripped = false; // sets to true when laser beam is broken.
int threshold = 900;

unsigned long startTime = 0;
unsigned long endTime = 0;

void setup()
{
    pinMode(signalPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, 0);
    
    TinySerial.write("Starting Start Line Sensor\n");
    
    bool startTripped = true;
    bool finishTripped = true;
    
    while (1) {        
        // Ensure both sensors are aligned with their lasers
        while (startTripped || finishTripped) {
            flashLed(200);
            startTripped = analogRead(sensePin) <= threshold;
            finishTripped = digitalRead(signalPin) == 1;
        }
        
        TinySerial.write("Sensors aligned.");
        
        // Wait until the start sensors is tripped
        while (!startTripped) {
            startTripped = analogRead(sensePin) <= threshold;
        }
        
        unsigned long startTime = millis();
        
        digitalWrite(ledPin, 1);
        
        while (!finishTripped) {
            finishTripped = digitalRead(signalPin) == 1;
        }
        
        unsigned long endTime = millis();
        
        digitalWrite(ledPin, 1);
        printTime(endTime-startTime);

    }
    
}

void flashLed(int period) {
    digitalWrite(ledPin, 1);
    delay(period/2);
    digitalWrite(ledPin, 0);
    delay(period/2);
}

void printTime(unsigned long time) {
    /*
        Reverse the digits and print them out one by one
        need to reverse because print algorithm prints right to left.
    */
    unsigned long div;
    for (div = 1; div <= time; div *= 10);
    do {
        div /= 10;
        TinySerial.write((time/div) + '0');
        time %= div;
    } while(time);
    TinySerial.write("\n");
}

void loop()
{

}