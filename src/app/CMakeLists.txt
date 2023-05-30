set(target_name app)

enable_testing()

add_executable(
    app
    app/main.cpp
)

target_include_directories(
    ${target_name} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    ${target_name}
    PRIVATE
      librgr
)
