add_executable(ray main.cpp)
target_compile_options(ray PUBLIC "-fconstexpr-ops-limit=4294967295")

add_custom_target(run
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/ray image.ppm
    COMMAND convert image.ppm image.png
    )

