#include "turtle.hpp"

int main() {
    screen_size(1000, 750);
    bgcolor(150, 150, 150);

    Turtle t;

    t.set_speed(100);
    
    t.circle(-50, 180, 18);
    t.circle(100, 180, 6);

    t.left(90);
    t.forward(300);

    t.right(45);
    t.circle(200);

    mainloop();
    return 0;
}