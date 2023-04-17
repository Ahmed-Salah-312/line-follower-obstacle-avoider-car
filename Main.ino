// Variables used in measuring distance
long duration;
int distance;
// Ultrasonic sensor pins
#define TRIGGER_PIN 6
#define ECHO_PIN 5
// IR sensors pins
#define irLeft 9
#define irRight 7
// H-bridge pins
// Right motor
#define rightEnable 10
int right_motor_forward=8;
int right_motor_backward=13;
// Left motor
#define leftEnable 11
int Motor_left_forward=4;
int Motor_left_backward=12;

void setup() {
  // Defining the Arduino pins
  // Ultrasonic sensor
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // IR sensors
  pinMode(irRight,INPUT);
  pinMode(irLeft,INPUT);
  // H-bridge sensors
  // Enable pins for speed
  pinMode(rightEnable, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  // Input pins for direction
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);
  pinMode(Motor_left_forward,OUTPUT);
  pinMode(Motor_left_backward,OUTPUT);
}

void loop() {
  // Save the distance that the ultrasonic calculates in a variable
  distance = getDistance();  
  // If there is an obstacle close nearby, the car avoids it
  if (distance <= 15) {
    // Stop for a second
    Stop();
    delay(1000);
    // The car redirects itself left and moves for 675 milliseconds
    moveLeft();
    delay(250);
    moveForward();
    delay(675);
    // The car redirects itself right and moves for 675 milliseconds
    moveRight();
    delay(400);
    moveForward();
    delay(675);
  
  }
  // If there are no obstacles, it follows the line
  else {
   // When the left sensor sees black, the car goes left
    if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 0) {
      moveLeft();
    }
    // When the right sensor sees black, the car goes right
    else if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 1) {
      moveRight();
    }
    // If both sensors see the same color, the car goes forward
    else {
      moveForward();
    }
  }
}

int getDistance() {
  // Clears the trigger pin condition
  digitalWrite(TRIGGER_PIN, LOW); 
  delayMicroseconds(2);
  // Sets the trigger pin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  // Reads the echo pin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;  //Speed of sound wave divided by 2 (back and forth)
  return distance;
}
// Stop the motors by not giving them neither polarity nor speed
void Stop() {
  digitalWrite(Motor_left_forward, 0);
  digitalWrite(Motor_left_backward, 0);
  digitalWrite(right_motor_forward, 0);
  digitalWrite(right_motor_backward, 0); 
  analogWrite(rightEnable, 0);
  analogWrite(leftEnable, 0); 
}
// Move forward by giving the motors the same polarity, with slightly different speeds to compensate for physical errors
void moveForward() {
  digitalWrite(Motor_left_forward, HIGH);
  digitalWrite(Motor_left_backward, 0);
  digitalWrite(right_motor_forward, HIGH);
  digitalWrite(right_motor_backward, 0);
  analogWrite(rightEnable, 50);
  analogWrite(leftEnable, 51);
}
// Turn right by moving the left motor forward and the right one backward, with different speeds to make the car follow the line smoothly
void moveRight() {
  digitalWrite(Motor_left_forward, HIGH);
  digitalWrite(Motor_left_backward, 0);
  digitalWrite(right_motor_forward, 0);
  digitalWrite(right_motor_backward, HIGH);
  analogWrite(rightEnable, 55);
  analogWrite(leftEnable, 65); 
}
// Turn left by moving the right motor forward and the left one backward, with different speeds to make the car follow the line smoothly
void moveLeft() 
{
  digitalWrite(Motor_left_forward, 0);
  digitalWrite(Motor_left_backward, HIGH);
  digitalWrite(right_motor_forward, HIGH);
  digitalWrite(right_motor_backward, 0);
  analogWrite(rightEnable,65);
  analogWrite(leftEnable,55);
}
