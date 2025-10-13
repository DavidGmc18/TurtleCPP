#!/bin/bash
set -e

# ======================================================
# gen_shaders.sh — convert GLSL files into shaders.o
# ======================================================
# Usage:
#   ./gen_shaders.sh <shader_dir> <header_path> [output_obj]
# ======================================================

# Get absolute path of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Arguments relative to script dir, not CWD
SHADER_DIR="$SCRIPT_DIR/${1:-.}"
HEADER_PATH="$SCRIPT_DIR/${2:-shaders.h}"
OUTPUT_OBJ="$SCRIPT_DIR/${3:-build/shaders.o}"

mkdir -p "$(dirname "$OUTPUT_OBJ")"

# Make sure shader dir exists
if [ ! -d "$SHADER_DIR" ]; then
    echo "Error: Shader directory not found: $SHADER_DIR"
    exit 1
fi

# Make sure header exists
if [ ! -f "$HEADER_PATH" ]; then
    echo "Error: Header file not found: $HEADER_PATH"
    exit 1
fi

# Compute relative path for include
REL_INCLUDE=$(realpath --relative-to="$(dirname "$OUTPUT_OBJ")" "$HEADER_PATH" 2>/dev/null || echo "$HEADER_PATH")

# Temporary C file
TMP_C_FILE="$(dirname "$OUTPUT_OBJ")/shaders_gen.c"

# Generate temporary C file
{
    echo "#include \"$REL_INCLUDE\""
    for file in "$SHADER_DIR"/*; do
        [ -f "$file" ] || continue
        name=$(basename "$file")
        ext="${name##*.}"
        var="shader_${ext}_src"
        echo "const char* $var = R\"("
        cat "$file"
        echo ")\";"
    done
} > "$TMP_C_FILE"

# Compile
g++ -DDEBUG -fPIC -I"$(dirname "$HEADER_PATH")" -c "$TMP_C_FILE" -o "$OUTPUT_OBJ"

# Clean up
rm -f "$TMP_C_FILE"