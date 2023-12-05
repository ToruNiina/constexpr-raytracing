add_executable(ray main.cpp)
target_compile_options(ray PUBLIC "-fconstexpr-ops-limit=4294967295")
