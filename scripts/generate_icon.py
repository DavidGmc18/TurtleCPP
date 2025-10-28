from PIL import Image

image = Image.open("../assets/turtle-icon-size_256.png").convert("RGBA")
width, height = image.size
pixels = list(image.getdata())

with open("../generated/icon.hpp", "w") as f:
    f.write("#pragma once\n\n")
    f.write("namespace turtle {\n\n")
    f.write(f"const int ICON_WIDTH = {width};\n")
    f.write(f"const int ICON_HEIGHT = {height};\n")
    f.write(f"const unsigned char ICON_PIXELS[{width*height*4}] = {{\n")

    for i, (r, g, b, a) in enumerate(pixels):
        f.write(f"{r},{g},{b},{a},")
        if (i + 1) % width == 0:
            f.write("\n")

    f.write("};\n\n")
    f.write("}")