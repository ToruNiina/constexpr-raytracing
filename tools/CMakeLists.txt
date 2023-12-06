add_executable(gen_rsqrt gen_rsqrt.cpp)
add_executable(gen_sqrt  gen_sqrt.cpp)

add_custom_target(gen_tables
    COMMAND gen_sqrt
    COMMAND gen_rsqrt
    COMMAND mv sqrt_*.dat ${PROJECT_SOURCE_DIR}/include/parameters
    COMMAND mv rsqrt_*.dat ${PROJECT_SOURCE_DIR}/include/parameters
    )

