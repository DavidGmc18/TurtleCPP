file(WRITE "${OUTPUT_C}")
file(GLOB SHADER_FILES "${INPUT_DIR}/*")

foreach(SHADER_FILE IN LISTS SHADER_FILES)
    get_filename_component(FILE_EXT "${SHADER_FILE}" EXT)
    if(NOT EXISTS "${SHADER_FILE}" OR IS_DIRECTORY "${SHADER_FILE}" OR FILE_EXT STREQUAL ".h")
        continue()
    endif()

    get_filename_component(NAME "${SHADER_FILE}" NAME)
    get_filename_component(EXT "${NAME}" EXT)
    string(SUBSTRING "${EXT}" 1 -1 EXT_NO_DOT)

    file(READ "${SHADER_FILE}" CONTENTS)

    string(REPLACE "\"" "\\\"" ESCAPED_CONTENTS "${CONTENTS}")
    string(REPLACE "\n" "\\n\"\n\"" ESCAPED_CONTENTS "${ESCAPED_CONTENTS}")

    file(APPEND "${OUTPUT_C}" "const char* shader_${EXT_NO_DOT}_src = \"${ESCAPED_CONTENTS}\";\n\n")
endforeach()