/*
 * ADXL335 Accelerometer Example
 * 
 * Shows how to read in analog input from the ADXL335 Accelerometer
 * 
 * Circuit for Adafruit version:
 *  Sensor Pin | Arduino Pin
 *  ------------------------
 *  Xout       | A0
 *  Yout       | A1
 *  Zout       | A2
 *  GND        | GND
 *  3Vo        | AREF
 *  Vin        | 5V
 *  
 * created by Raunak Singh Inventor
 * modified 22 Jul 2022
 */

// set the input pin for XOut, YOut, ZOut
int xOutPin = A0;
int yOutPin = A1;
int zOutPin = A2;
 
void setup() {
  Serial.begin(9600);
//  // set the voltage value at the top
//  // of the input range to 3.3V
//  // (the voltage being passed into the AREF pin)
//  analogReference(EXTERNAL);
}

void loop() {
  // read the  values for X, Y, Z
  int XValue = analogRead(xOutPin);
  int YValue = analogRead(yOutPin);
  int ZValue = analogRead(zOutPin);

  Serial.print("XValue: ");
  Serial.println(XValue);

  Serial.print("YValue: ");
  Serial.println(YValue);

  Serial.print("ZValue: ");
  Serial.println(ZValue);

  Serial.println();
  // delay(1000); 
}
