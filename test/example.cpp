#include "turtle/turtle.hpp"

using namespace turtle;

int main() {
    screen_size(1000, 750);
    bgcolor({30, 127, 45}); // RGB color

    Turtle turtle;
    turtle.set_speed(200); // Speed in px/sec
    turtle.pencolor("purple"); // String as color
    turtle.penwidth(5); // Pen width in px

    turtle.penup();
    turtle.go_to(0, -100); // goto coordinates
    turtle.pendown();

    turtle.forward(200);
    turtle.left(90);
    turtle.forward(80);
    turtle.backward(160);

    mainloop();
    return 0;
}