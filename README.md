# TurtleCPP

Turtle implementation in C++

**Example program**
```
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
```

## Setup / Dependencies
### Windows
vcpkg installation:
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
[Environment]::SetEnvironmentVariable("Path",[Environment]::GetEnvironmentVariable("Path","User")+";$env:USERPROFILE\vcpkg","User")
```
Restart terminal and install GLFW:
```
vcpkg install glfw3
vcpkg integrate install
```
##
### MacOS

pkg-config and GLFW installation:
```
brew install pkg-config
brew install glfw
```

##
### Linux
GLFW installation:
```
sudo apt install libglfw3-dev
```

## Building from source
### 1. Clone this repository:
```
git clone https://github.com/DavidGmc18/TurtleCPP.git
cd TurtleCPP
```

### 2. Configure Cmake:

**Linux & MacOS**
```
cmake -S . -B build
```

**Windows**
```
cmake -S . -B build -G Ninja
```

##
> Use ```-DCMAKE_BUILD_TYPE=Release``` if you want release build type instead of debug.**

### 3. Build

```
cmake --build build
```