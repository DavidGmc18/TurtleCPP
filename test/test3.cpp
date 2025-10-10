#include "turtle.hpp"

int main() {
    Turtle t;

    t.set_speed(100);
    
    t.circle(-50, 180, 18);
    t.circle(100, 180, 6);

    t.left(90);
    t.forward(300);

    t.right(45);
    t.circle(150);

    mainloop();
    return 0;
}