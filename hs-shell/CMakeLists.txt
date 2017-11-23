project(hs_shell)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c commands.c commands.h mapper.h tokenizer.c tokenizer.h)
add_executable(hs_shell ${SOURCE_FILES})
