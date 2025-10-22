#include "turtle.hpp"

void srpienski_triangle(Turtle& t, float size, int n) {
    if (n < 0) {
        return;
    } else if (n == 0) {
        for (int i = 0; i < 3; ++i) {
            t.forward(size);
            t.left(120);
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            t.forward(size/2);
            srpienski_triangle(t, size/2, n-1);
            t.forward(size/2);
            t.left(120);
        }
    }
}

int main() {
    screen_size(1000, 800);
    Turtle t;
    t.set_speed(1000);
    t.penup();
    t.go_to(-200, -150);
    t.pendown();
    t.right(90);

    srpienski_triangle(t, 400, 4);

    mainloop();
}