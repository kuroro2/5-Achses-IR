#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoEasing.h>
#include <Servo.h>

// Create the Adafruit PWM Servo Driver object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// ServoEasing objects for each servo
ServoEasing Servo1;
ServoEasing Servo2;
ServoEasing Servo3;
ServoEasing Servo4;
ServoEasing Servo5;

// Define the pins for the potentiometers
#define POT1_PIN A0
#define POT2_PIN A1
#define POT3_PIN A2
#define POT4_PIN A3
#define POT5_PIN A4

// Servo channels on the Adafruit PWM driver
#define SERVO1_CHANNEL 0
#define SERVO2_CHANNEL 1
#define SERVO3_CHANNEL 2
#define SERVO4_CHANNEL 3
#define SERVO5_CHANNEL 4

// Parameters for the servo range (adjust based on your servos)
#define SERVOMIN  150 // Minimum pulse length count (servo at 0 degrees)
#define SERVOMAX  600 // Maximum pulse length count (servo at 180 degrees)

void setup() {
  // Initialize the PWM driver with the I2C address (default 0x40)
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz

  // Attach ServoEasing objects to channels on the Adafruit PWM driver
  Servo1.attach(SERVO1_CHANNEL, SERVOMIN, SERVOMAX, &pwm);
  Servo2.attach(SERVO2_CHANNEL, SERVOMIN, SERVOMAX, &pwm);
  Servo3.attach(SERVO3_CHANNEL, SERVOMIN, SERVOMAX, &pwm);
  Servo4.attach(SERVO4_CHANNEL, SERVOMIN, SERVOMAX, &pwm);
  Servo5.attach(SERVO5_CHANNEL, SERVOMIN, SERVOMAX, &pwm);

  // Set easing speed for all servos (optional)
  setSpeedForAllServos(20);  // Speed is in degrees per second

  Serial.begin(9600);
}

void loop() {
  // Read the positions from the potentiometers
  int pot1Value = analogRead(POT1_PIN);
  int pot2Value = analogRead(POT2_PIN);
  int pot3Value = analogRead(POT3_PIN);
  int pot4Value = analogRead(POT4_PIN);
  int pot5Value = analogRead(POT5_PIN);

  // Map the potentiometer values to servo angles (0-180 degrees)
  int angle1 = map(pot1Value, 0, 1023, 0, 180);
  int angle2 = map(pot2Value, 0, 1023, 0, 180);
  int angle3 = map(pot3Value, 0, 1023, 0, 180);
  int angle4 = map(pot4Value, 0, 1023, 0, 180);
  int angle5 = map(pot5Value, 0, 1023, 0, 180);

  // Move the servos to the mapped positions with easing
  Servo1.startEaseTo(angle1);
  Servo2.startEaseTo(angle2);
  Servo3.startEaseTo(angle3);
  Servo4.startEaseTo(angle4);
  Servo5.startEaseTo(angle5);

  // Execute the easing movement
  syncAllServosStartAndWait();  // Wait for all servos to complete movement

  // Print the angles for debugging
  Serial.print("Servo1: "); Serial.print(angle1);
  Serial.print(" Servo2: "); Serial.print(angle2);
  Serial.print(" Servo3: "); Serial.print(angle3);
  Serial.print(" Servo4: "); Serial.print(angle4);
  Serial.print(" Servo5: "); Serial.println(angle5);

  delay(50);  
}
