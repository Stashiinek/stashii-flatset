set(target_name librgr)

add_library(${target_name} STATIC
    librgr/vector.hpp
    librgr/flatset.hpp)

target_include_directories(
    ${target_name} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

set_target_properties(librgr PROPERTIES LINKER_LANGUAGE CXX)

#set_target_properties(librgr PROPERTIES LINKER_LANGUAGE CXX)

#target_include_directories(
#      ${target_name}
#      PUBLIC
#        ${CMAKE_CURRENT_LIST_DIR}
#        ${PROJECT_SOURCE_DIR}/external/PicoSHA2
#
#    )

#target_link_libraries(
#    ${target_name}
#    PRIVATE
#      picosha2
#    )
