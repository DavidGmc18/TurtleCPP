#include "turtle/turtle.hpp"

using namespace turtle;

int main() {
    screen_size(1200, 600);

    Turtle t1;
    t1.set_speed(0);
    t1.penwidth(400);
    t1.right(330);
    t1.forward(200);

    mainloop();
}