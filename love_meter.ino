#include <Servo.h>

/*
    LOVE METER
*/

Servo myServo;

const int sensorPin = A0; // Pin for TMP sensor
float baselineTemp = 20.0;
float hottestTemp = 26.0;
int angle;

void setup() {
  // Open a serial port to see values from analog input
  Serial.begin(9600);

  // Get average baselineTemp from the first 5 seconds of sensor readings
  int readings[500];
  // Keep track of number of readings
  int count = 0;

  Serial.print("Taking sample...");
  while(millis() < 5000){
    unsigned long reading = millis();
    
    // Get reading from sensor
    int sensorVal = analogRead(sensorPin); 

    // Store reading
    readings[count] = sensorVal;
    count++;

    // Don't take samples too quickly
    delay(10);
  }
  
  Serial.println(" Done!");
  Serial.print("Total readings: ");
  Serial.println(count);

  // Take average of readings
  double sum = 0;
  for(int i=0; i<count; i++){
    sum = sum + readings[i];
  }

  int averageReading = sum / count;
  Serial.print("Average reading: ");
  Serial.println(averageReading);
  
  // Convert the reading to voltage
  float voltage = (averageReading/1024.0) * 5.0;
  Serial.print("Voltage: ");
  Serial.println(voltage);

  // Convert the voltage to temperature in degrees
  // See: https://www.arduino.cc/documents/datasheets/TEMP-TMP35_36_37.pdf
  baselineTemp = (voltage - 0.5) * 100;
  Serial.print("Baseline Temperature: ");
  Serial.println(baselineTemp);
  hottestTemp = baselineTemp + 6;
  Serial.print("Hottest Temperature: ");
  Serial.println(hottestTemp);

  // Servo motor is getting input on pin 9
  myServo.attach(9);
}

void loop() {
  // Get reading from sensor
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.print(sensorVal);

  // Convert the ADC reading to voltage
  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  // Convert the voltage to temperature in degrees
  // See: https://www.arduino.cc/documents/datasheets/TEMP-TMP35_36_37.pdf
  float temperature = (voltage - 0.5) * 100;
  Serial.print(", degrees C: ");
  Serial.println(temperature);

  // Map temperature to servo motor angle
  angle = map(temperature, baselineTemp, hottestTemp, 0, 179);
  Serial.print(", angle: ");
  Serial.println(angle);

  // Rotate the servo motor
  myServo.write(angle);
  // Wait for servo meter to adjust angle
  delay(15);
  // TODO: Figure out why - https://forum.arduino.cc/t/temperature-sensor-gives-weird-readings-when-servo-motor-is-attached-why/486094
}
