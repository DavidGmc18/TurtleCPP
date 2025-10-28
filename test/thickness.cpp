#include "turtle/turtle.hpp"

using namespace turtle;

int main() {
    Turtle turtle;
    turtle.set_speed(0);
    turtle.right(90);
    turtle.forward(100);
    turtle.go_to(100, 0.5);
    turtle.forward(100);

    mainloop();
}