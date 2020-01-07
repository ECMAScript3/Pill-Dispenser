#include "control.h"

rotary::rotary(int _srv){
    srv_p = _srv;
    deg = 0;
    srv.attach(srv_p);
    srv.write(deg);
    srv.detach();
};
rotary::rotary(int _srv, int _led, int _phot){
    led_p = _led;
    phot_p = _phot;
    srv_p = _srv;
    pinMode(led_p, OUTPUT);
    pinMode(phot_p, INPUT);
};
void rotary::advance_sen() {
    digitalWrite(led_p, HIGH);
    srv.attach(srv_p);
    srv.write(100);
    while(digitalRead(phot_p) == LOW) {};
    srv.write(90);
    srv.detach();
};
void rotary::advance_deg(float deg) {
    deg += srv.read();
    srv.attach(srv_p);
    srv.write(deg);
    srv.detach();
};