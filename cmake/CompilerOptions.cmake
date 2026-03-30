add_library(velocity_compile_options INTERFACE)

target_compile_options(velocity_compile_options INTERFACE
        -Wall -Wextra -Wpedantic
        -Wno-unused-parameter
        -fno-exceptions
        -fno-rtti
)

if(VELOCITY_ENABLE_ASAN)
    target_compile_options(velocity_compile_options INTERFACE -fsanitize=address,undefined)
    target_link_options(velocity_compile_options INTERFACE -fsanitize=address,undefined)
endif()

if(VELOCITY_ENABLE_TSAN)
    target_compile_options(velocity_compile_options INTERFACE -fsanitize=thread)
    target_link_options(velocity_compile_options INTERFACE -fsanitize=thread)
endif()