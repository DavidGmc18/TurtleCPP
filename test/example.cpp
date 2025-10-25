#include "turtle.hpp"

int main() {
    screen_size(1000, 750);
    bgcolor({30, 127, 45}); // RGB color

    Turtle turtle;
    turtle.set_speed(200); // Speed in px/sec
    turtle.pencolor("purple"); // String as color
    turtle.penwidth(5); // Pen width in px

    turtle.left(90);
    turtle.forward(100);

    mainloop();
    return 0;
}