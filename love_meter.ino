/*
    LOVE METER
*/

const int sensorPin = A0; // Pin for TMP sensor
float baselineTemp = 20.0;

void setup() {
  // Open a serial port to see values from analog input
  Serial.begin(9600);

  // Initialize LED pins
  for(int pinNumber=2; pinNumber<5; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);  
  }

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
  float baselineTemp = (voltage - 0.5) * 100;
  Serial.print("Baseline Temperature: ");
  Serial.println(baselineTemp);
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

  // For every 2 degrees C, light up an LED
  if (temperature < baselineTemp+2){
    digitalWrite(2, LOW);  
    digitalWrite(3, LOW); 
    digitalWrite(4, LOW); 
  } else if(temperature >= baselineTemp+2 && temperature < baselineTemp+4){
    digitalWrite(2, LOW);  
    digitalWrite(3, LOW); 
    digitalWrite(4, HIGH); 
  } else if(temperature >= baselineTemp+4 && temperature < baselineTemp+6){
    digitalWrite(2, LOW);  
    digitalWrite(3, HIGH); 
    digitalWrite(4, HIGH);   
  } else if (temperature >= baselineTemp+6){
    digitalWrite(2, HIGH);  
    digitalWrite(3, HIGH); 
    digitalWrite(4, HIGH);   
  }
  // Don't read from ADC too quickly
  delay(1);
}
