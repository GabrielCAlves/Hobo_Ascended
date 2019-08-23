#ifndef __IR_H
#define __IR_H

struct IR {
  int port;

  IR(int p): port(p) {
    pinMode(port, INPUT);
  }

  inline int readVal() {
    return analogRead(port);
  }
};

#endif
