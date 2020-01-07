#include "timing.h"
ISR (WDT_vect) 
{
   wdt_disable();
}
clock::clock(unsigned long tm, int _time_sz = 1) {
    time_sz = _time_sz;
    time_array = calloc(time_sz, sizeof(tme));
    daytime = tm;
    millis_0 = millis();
};
clock::~clock() {
    free(time_array);
};
int clock::reg_trg(unsigned long t, void (*func)()) {
    assert(n < time_sz);
    tme* tm_ptr = (time_array + n * sizeof(tme));
    tm_ptr->func = func;
    tm_ptr->execd = false;
    tm_ptr->tm = t;
    n++;
};
int clock::update_trg(unsigned long t, void (*func)(), int _n) {
    assert(_n < time_sz);
    tme* tm_ptr = (time_array + _n * sizeof(tme));
    tm_ptr->func = func;
    tm_ptr->execd = false;
    tm_ptr->tm = t;
};
void clock::update_tm(unsigned long tm) {
    daytime = tm;
};
void clock::run() {
    daytime += 8000 + millis() - millis_0;
    millis_0 = millis();
    if (daytime >= day_max) {
        daytime %= day_max;
        for (int i = n; --i>=0;) {
        tme* tm_ptr = (time_array + i * sizeof(tme));
        tm_ptr->execd = false;
    }
    }
    for (int i = n; --i>=0;) {
        tme* tm_ptr = (time_array + i * sizeof(tme));
        if (daytime >= tm_ptr->tm && !tm_ptr->execd) {
            (*(tm_ptr->func))();
        }
    }
    MCUSR = 0;   
    WDTCSR = bit (WDCE) | bit (WDE);
    WDTCSR = bit (WDIE) | bit (WDP3) | bit (WDP0);
    
    wdt_reset();
    set_sleep_mode(SLEEP_MODE_STANDBY);
    interrupts();
    sleep_enable();
    sleep_cpu();
    sleep_disable();

};