file(WRITE "${OUTPUT_CPP}" "#include \"../src/shaders.hpp\"\n")

separate_arguments(INPUT_SHADERS_LIST NATIVE_COMMAND "${INPUT_SHADERS}")

foreach(SHADER_FILE IN LISTS INPUT_SHADERS_LIST)
    get_filename_component(FILE_EXT "${SHADER_FILE}" EXT)
    if(NOT EXISTS "${SHADER_FILE}" OR IS_DIRECTORY "${SHADER_FILE}" OR FILE_EXT STREQUAL ".h")
        continue()
    endif()

    get_filename_component(NAME "${SHADER_FILE}" NAME_WE)
    get_filename_component(EXT "${SHADER_FILE}" EXT)
    string(SUBSTRING "${EXT}" 1 -1 EXT_NO_DOT)

    file(READ "${SHADER_FILE}" CONTENTS)

    string(REPLACE "\"" "\\\"" ESCAPED_CONTENTS "${CONTENTS}")
    string(REPLACE "\n" "\\n\"\n\"" ESCAPED_CONTENTS "${ESCAPED_CONTENTS}")

    file(APPEND "${OUTPUT_CPP}" "const char* ${NAME}_${EXT_NO_DOT}_src = \"${ESCAPED_CONTENTS}\";\n\n")
endforeach()