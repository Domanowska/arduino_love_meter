/*
    LOVE METER
*/

const int sensorPin = A0; // Pin for TMP sensor
const float baselineTemp = 20.0;

void setup() {
  // Open a serial port to see values from analog input
  Serial.begin(9600);

  // Initialize LED pins
  for(pinNumber=2; pinNumber<5; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
