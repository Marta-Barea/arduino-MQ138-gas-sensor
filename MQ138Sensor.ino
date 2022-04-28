// MQ-138 e-Nose System //

// For reliable measurements, it is necessary to stabilize the sensor for 2 hours //
// To do this, the system should be connected to the power supply socket while the sensor is cured for this period of time without exposure to the sample //

// Analog pin A0 has a MQ-138 sensor connected to it: 

int mq138Input = A0;

// Digital pins 2, 4 and 13 have LEDs connected to them:

int redLed = 2;
int greenLed = 13;
int blueLed = 4;

// Declare variables for stability measurement of the MQ-138 sensor:

int delta = 0;
int oldValues = 0;
int steps = 0;

// Set on the specified pin whether it should behave as an input or an output:

void setup() {
  
 Serial.begin(9600); // Initialize serial communication at 9600 bits per second
 pinMode(mq138Input, INPUT); // Make the MQ-138's pin an input
 pinMode(redLed, OUTPUT);// Make the red LED's pin an output
 pinMode(blueLed, OUTPUT);// Make the blue LED's pin an output
 pinMode(greenLed, OUTPUT); // Make the green LED's pin an output 
 
}

// The loop routine that runs on and on:

void loop() {

//Analog output reading:

 int mq138Status = analogRead(mq138Input); // Read the analog output of the MQ-138 sensor
 float voltage = mq138Status * (5.0 / 1023.0); // Convert the readout to a voltage value: Arduino UNO has analog inputs with 10-bit resolution (values from 0 to 1023)

// Set the stability conditions for the measurement of the MQ-138 sensor (evaluated on the ADC reading):

 steps = (steps + 1) % 10;

 if (steps == 0) {
 delta = mq138Status - oldValues;
 if (delta < 0) {
 delta = -1 * delta;
 }

 oldValues = mq138Status;

 if (delta < 5) {
 digitalWrite(blueLed, HIGH);
 } else {
 digitalWrite(blueLed, LOW);
 }
 }

 // Set the gas detection conditions:

 if (voltage > 1) { // The voltage of the MQ-138 sensor is stable at ~ 0.5 V
 digitalWrite(redLed, LOW);
 digitalWrite(greenLed, HIGH);
 } else {
 digitalWrite(redLed, HIGH);
 digitalWrite(greenLed, LOW);
 }
 
 // Print the MQ-138 sensor response:
 
 Serial.print("ADC:");
 Serial.print(mq138Status);
 Serial.print("    Voltage(V):");
 Serial.println(voltage);
 delay(100); // Delay in between reads
}
