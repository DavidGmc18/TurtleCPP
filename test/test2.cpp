#include "turtle.hpp"

int main() {
    screen_size(1000, 750);
    bgcolor(150, 150, 150);

    Turtle t1, t2, t3;

    t1.set_speed(100);
    t2.set_speed(100);
    t3.set_speed(100);

    t1.color(255, 0, 0);
    t2.color(0, 255, 0);
    t3.color(0, 0, 255);

    t1.penup();
    t2.penup();
    t3.penup();

    t1.go_to(0, -200);
    t2.go_to(0, -200);
    t3.go_to(0, -200);

    t1.pendown();
    t2.pendown();
    t3.pendown();

    int d = 400;

    t1.forward(d);
    for (int i = 0; i < d/10; ++i) {
        t2.forward(10);
        for (int j = 0; j < 20; ++j) {
            t3.forward(0.5);
        }
    }

    mainloop();
    return 0;
}