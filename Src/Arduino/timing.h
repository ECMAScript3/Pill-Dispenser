#pragma once
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <assert.h>
typedef struct tme {
  unsigned long tm;
  bool execd;
  void (*func)();
} tme;
class clock {
  public:
    clock(unsigned long tm, int _time_sz = 1);
    ~clock();
    //Register new trigger
    int reg_trg(unsigned long t, void (*func)());
    //Update existing trigger, n-th trigger updated in order of registration.
    int update_trg(unsigned long t, void (*func)(), int n);
    //Update the clock's time, used to correct accrued error
    void update_tm(unsigned long tm);
    // Run in loop, how clock keeps time and handles sleeping and triggers
    void run();
  private:
    unsigned long daytime;
    int n = 0;
    int time_sz;
    tme* time_array;
    const unsigned long day_max = 86400000;
    unsigned long millis_0;
};
