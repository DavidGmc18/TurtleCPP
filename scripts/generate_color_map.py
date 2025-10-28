import matplotlib.colors as mcolors
import os

output_path = "../generated/color_map.hpp"
os.makedirs(os.path.dirname(output_path), exist_ok=True) 

with open("../generated/color_map.hpp", "w") as f:
    f.write("#pragma once\n\n")
    f.write("#include <string>\n")
    f.write("#include <unordered_map>\n\n")
    f.write("namespace turtle {\n\n")
    f.write("const std::unordered_map<std::string, uint32_t> color_map = {\n")

    for color in list(mcolors.CSS4_COLORS):
        f.write('    {"' + color + '", 0x' + mcolors.CSS4_COLORS[color].split("#")[1] + "FF},\n")
    f.write("};\n\n")
    f.write("}")