/* 
 *  WalrusEye: Sensor Code
 *  
 *  code to get data from the Temp, GNSS, and Accelerometer 
 *  connected to the Spresense board and
 *  print it to the Serial Monitor
 *  
 *  created by Raunak Singh Inventor
 *  modified 22 Jul 2022
*/

#include <GNSS.h>
static SpGnss Gnss;

float temp;
int tempPin = A3;

int xOutPin = A0;
int yOutPin = A1;
int zOutPin = A2;

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

int micPin = A4;

void setup() {
    /* Setup serial output for printing. */
    Serial.begin(115200);

    /* Initialize GNSS. */
    Gnss.begin();
    Gnss.start();
}

void loop()
{
  /* Wait for an update. */
  if (Gnss.waitUpdate(-1))
  {
    /* Get navigation data. */
    SpNavData NavData;
    Gnss.getNavData(&NavData);

    /* Print position and satellite count. */
    Serial.print("LAT ");
    Serial.println(NavData.latitude, 6);
    Serial.print("LNG ");
    Serial.println(NavData.longitude, 6);
    
    temp = analogRead(tempPin);
    // read analog volt from sensor and save to variable temp
    temp = temp * 0.48828125;
    // convert the analog volt to its temperature equivalent
    Serial.print("TEMP ");
    Serial.print(temp); // display temperature value
    Serial.println();

    // read the  values for X, Y, Z
    int XValue = analogRead(xOutPin);
    int YValue = analogRead(yOutPin);
    int ZValue = analogRead(zOutPin);

    Serial.print("X ");
    Serial.print(XValue);
    Serial.println();
    Serial.print("Y ");
    Serial.print(YValue);
    Serial.println();
    Serial.print("Z ");
    Serial.print(ZValue);
    Serial.println();

    unsigned long startMillis= millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level

    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

    // collect data for 50 mS
    while (millis() - startMillis < sampleWindow)
    {
       sample = analogRead(4);
       if (sample < 1024)  // toss out spurious readings
       {
          if (sample > signalMax)
          {
             signalMax = sample;  // save just the max levels
           }
           else if (sample < signalMin)
          {
             signalMin = sample;  // save just the min levels
          }
       }
    }
    peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
    double volts = (peakToPeak * 5.0) / 1024;  // convert to volts

    Serial.print("MIC ");
    Serial.println(volts);
    
    delay(1000); // update sensor reading each one second
  }
}
