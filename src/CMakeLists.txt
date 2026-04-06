add_library(velocity_types INTERFACE
        core/order.hpp
        common/types.hpp
)

target_include_directories(velocity_types INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(velocity_engine
        main.cpp
)

target_link_libraries(velocity_engine PRIVATE velocity_types)