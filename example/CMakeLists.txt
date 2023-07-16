project(${PROJECT_EXMAPLE})

add_executable(${PROJECT_EXMAPLE} src/main.cpp)

target_link_libraries(${PROJECT_EXMAPLE} PRIVATE
    ${PROJECT_LIB}
    ${DEPENDENCY_LIBS}
)

target_include_directories(${PROJECT_EXMAPLE} PRIVATE ${PROJECT_INCLUDE_DIR})
