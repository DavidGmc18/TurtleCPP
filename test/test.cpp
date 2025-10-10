#include "turtle.hpp"

int main() {
    screen_size(1000, 750);
    bgcolor("lightgrey");

    Turtle t;
    t.set_speed(200);

    t.color({255, 0, 0});
    t.forward(100);

    t.right(45);
    t.forward(100);

    t.penup();
    t.forward(200);

    t.pendown();
    t.penwidth(5);
    t.pencolor({0, 255, 0});
    t.left(45);
    t.backward(100);

    t.go_to(-100, 0);
    
    t.forward(128);

    t.penwidth(15);
    t.go_to(-100, -150);

    t.left(-90);
    t.forward(128);

    mainloop();
    return 0;
}