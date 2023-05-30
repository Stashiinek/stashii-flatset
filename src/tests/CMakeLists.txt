set(target_name test)

enable_testing()

add_executable(
    test
    tests/test.cpp
)

target_include_directories(
      ${target_name}
      PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(
    ${target_name}
    PRIVATE
      GTest::gtest_main
      librgr
)
