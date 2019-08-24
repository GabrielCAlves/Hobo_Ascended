#include "Ultrasonic.h"
#include "color.h"
#include "motor.h"
#include "ir.h"
#include "us.h"

#define THRESHOLD 200

#define LF_SPEED 2500
#define TURN_TIMES 50
#define REG_TIMES 5

int rs[] = {30, 31, 32, 33};
int ls[] = {36, 37, 38, 39};

int rightThresh[] = {25, 115, 28, 132, 23, 110};
int leftThresh[] = {25, 120, 27, 135, 23, 115};

Sensor rightColor(rs, 34, rightThresh);
Sensor leftColor(ls, 35, leftThresh);

int consecutiveCount = 0;
bool finishedLF = false;

void setup() {
  Serial.begin(9600);
}

int loopCount = 0;

void loop() {
  loopCount++;

  if (!finishedLF) lineFollower(true);
  else rescueArea();

  lineFollower(true);
}

void testGreen() {
  Serial.print("L ");
  leftColor.getReadings();
  leftColor.displayValues();
  Serial.print(leftColor.isGreen());
  Serial.print("   ");
  Serial.print("R ");
  rightColor.getReadings();
  rightColor.displayValues();
  Serial.print(rightColor.isGreen());
  Serial.println();
}

int getDiff() {
  int rightVal = (double)rightIR.readVal() * 0.68;
  int leftVal = leftIR.readVal();
  int diff = rightVal - leftVal;

  return diff;
}

void turn(int diff, int times=REG_TIMES) {
  if (diff > THRESHOLD) drive(RIGHT, TURN_TIMES);
  else if (diff < -THRESHOLD) drive(LEFT, TURN_TIMES);
  else drive(FRONT, times);
}

void doGreen() {
  bool rightG = rightColor.isGreen();
  bool leftG = leftColor.isGreen();

  if (!rightG && !leftG) return;
  else if (rightG && leftG) turnAround();
  else if (rightG) turnColor('R');
  else if (leftG) turnColor('L');

  //leftColor.displayValues();
  //Serial.print(" ");
  //rightColor.displayValues();
  //Serial.println();
}

void doRamp() {
  bool isRamp = rampDetect();
  consecutiveCount = (isRamp ? consecutiveCount + 1 : 0);
  if (consecutiveCount >= 3) {
    drive(BACK, 100);
    finishedLF = true;
  }
}

void rescueArea() {
  int ld, rd;

  bool rampL = true, rampR = true;
  while (rampL && rampR) {
    ld = leftUS.read();
    rd = rightUS.read();

    rampL = (0 < ld) && (ld < 7);
    rampR = (0 < rd) && (rd < 7);

    while (true) {
      lineFollower(false);
    }
  }

  drive(FRONT, 50);

  int side = (ld > rd) ? LEFT : RIGHT;
  detectVictim(side);
}

void lineFollower(bool notOnRamp) {
  if (notOnRamp) {
    doRamp(); if (finishedLF) return;
    doGreen();
    if (nearFront(5)) turnObstacle();
    turn(getDiff());
  }
  turn(getDiff(), 50);
}
