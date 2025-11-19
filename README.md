# TurtleCPP

Turtle implementation in C++

**Example program**
```
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
> Use ```-DCMAKE_BUILD_TYPE=Release``` if you want release build type instead of debug.

### 3. Build

```
cmake --build build
```

### 4. Run test (optional)

**Windows**
```
.\test.bat <testname>
```


**Linux & MacOS**
```
chmod +x ./test.sh
./test.sh <testname>
```

###
> ```<testname>``` is the name of the C++ test file inside the /test folder without the .cpp extension. For example, to run test.cpp on Windows ```.\test.bat test```