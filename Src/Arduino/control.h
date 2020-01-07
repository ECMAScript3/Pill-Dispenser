#pragma once
#include <Servo.h>
class rotary {
    public:
    rotary(int _srv, int _led, int _phot);
    rotary(int _srv);
//Advances rotary 1 space
    void advance_sen();
    void advance_deg(float deg);
    private:
    int led_p;
    int phot_p;
    int srv_p;
    float deg;
    Servo srv;
};