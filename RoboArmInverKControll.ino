#include <Servo.h>
#include <PID_v1.h>

// Define the servos
Servo servo1, servo2, servo3, servo4, servo5;

// Servo pins
int servoPins[5] = {3, 5, 6, 9, 10};

// Define PID parameters
double Kp = 2.0, Ki = 0.5, Kd = 1.0;
double input[5], output[5], setpoint[5];

// Create PID controllers for each servo
PID pid1(&input[0], &output[0], &setpoint[0], Kp, Ki, Kd, DIRECT);
PID pid2(&input[1], &output[1], &setpoint[1], Kp, Ki, Kd, DIRECT);
PID pid3(&input[2], &output[2], &setpoint[2], Kp, Ki, Kd, DIRECT);
PID pid4(&input[3], &output[3], &setpoint[3], Kp, Ki, Kd, DIRECT);
PID pid5(&input[4], &output[4], &setpoint[4], Kp, Ki, Kd, DIRECT);

// Arm segment lengths 
double L1 = 10.0;  // Length of first segment
double L2 = 10.0;  // Length of second segment
double L3 = 5.0;   // Length of third segment 

// Desired position for the gripper 
double targetX = 15.0;
double targetY = 10.0;
double targetZ = 5.0;

void setup() {
  Serial.begin(9600);

  // Attach the servos to the pins
  servo1.attach(servoPins[0]);
  servo2.attach(servoPins[1]);
  servo3.attach(servoPins[2]);
  servo4.attach(servoPins[3]);
  servo5.attach(servoPins[4]);

  // Initialize the PID controllers
  pid1.SetMode(AUTOMATIC);
  pid2.SetMode(AUTOMATIC);
  pid3.SetMode(AUTOMATIC);
  pid4.SetMode(AUTOMATIC);
  pid5.SetMode(AUTOMATIC);
}

void loop() {
  // Inverse Kinematics to calculate target angles
  calculateInverseKinematics(targetX, targetY, targetZ, setpoint);

  // Read current angles
  input[0] = readServoAngle(POT1);
  input[1] = readServoAngle(POT2);
  input[2] = readServoAngle(POT3);
  input[3] = readServoAngle(POT4);
  input[4] = readServoAngle(POT5);

  // Compute PID outputs
  pid1.Compute();
  pid2.Compute();
  pid3.Compute();
  pid4.Compute();
  pid5.Compute();

  // Update servo positions based on PID output
  servo1.write(output[0]);
  servo2.write(output[1]);
  servo3.write(output[2]);
  servo4.write(output[3]);
  servo5.write(output[4]);

  // Small delay to allow for smooth movement
  delay(20);
}

void calculateInverseKinematics(double x, double y, double z, double* angles) {
  // IK Calculations for 5 angles
}

double readServoAngle(POT) {
  input = analogread(POT)
  return input;
}
