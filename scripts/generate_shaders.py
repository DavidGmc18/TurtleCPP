import os

script_dir = os.path.dirname(os.path.abspath(__file__))
shaders_dir = os.path.join(script_dir, "../shaders")
output_path = os.path.join(script_dir, "../generated/shaders_src.cpp")

with open(output_path, "w") as f:
    f.write('#include "../src/shaders.hpp"')

    for shader in os.listdir(shaders_dir):
        name, extension = os.path.splitext(shader)
        extension = extension[1:]
        f.write('\n\nconst char* turtle::' + name + "_" + extension + "_src =")

        with open(os.path.join(shaders_dir, shader), "r") as s:
            for line in s:
                f.write('\n"' + line.replace("\n", "\\n") + '"')

        f.write(";")