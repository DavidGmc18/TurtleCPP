#include "turtle/turtle.hpp"

using namespace turtle;

int main() {
    Turtle t;

    t.set_speed(100);
    
    t.circle(-50, 180, 18);

    t.fillcolor({255, 0, 0});

    t.begin_fill();
    t.circle(100, 180, 6);
    t.end_fill();
    
    t.left(90);
    t.forward(300);

    t.right(45);
    t.fillcolor("green");
    t.begin_fill();
    t.circle(150);

    t.left(90);

    mainloop();
    return 0;
}