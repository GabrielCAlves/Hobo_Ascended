#ifndef __US_H
#define __US_H

#include "motor.h"

Ultrasonic rightUS(3, 4);
Ultrasonic frontUS(9, 8);
Ultrasonic leftUS(5, 6);

int usSide(int side) {
  return (side == RIGHT) ? rightUS.read() : leftUS.read();
}

bool nearFront(int minDist=10) {
  int frontD = frontUS.read();
  return ((0 < frontD) && (frontD < minDist));
}

bool rampDetect() {
  int lr = leftUS.read();
  int rr = rightUS.read();

  bool lramp = (0 < lr) && (lr < 7);
  bool rramp = (0 < rr) && (rr < 7);

  return (lramp && rramp);
}

int getWallDist(int side) {
  int wallSize = 0, wallDist;
  do {
    wallSize++;

    int leitura = usSide(side);
    wallDist = max(wallDist, leitura);

    drive(FRONT);

  } while (!nearFront());
  while (wallSize--) drive(BACK);

  return wallDist;
}

bool detectVictim(int side) {
  int wallDist = getWallDist(side);

  int ballDist = 0;
  int ballPos = 0;
  while (!nearFront()) {
    int distRead = usSide(side);
    if (distRead < wallDist-10) {
      ballDist = distRead;
      break;
    }
  }

  if (ballDist) {
    turn90(otherSide(side));
    drive(BACK, ballDist+3, 3500);

    drive(FRONT, ballDist);
    turn90(side);

    return true;
  }

  else return false;
}

void obstacleDeflect() {
  int dist = frontUS.read();

  if (dist < 4 && dist > 0) turnObstacle();
}

#endif
