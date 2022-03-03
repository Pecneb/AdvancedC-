#ifndef TIMER
#define TIMER

#include <chrono>

class FunctionTimer {
  int timesToRun
  public:
  FunctionTimer(unsigned int ttr) : timesToRun(ttr) {}
  template <typename funcToRun>
  void runFunc(funcToRun);
  void 
};

#endif
