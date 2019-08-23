#include "Ultrasonic.h"
#include "color.h"
#include "motor.h"
#include "ir.h"

// definir valores
#define THRESHOLD 300

#define LF_SPEED 2500
#define TURN_TIMES 25
#define REG_TIMES 5

// definir sensores US
Ultrasonic rightUS(3, 4);
Ultrasonic frontUS(9, 8);
Ultrasonic leftUS(5, 6);

// definir sensores IR
IR rightIR(A8);
IR centerIR(A9);
IR leftIR(A10);

// definir sensores cor
int rs[] = {30, 31, 32, 33};
int ls[] = {36, 37, 38, 39};

int rightThresh[] = {25, 115, 28, 132, 23, 110};
int leftThresh[] = {25, 120, 27, 135, 23, 115};

Sensor rightColor(rs, 34, rightThresh);
Sensor leftColor(ls, 35, leftThresh);

void setup() {

  setMotors();

  Serial.begin(9600);

}

void loop() {
  bool rightG = rightColor.isGreen();
  bool leftG = leftColor.isGreen();

  Serial.print(leftG);
  Serial.print(" ");
  Serial.println(rightG);

  delay(100);
}

void lineFollower() {
  bool rightG = rightColor.isGreen();
  bool leftG = leftColor.isGreen();
  
  int rightVal = (double)rightIR.readVal()*0.68;
  int leftVal = leftIR.readVal();
    
  int diff = rightVal - leftVal;
  
  if (rightG && leftG) turnAround();
  else if (rightG) turnColor('R');
  else if (leftG) turnColor('L');

  if (diff > THRESHOLD) drive(RIGHT, TURN_TIMES, LF_SPEED);
  else if (diff < -THRESHOLD) drive(LEFT, TURN_TIMES, LF_SPEED);
  else drive(FRONT, REG_TIMES, LF_SPEED);

}

void obstacleDeflect() {
  int dist = frontUS.read();

  if (dist < 4 && dist > 0) turnObstacle();

}
